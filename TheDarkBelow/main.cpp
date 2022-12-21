#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/RigidBody.h"
#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/PlayerControlSystem.h"
#include "ECS/Types.h"
#include "TextureLoader.h"

DarkBelow::ECS::Coordinator gCoordinator;
DarkBelow::TextureLoader gTextureLoader;
static bool quit = false;

int main() {
    using namespace DarkBelow;
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "The Dark Below");
    gCoordinator.init();
    gTextureLoader.init();

    gCoordinator.RegisterComponent<ECS::Transform>();
    gCoordinator.RegisterComponent<ECS::Sprite>();
    gCoordinator.RegisterComponent<ECS::RigidBody>();

    auto physicsSystem = gCoordinator.RegisterSystem<ECS::PhysicsSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::RigidBody>());
        signature.set(gCoordinator.GetComponentType<ECS::Transform>());
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
            sf::Vector2f(200.f, 200.f),
            sf::Vector2f(0.f, 0.f),
            sf::Vector2f(1, 1)
        });
    gCoordinator.AddComponent(
        Player,
        ECS::RigidBody{
            sf::Vector2f(0.0f, 0.0f),
            sf::Vector2f(0.0f, 0.0f)
        });
    playerControlSystem->init(Player);


    sf::Texture playerTexture;
    playerTexture = gTextureLoader.getTexture("playerChar");
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    gCoordinator.AddComponent(
        Player,
        ECS::Sprite{
            playerSprite
        });

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