#include "RenderSystem.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../ECS/Coordinator.h"
#include "../TextureLoader.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"

#include "SFML/Graphics/RectangleShape.hpp"

extern DarkBelow::TextureLoader gTextureLoader;
extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		void RenderSystem::init() {

		}

		void RenderSystem::draw(sf::RenderWindow& window) {
			for (auto const& entity : mEntities) {
				auto& const transform = gCoordinator.GetComponent<Transform>(entity);
				sf::Sprite sprite = gCoordinator.GetComponent<Sprite>(entity).sprite;
				sprite.setPosition(transform.position);
				sprite.setScale(transform.scale);
				window.draw(sprite);
			}
		}
	}
}