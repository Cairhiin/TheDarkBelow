#ifndef ANIMATION_COMPONENT
#define ANIMATION_COMPONENT

#include "../Constants.h"
#include "../Animation.h"

namespace DarkBelow {
	namespace ECS {
		struct Animation {
			AnimationData animation;
			size_t speed;		
		};
	}
}

#endif

