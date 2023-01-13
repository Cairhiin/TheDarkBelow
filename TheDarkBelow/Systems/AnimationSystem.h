#ifndef ANIMATION_SYSTEM
#define ANIMATION_SYSTEM

#include "../ECS/System.h"
#include "../ECS/Coordinator.h"
#include "../Components/Animation.h"

extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		class AnimationSystem : public System {
		public:
			void init();
			void update(float dt);

		private:
			float timer;
		};
	}
}


#endif

