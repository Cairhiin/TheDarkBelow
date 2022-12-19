#include <SFML/Graphics.hpp>
#include "Coordinator.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"

DarkBelow::ECS::Coordinator gCoordinator;

static bool quit = false;

int main() {
    gCoordinator.Init();

    gCoordinator.RegisterComponent<DarkBelow::ECS::Transform>();
    gCoordinator.RegisterComponent<DarkBelow::ECS::Sprite>();
    gCoordinator.RegisterComponent<DarkBelow::ECS::RigidBody>();

    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}