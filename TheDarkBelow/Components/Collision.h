#ifndef COLLISION_COMPONENT
#define COLLISION_COMPONENT

#include "SFML/Graphics/Rect.hpp"
#include <string>

namespace DarkBelow {
	namespace ECS {
		struct Collision {
			sf::FloatRect hitbox;
			std::string tag;
		};
	}
}
#endif

