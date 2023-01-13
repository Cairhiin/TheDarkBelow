#ifndef COMPONENT_SPRITE
#define COMPONENT_SPRITE

#include <iostream>
#include <map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "../Animation.h"
#include "../Components/Animation.h"

namespace DarkBelow {
	namespace ECS {
		struct Sprite {
			std::map<AnimationType, sf::Sprite> sprites;
			sf::IntRect srcRect = sf::IntRect(0, 0, 0, 0);
			AnimationType currentSpriteName = AnimationType::IDLE;
			int offset = 0;

			void init() {
				if (srcRect.height != 0) {
					this->sprites[currentSpriteName].setTextureRect(srcRect);
				}
			}
		};
	}
}

#endif 

