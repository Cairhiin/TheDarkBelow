#ifndef COMPONENT_SPRITE
#define COMPONENT_SPRITE

#include <iostream>
#include <map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "../Constants.h"

namespace DarkBelow {
	namespace ECS {
		struct Sprite {
			std::map<const std::string, sf::Sprite> sprites;
			sf::IntRect srcRect = sf::IntRect(0, 0, 0, 0);
			std::string currentSpriteName;

			void init() {
				if (srcRect.height != 0) {
					this->sprites[currentSpriteName].setTextureRect(srcRect);
				}
			}
		};
	}
}

#endif 

