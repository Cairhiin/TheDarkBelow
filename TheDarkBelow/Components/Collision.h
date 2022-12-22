#ifndef COLLISION_COMPONENT
#define COLLISION_COMPONENT

#include "SFML/Graphics/Rect.hpp"

namespace DarKBelow {
	namespace ECS {
		struct Collision {
			sf::FloatRect hitbox;
		};
	}
}
#endif

