#ifndef ANIMATION_DATA
#define ANIMATION_DATA

#include <array>
#include "SFML/Graphics/Rect.hpp"
#include "Constants.h"

namespace DarkBelow {
	struct AnimationData {
		size_t frames;
		size_t offset;
		Constants::AnimationType type;
		std::array<sf::IntRect, 10> sourceRect;
		bool playsContinuously = false;
		bool isPriorityAnimation = false;
	};
}

#endif 

