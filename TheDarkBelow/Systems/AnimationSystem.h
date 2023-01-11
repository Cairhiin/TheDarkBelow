#ifndef ANIMATION_SYSTEM
#define ANIMATION_SYSTEM

#include "../ECS/System.h"
#include "../ECS/Coordinator.h"

extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		class AnimationSystem : public System {
			void init();
			void update(float dt);
		};
	}
}


#endif

