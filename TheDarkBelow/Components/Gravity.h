#ifndef GRAVITY_COMPONENT
#define GRAVITY_COMPONENT

#include "SFML/System/Vector2.hpp"

namespace DarkBelow {
	namespace ECS {
		struct Gravity {
			sf::Vector2f force;
		};
	}
}

#endif
