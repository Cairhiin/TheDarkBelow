#ifndef BOSS_COMPONENT
#define BOSS_COMPONENT

#include <set>
#include "../Constants.h"

namespace DarkBelow {
	namespace ECS {
		struct Boss {
			std::set<Constants::Monster::Modifier> modifiers;
		};
	}
}

#endif 

