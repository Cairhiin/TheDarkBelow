#include "PhysicsSystem.h"
#include "../ECS/Coordinator.h"
#include "../Components/RigidBody.h"
#include "../Components/Transform.h"

extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
		void PhysicsSystem::init() {

		}

		void PhysicsSystem::update(float dt) {
			for (auto const& entity : mEntities) {
				auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
				auto& transform = gCoordinator.GetComponent<Transform>(entity);

				transform.position += rigidBody.velocity * dt;
			}
		}
	}
}