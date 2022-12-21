#ifndef COMPONENT_TRANSFORM
#define COMPONENT_TRANSFORM

#include <SFML/System/Vector2.hpp>

namespace DarkBelow {
	namespace ECS {
		struct Transform {
			sf::Vector2f position;
			sf::Vector2f rotation;
			sf::Vector2f scale;
		};
	}
}
#endif 

