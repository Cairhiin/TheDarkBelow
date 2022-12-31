#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/RigidBody.h"
#include "Components/Gravity.h"
#include "Components/Collision.h"
#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/PlayerControlSystem.h"
#include "ECS/Types.h"
#include "TextureLoader.h"
#include "Map.h"
#include "Constants.h"

DarkBelow::ECS::Coordinator gCoordinator;
DarkBelow::TextureLoader gTextureLoader;
static bool quit = false;

int main() {
    using namespace DarkBelow;
    
    sf::RenderWindow window(sf::VideoMode(640, 320), "The Dark Below");
    gCoordinator.init();
    gTextureLoader.init();

    gCoordinator.RegisterComponent<ECS::Transform>();
    gCoordinator.RegisterComponent<ECS::Sprite>();
    gCoordinator.RegisterComponent<ECS::RigidBody>();
    gCoordinator.RegisterComponent<ECS::Gravity>();
    gCoordinator.RegisterComponent<ECS::Collision>();

    auto physicsSystem = gCoordinator.RegisterSystem<ECS::PhysicsSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::RigidBody>());
        signature.set(gCoordinator.GetComponentType<ECS::Transform>());
        signature.set(gCoordinator.GetComponentType<ECS::Collision>());
        gCoordinator.SetSystemSignature<ECS::PhysicsSystem>(signature);
    }

    physicsSystem->init();

    auto renderSystem = gCoordinator.RegisterSystem<ECS::RenderSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::Sprite>());
        signature.set(gCoordinator.GetComponentType<ECS::Transform>());
        gCoordinator.SetSystemSignature<ECS::RenderSystem>(signature);
    }

    auto collisionSystem = gCoordinator.RegisterSystem<ECS::CollisionSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::Collision>());
        gCoordinator.SetSystemSignature<ECS::RenderSystem>(signature);
    }
    
    renderSystem->init();

    auto playerControlSystem = gCoordinator.RegisterSystem<ECS::PlayerControlSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::RigidBody>());
        gCoordinator.SetSystemSignature<ECS::PlayerControlSystem>(signature);
    }

    auto Player = gCoordinator.CreateEntity();
    gCoordinator.AddComponent(
        Player,
        ECS::Transform{
            sf::Vector2f(50.f, 0.f),
            sf::Vector2f(0.f, 0.f),
            Constants::Player::SCALE
        });
    gCoordinator.AddComponent(
        Player,
        ECS::RigidBody{
            sf::Vector2f(0.f, 0.f),
            sf::Vector2f(0.f, 0.f)
        });
    gCoordinator.AddComponent(
        Player,
        ECS::Gravity{
            Constants::Game::GRAVITY
        });
    gCoordinator.AddComponent(
        Player,
        ECS::Collision{
            sf::FloatRect(0.f, 0.f, 50.f, 100.f),
            "Player"
        });
    playerControlSystem->init(Player);

    std::string mapTextureId = "tileLevel1";
    auto level = std::make_unique<Map>(mapTextureId, Constants::Level::SCALE, Constants::Level::TILE_SIZE);
    level->Load();

    sf::Texture playerTexture;
    playerTexture = gTextureLoader.getTexture("playerChar");
    sf::Sprite playerSprite;
    gCoordinator.AddComponent(
        Player,
        ECS::Sprite{
            playerSprite,
            playerTexture
        });
    gCoordinator.GetComponent<ECS::Sprite>(Player).init();

    sf::Clock deltaClock;
    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    event.type = sf::Event::Closed;
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
            playerControlSystem->update(event);
        }

        physicsSystem->update(dt);

        window.clear();
        renderSystem->draw(window);
        window.display();
    }

    return 0;
}