#ifndef ANIMATION_DATA
#define ANIMATION_DATA

#include <array>
#include "SFML/Graphics/Rect.hpp"

namespace DarkBelow {
	enum AnimationType {
		IDLE,
		ATTACK_1,
		TAKE_HIT,
		DEATH,
		RUN
	};
	struct AnimationData {
		size_t frames;
		size_t offset;
		AnimationType type;
		std::array<sf::IntRect, 10> hitboxRectPerFrame;
		bool playsContinuously = false;
		bool isPriorityAnimation = false;
	};
}

#endif 

