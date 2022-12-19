#ifndef COMPONENT_RIGID_BODY
#define COMPONENT_RIGID_BODY

#include <SFML/System/Vector2.hpp>

namespace DarkBelow {
	namespace ECS {
		struct RigidBody {
			sf::Vector2f velocity;
			sf::Vector2f acceleration;
		};
	}
}

#endif 
