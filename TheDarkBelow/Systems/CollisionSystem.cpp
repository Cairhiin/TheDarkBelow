#include "CollisionSystem.h"

#include <iostream>

#include "../Components/Collision.h"
#include "../Components/Transform.h"
#include "../Components/RigidBody.h"
#include "../ECS/Coordinator.h"
#include "../Constants.h"

extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	namespace ECS {
        CollisionSystem::CollisionSystem() : spatialHash(std::make_unique<SpatialHash>()) {}

		void CollisionSystem::init() {

		}

        void CollisionSystem::update() {
            spatialHash->CreateSpatialHash(mEntities);
            for (auto& entity : mEntities) {
                auto& collider = gCoordinator.GetComponent<Collision>(entity);
                auto& transform = gCoordinator.GetComponent<Transform>(entity);
                collider.hitbox.left = transform.position.x;
                collider.hitbox.top = transform.position.y;
                
                if (
                    collider.tag != Constants::Level::PLAYER && 
                    collider.tag != Constants::Level::MONSTER &&
                    collider.tag != Constants::Level::PROJECTILE
                ) continue;

                std::vector<Entity> closeEntities;
                closeEntities = spatialHash->GetSurroundingCellsEntities(transform.position);
                for (auto const& closeEntity : closeEntities) {
                    auto const& closeCollider = gCoordinator.GetComponent<Collision>(closeEntity);
                    auto const& closeTransform = gCoordinator.GetComponent<Transform>(closeEntity);

                    if (collider.hitbox.intersects(closeCollider.hitbox)) {                   
                        if (gCoordinator.GetComponent<Collision>(closeEntity).tag == Constants::Level::GROUND_TILE_3 ||
                            gCoordinator.GetComponent<Collision>(closeEntity).tag == Constants::Level::GROUND_TILE_4) {
                            std::cout << "PENETRATION: " << (collider.hitbox.top + collider.hitbox.height) - closeCollider.hitbox.top << std::endl;
                            auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
                            if (rigidBody.velocity.y > 0.f || rigidBody.velocity.y < 0.f) {
                                rigidBody.velocity.y = 0.f;
                            }
                            if (rigidBody.velocity.x > 0.f || rigidBody.velocity.x < 0.f) {
                                rigidBody.velocity.x = 0.f;
                            }
                            rigidBody.acceleration.y = 0.f;
                            collider.onSolidGround = true;
                        }
                        else {
                            collider.onSolidGround = false;
                        }
                    }
                }
            }
		}
	}
}
