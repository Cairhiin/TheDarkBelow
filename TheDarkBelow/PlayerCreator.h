#ifndef PLAYER_CREATOR
#define PLAYER_CREATOR

#include <vector>
#include <memory>
#include "SFML/Graphics/Texture.hpp"
#include "ECS/Types.h"

namespace DarkBelow {
	class PlayerCreator {
	public:
		static ECS::Entity& CreatePlayerEntity();

	};
}

#endif

