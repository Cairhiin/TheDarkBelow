#include "PlayerControlSystem.h"

#include <iostream>

#include "../ECS/Coordinator.h"
#include "../Components/RigidBody.h"
#include "../Components/Collision.h"
#include "../Constants.h"

extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		void PlayerControlSystem::init(Entity Player) {
			mPlayer = Player;
		}

		void PlayerControlSystem::update(sf::Event event) {
			auto& rigidBody = gCoordinator.GetComponent<RigidBody>(mPlayer);
			auto& collider = gCoordinator.GetComponent<Collision>(mPlayer);

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					mMovingUp = /* false */ true;
				}
				if (event.key.code == sf::Keyboard::S) {
					mMovingDown = /* false */ true;
				}
				if (event.key.code == sf::Keyboard::A /* && collider.onSolidGround */) {
					mMovingLeft = true;
				}
				if (event.key.code == sf::Keyboard::D /* && collider.onSolidGround */) {
					mMovingRight = true;
				}
				if (event.key.code == sf::Keyboard::Space && collider.onSolidGround) {
					rigidBody.velocity.y = Constants::Player::JUMP_FORCE.y;
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

			// Temporary to test collision
			if (mMovingUp) {
				rigidBody.velocity.y = -Constants::Player::SPEED.y;
			}
			else if (mMovingDown) {
				rigidBody.velocity.y = Constants::Player::SPEED.y;
			}
			else {
				rigidBody.velocity.y = 0.f;
			}
		}
	}
}