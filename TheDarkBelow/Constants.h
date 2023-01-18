#ifndef GAME_CONSTANTS
#define GAME_CONSTANTS

#include "SFML/System/Vector2.hpp"
#include "Animation.h"

namespace DarkBelow {
	namespace Constants {
		namespace Game {
			const sf::Vector2f GRAVITY = { 0.f, 200.f };
			constexpr float TERMINAL_VELOCITY = 800.f;
		}

		namespace Player {
			const sf::Vector2f SPEED = { 100.f, 100.f };
			const sf::Vector2f SCALE = { 2.f, 2.f };
			const sf::Vector2f JUMP_FORCE = { 0.f, -200.f };

			const AnimationData idleAnimation = {
				10,
				0,
				AnimationType::IDLE,
				{ sf::IntRect(0, 40, 108, 40) },
				true
			};

			const AnimationData runAnimation = {
				10,
				0,
				AnimationType::RUN,
				{ sf::IntRect(0, 40, 108, 40) }
			};

			const AnimationData attack_1_Animation = {
				4,
				0,
				AnimationType::ATTACK_1,
				{ sf::IntRect(4, 20, 105, 60) },
				false,
				true
			};
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
			constexpr float SPATIAL_HASH_CELL_SIZE = 128.f;
			constexpr int SPATIAL_HASH_COLUMNS = 10;
			constexpr int SPATIAL_HASH_ROWS = 5;
		}

		namespace Monster {
			const sf::Vector2f SPEED = { 100.f, 100.f };
			const sf::Vector2f SCALE = { 2.f, 2.f };
			const enum MonsterType {
				SKELETAL_WARRIOR,
				FLOATING_EYEBALL,
				GOBLIN,
			};
			const struct SkeletalWarrior {
				std::string name = "Skeletal Warrior";
			};
			const enum Modifier {
				EXTRA_STRONG,
				EXTRA_FAST,
				HEALTHY,
				TELEPORTER
			};
		}
	}
}

#endif

