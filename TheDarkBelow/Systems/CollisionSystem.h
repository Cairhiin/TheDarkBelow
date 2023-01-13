#ifndef COLLISION_SYSTEM
#define COLLISION_SYSTEM

#include <memory>
#include "../ECS/System.h"
#include "SFML/Graphics/Rect.hpp"
#include "../SpatialHash.h"

namespace DarkBelow {
	namespace ECS {
		class CollisionSystem : public System {
		public:
			CollisionSystem();
			void init();
			void update();

		private:
			std::unique_ptr<SpatialHash> spatialHash;
		};
	}
}
#endif

