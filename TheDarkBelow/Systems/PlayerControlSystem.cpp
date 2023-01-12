#include "PlayerControlSystem.h"

#include <iostream>

#include "../ECS/Coordinator.h"
#include "../Components/RigidBody.h"
#include "../Components/Collision.h"
#include "../Components/Animation.h"
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
			auto& animComponent = gCoordinator.GetComponent<Animation>(mPlayer);

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					animComponent.animation.type = Constants::RUN;
					mMovingUp = /* false */ true;
				}
				if (event.key.code == sf::Keyboard::S) {
					animComponent.animation.type = Constants::RUN;
					mMovingDown = /* false */ true;
				}
				if (event.key.code == sf::Keyboard::A /* && collider.onSolidGround */) {
					animComponent.animation.type = Constants::RUN;
					mMovingLeft = true;
				}
				if (event.key.code == sf::Keyboard::D /* && collider.onSolidGround */) {
					animComponent.animation.type = Constants::RUN;
					mMovingRight = true;
				}
				if (event.key.code == sf::Keyboard::Space && collider.onSolidGround) {
					rigidBody.velocity.y = Constants::Player::JUMP_FORCE.y;
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					animComponent.animation.type = Constants::IDLE;
					mMovingUp = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					animComponent.animation.type = Constants::IDLE;
					mMovingDown = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					animComponent.animation.type = Constants::IDLE;
					mMovingLeft = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					animComponent.animation.type = Constants::IDLE;
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