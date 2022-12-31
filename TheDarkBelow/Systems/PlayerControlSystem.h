#ifndef PLAYER_CONTROL_SYSTEM
#define PLAYER_CONTROL_SYSTEM

#include "SFML/Window/Event.hpp"
#include "../ECS/System.h"
#include "../Components/RigidBody.h"

namespace DarkBelow {
	namespace ECS {
		class PlayerControlSystem : public System {
		public:
			void init(Entity Player);
			void update(sf::Event event);

		private:
			Entity mPlayer;
			bool mMovingUp = false;
			bool mMovingDown = false;
			bool mMovingRight = false;
			bool mMovingLeft = false;
		};
	}
}

#endif

