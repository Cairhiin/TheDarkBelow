#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/RigidBody.h"
#include "Systems/RenderSystem.h"
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

    auto renderSystem = gCoordinator.RegisterSystem<ECS::RenderSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<ECS::Sprite>());
        signature.set(gCoordinator.GetComponentType<ECS::Transform>());
        gCoordinator.SetSystemSignature<ECS::RenderSystem>(signature);
    }
    
    auto Player = gCoordinator.CreateEntity();
    gCoordinator.AddComponent(
        Player,
        ECS::Transform{
            sf::Vector2f(200.f, 200.f),
            sf::Vector2f(0.f, 0.f),
            sf::Vector2f(1, 1)
        });

    sf::Texture playerTexture;
    playerTexture = gTextureLoader.getTexture("playerChar");
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    gCoordinator.AddComponent(
        Player,
        ECS::Sprite{
            playerSprite
        });

    renderSystem->init();

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        renderSystem->draw(window);
        window.display();
    }

    return 0;
}