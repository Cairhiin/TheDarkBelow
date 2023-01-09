#include "PhysicsSystem.h"
#include "../ECS/Coordinator.h"
#include "../Components/RigidBody.h"
#include "../Components/Transform.h"
#include "../Components/Gravity.h"
#include "../Constants.h"

extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		void PhysicsSystem::init() {

		}

		void PhysicsSystem::update(float dt) {
			for (auto const& entity : mEntities) {
				auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
				auto& transform = gCoordinator.GetComponent<Transform>(entity);
				auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);

				transform.position += rigidBody.velocity * dt;
				//rigidBody.velocity += gravity.force * dt;

				if (rigidBody.velocity.y >= Constants::Game::TERMINAL_VELOCITY) {
					rigidBody.velocity.y = Constants::Game::TERMINAL_VELOCITY;
				}
			}
		}
	}
}