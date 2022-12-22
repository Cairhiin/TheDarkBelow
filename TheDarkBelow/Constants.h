#ifndef GAME_CONSTANTS
#define GAME_CONSTANTS

#include "SFML/System/Vector2.hpp"

namespace DarkBelow {
	namespace Constants {
		namespace Game {
			const sf::Vector2f GRAVITY = { 0.f, 50.f };
			const float TERMINAL_VELOCITY = 400.f;
		}

		namespace Player {
			const sf::Vector2f SPEED = { 50.f, 50.f };
			const sf::Vector2f SCALE = { 1.f, 1.f };
		}
	}
}

#endif

