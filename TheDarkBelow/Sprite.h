#ifndef COMPONENT_SPRITE
#define COMPONENT_SPRITE

#include <SFML/Graphics/Sprite.hpp>

namespace DarkBelow {
	namespace ECS {
		struct Sprite {
			sf::Sprite mSprite;
			sf::IntRect mDestination;
		};
	}
}

#endif 

