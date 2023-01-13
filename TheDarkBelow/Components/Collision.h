#ifndef COLLISION_COMPONENT
#define COLLISION_COMPONENT

#include <string>

#include "SFML/Graphics/Rect.hpp"
#include "../Constants.h"

namespace DarkBelow {
	namespace ECS {
		struct Collision {
			Constants::Level::TileNames tag;
			sf::FloatRect hitbox;
			bool onSolidGround = false;
		};
	}
}
#endif

