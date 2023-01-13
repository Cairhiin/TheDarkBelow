#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/RigidBody.h"
#include "Components/Gravity.h"
#include "Components/Collision.h"
#include "Components/Animation.h"
#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/PlayerControlSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/AnimationSystem.h"
#include "ECS/Types.h"
#include "TextureLoader.h"
#include "Map.h"
#include "Constants.h"
#include "SpatialHash.h"
#include "PlayerCreator.h"

DarkBelow::TextureLoader gTextureLoader;
DarkBelow::ECS::Coordinator gCoordinator;
static bool quit = false;

int main() {
    using namespace DarkBelow;
    
    sf::RenderWindow window(sf::VideoMode(1280, 640), "The Dark Below");
    gCoordinator.init();

    gCoordinator.RegisterComponent<ECS::Transform>();
    gCoordinator.RegisterComponent<ECS::Sprite>();
    gCoordinator.RegisterComponent<ECS::RigidBody>();
    gCoordinator.RegisterComponent<ECS::Gravity>();
    gCoordinator.RegisterComponent<ECS::Collision>();
    gCoordinator.RegisterComponent<ECS::Animation>();

    auto physicsSystem = gCoordinator.RegisterSystem<ECS::PhysicsSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::RigidBody>());
        signature.set(gCoordinator.GetComponentType<ECS::Transform>());
        signature.set(gCoordinator.GetComponentType<ECS::Gravity>());
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

    auto animationSystem = gCoordinator.RegisterSystem<ECS::AnimationSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::Sprite>());
        signature.set(gCoordinator.GetComponentType<ECS::Animation>());
        gCoordinator.SetSystemSignature<ECS::AnimationSystem>(signature);
    }

    auto collisionSystem = gCoordinator.RegisterSystem<ECS::CollisionSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::Collision>());
        signature.set(gCoordinator.GetComponentType<ECS::RigidBody>());
        signature.set(gCoordinator.GetComponentType<ECS::Transform>());
        gCoordinator.SetSystemSignature<ECS::RenderSystem>(signature);
    }
    
    renderSystem->init();

    auto playerControlSystem = gCoordinator.RegisterSystem<ECS::PlayerControlSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::RigidBody>());
        signature.set(gCoordinator.GetComponentType<ECS::Transform>());
        signature.set(gCoordinator.GetComponentType<ECS::Collision>());
        signature.set(gCoordinator.GetComponentType<ECS::Transform>());
        gCoordinator.SetSystemSignature<ECS::PlayerControlSystem>(signature);
    }

    std::string mapTextureId = "tileLevel1";
    auto level = std::make_unique<Map>(mapTextureId, Constants::Level::SCALE, Constants::Level::TILE_SIZE);
    level->Load();

    sf::Texture playerTexture;
    playerTexture = gTextureLoader.loadTexture("playerChar", "images/player/idle.png");
    std::array<sf::Texture, 4> playerTextures;
    playerTextures[0] = playerTexture;
    playerTexture = gTextureLoader.loadTexture("playerChar", "images/player/run.png");
    playerTextures[1] = playerTexture;
    auto& Player = PlayerCreator::CreatePlayerEntity(playerTextures);
    playerControlSystem->init(Player);

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
        animationSystem->update(dt);
        collisionSystem->update();

        window.clear();
        renderSystem->draw(window);
        window.draw(*level);
        window.display();
    }

    return 0;
}