#ifndef PHYSICS_SYSTEM
#define PHYSICS_SYSTEM

#include "../ECS/System.h"
#include "SFML/System/Time.hpp"

namespace DarkBelow {
	namespace ECS {
		class PhysicsSystem : public System {
		public:
			void init();
			void update(float dt);

		private:
		};
	}
}

#endif