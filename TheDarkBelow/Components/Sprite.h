#ifndef COMPONENT_SPRITE
#define COMPONENT_SPRITE

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "../Constants.h"

namespace DarkBelow {
	namespace ECS {
		struct Sprite {
			sf::Sprite sprite;
			sf::Texture texture;
			sf::IntRect srcRect = sf::IntRect(0, 0, 0, 0);

			void init() {
				this->sprite.setTexture(this->texture);
				if (srcRect.height != 0) {
					this->sprite.setTextureRect(srcRect);
				}
			}
		};
	}
}

#endif 

