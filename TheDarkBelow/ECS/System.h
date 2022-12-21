#ifndef ECS_SYSTEM
#define ECS_SYSTEM

#include <set>
#include "Types.h"

namespace DarkBelow {
	namespace ECS {
		// Source: https://code.austinmorlan.com/austin/2019-ecs/
		class System {
		public:
			std::set<Entity> mEntities;
		};
	}
}
#endif 

