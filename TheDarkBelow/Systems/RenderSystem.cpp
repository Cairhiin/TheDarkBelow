#include "RenderSystem.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../ECS/Coordinator.h"
#include "../TextureLoader.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"

extern DarkBelow::TextureLoader gTextureLoader;
extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		void RenderSystem::init() {

		}

		void RenderSystem::draw(sf::RenderWindow& window) {
			for (auto const& entity : mEntities) {
				sf::Vector2f position = gCoordinator.GetComponent<Transform>(entity).position;
				sf::Sprite sprite = gCoordinator.GetComponent<Sprite>(entity).sprite;
				sprite.setPosition(position);
				window.draw(sprite);
			}
		}
	}
}