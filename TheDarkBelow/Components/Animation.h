#ifndef ANIMATION_COMPONENT
#define ANIMATION_COMPONENT

namespace DarkBelow {
	enum AnimationType {
		IDLE,
		ATTACK,
		TAKE_HIT,
		DEATH,
		RUN
	};
	namespace ECS {
		struct Animation {
			AnimationType type = AnimationType::IDLE;
			size_t frames;
			size_t speed;
			bool playsContinuously = false;
			bool isPriorityAnimation = false;
		};
	}
}

#endif

