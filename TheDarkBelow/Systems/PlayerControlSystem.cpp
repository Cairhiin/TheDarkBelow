#include "PlayerControlSystem.h"
#include "../ECS/Coordinator.h"
#include "../Constants.h"

extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		void PlayerControlSystem::init(Entity Player) {
			mPlayer = Player;
		}

		void PlayerControlSystem::update(sf::Event event) {
			auto& rigidBody = gCoordinator.GetComponent<RigidBody>(mPlayer);

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					mMovingUp = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					mMovingDown = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					mMovingLeft = true;
				}
				if (event.key.code == sf::Keyboard::D) {
					mMovingRight = true;
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					mMovingUp = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					mMovingDown = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					mMovingLeft = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					mMovingRight = false;
				}
			}

			if (mMovingRight) {
				rigidBody.velocity.x = Constants::Player::SPEED.x;
			}
			else if (mMovingLeft) {
				rigidBody.velocity.x = -Constants::Player::SPEED.x;
			}
			else {
				rigidBody.velocity.x = 0.f;
			}
		}
	}
}