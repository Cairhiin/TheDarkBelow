#ifndef ENTITY_CREATOR
#define ENTITY_CREATOR

#include <vector>
#include <memory>
#include <set>
#include "SFML/Graphics/Texture.hpp"
#include "ECS/Types.h"
#include "Constants.h"

namespace DarkBelow {
	class EntityCreator {
	public:
		static ECS::Entity& CreatePlayerEntity();
		static ECS::Entity& CreateMonsterEntity(
			Constants::Monster::MonsterType type, 
			size_t level = 1, 
			bool isBoss = false
		);
		static std::set<Constants::Monster::Modifier> GetBossModifiers(int level);
	};
}

#endif

