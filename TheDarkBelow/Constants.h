#ifndef GAME_CONSTANTS
#define GAME_CONSTANTS

#include "SFML/System/Vector2.hpp"

namespace DarkBelow {
	namespace Constants {
		namespace Game {
			const sf::Vector2f GRAVITY = { 0.f, 200.f };
			constexpr float TERMINAL_VELOCITY = 800.f;
		}

		namespace Player {
			const sf::Vector2f SPEED = { 100.f, 100.f };
			const sf::Vector2f SCALE = { 1.f, 1.f };
			const sf::Vector2f JUMP_FORCE = { 0.f, -200.f };
		}

		namespace Level {
			const sf::Vector2i TILE_SIZE = { 16, 16 };
			const sf::Vector2f SCALE = { 2.f, 2.f };
			const enum TileNames {
				PLAYER,
				GROUND_TILE_1,
				GROUND_TILE_2,
				GROUND_TILE_3,
				GROUND_TILE_4,
				GROUND_TILE_5,
				GROUND_TILE_6,
				WALL_TILE_1,
				WALL_TILE_2,
				WALL_TILE_3,
				WALL_TILE_4,
				CEILING_TILE_1,
				CEILING_TILE_2,
				CEILING_TILE_3,
				CEILING_TILE_4,
				MONSTER,
				PROJECTILE,
			};
		}
	}
}

#endif

