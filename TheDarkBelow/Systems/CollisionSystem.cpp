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

                // Offsetting Origin changes
                if (collider.tag == Constants::Level::PLAYER) {
                    collider.hitbox.left -= 54;
                    collider.hitbox.top -= 20;
                }
                
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

                    sf::FloatRect overlap; // store the overlap between the hitboxes
                    if (collider.hitbox.intersects(closeCollider.hitbox, overlap)) {  
                        Constants::Level::TileNames tag = closeCollider.tag;
                        if (closeCollider.tag == Constants::Level::PLAYER) continue;
                                          
                        auto collisionNormal = closeTransform.position - transform.position;
                        auto manifold = this->getManifold(overlap, collisionNormal);
                        transform.position.x += this->resolve(manifold).x;
                        transform.position.y += this->resolve(manifold).y;
                            
                        auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
                        if (rigidBody.velocity.y > 0.f || rigidBody.velocity.y < 0.f) {
                            rigidBody.velocity.y = 0.f;
                        }

                        if (rigidBody.velocity.x > 0.f || rigidBody.velocity.x < 0.f) {
                            rigidBody.velocity.x = 0.f;
                        }

                        if (tag == Constants::Level::GROUND_TILE_5 ||
                            tag == Constants::Level::GROUND_TILE_6) {
                            rigidBody.acceleration.y = 0.f;
                            collider.onSolidGround = true;
                        }
                        else {
                            collider.onSolidGround = false;
                        }
                       
                        break;
                    }
                }
            }
		}

        sf::Vector3f CollisionSystem::getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal) {
            sf::Vector3f manifold;

            if (overlap.width < overlap.height) {
                manifold.x = (collisionNormal.x < 0) ? 1.f : -1.f;
                manifold.z = overlap.width;
            } else {
                manifold.y = (collisionNormal.y < 0) ? 1.f : -1.f;
                manifold.z = overlap.height;
            }
            
            return manifold;
        }

        sf::Vector2f CollisionSystem::resolve(const sf::Vector3f& manifold) {
            sf::Vector2f normal(manifold.x, manifold.y);
            return normal * manifold.z;
        }
	}
}
