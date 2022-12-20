#include <SFML/Graphics.hpp>
#include "Coordinator.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "RenderSystem.h"
#include "Transform.h"
#include "Types.h"
#include "TextureLoader.h"

DarkBelow::ECS::Coordinator gCoordinator;
DarkBelow::TextureLoader gTextureLoader;
static bool quit = false;

int main() {
    using namespace DarkBelow;
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
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

    renderSystem->init();

    while (window.isOpen()) {
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