#include "RenderSystem.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../ECS/Coordinator.h"
#include "../TextureLoader.h"
#include "SFML/Graphics/CircleShape.hpp"

extern DarkBelow::TextureLoader gTextureLoader;
extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		void RenderSystem::init() {
			mPlayerTexture = gTextureLoader.getTexture("playerChar");
			mPlayerSprite.setTexture(mPlayerTexture);
			mPlayerSprite.setPosition(200.f, 200.f);
		}

		void RenderSystem::draw(sf::RenderWindow& window) {
			window.draw(mPlayerSprite);
		}
	}
}