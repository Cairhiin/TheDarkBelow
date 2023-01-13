#include "PlayerControlSystem.h"

#include <iostream>

#include "../ECS/Coordinator.h"
#include "../Components/RigidBody.h"
#include "../Components/Collision.h"
#include "../Components/Animation.h"
#include "../Components/Transform.h"
#include "../Constants.h"
#include "../Animation.h"

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
			auto& transform = gCoordinator.GetComponent<Transform>(mPlayer);

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					animComponent.animation.type = AnimationType::RUN;
					mMovingUp = /* false */ true;
				}
				if (event.key.code == sf::Keyboard::S) {
					animComponent.animation.type = AnimationType::RUN;
					mMovingDown = /* false */ true;
				}
				if (event.key.code == sf::Keyboard::A /* && collider.onSolidGround */) {
					animComponent.animation.type = AnimationType::RUN;
					transform.scale = { -2.f, 2.f };
					mMovingLeft = true;
				}
				if (event.key.code == sf::Keyboard::D /* && collider.onSolidGround */) {
					animComponent.animation.type = AnimationType::RUN;
					transform.scale = { 2.f, 2.f };
					mMovingRight = true;
				}
				if (event.key.code == sf::Keyboard::Space && collider.onSolidGround) {
					rigidBody.velocity.y = Constants::Player::JUMP_FORCE.y;
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					animComponent.animation.type = AnimationType::IDLE;
					mMovingUp = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					animComponent.animation.type = AnimationType::IDLE;
					mMovingDown = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					animComponent.animation.type = AnimationType::IDLE;
					mMovingLeft = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					animComponent.animation.type = AnimationType::IDLE;
					mMovingRight = false;
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				animComponent.animation.type = AnimationType::ATTACK_1;
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