#ifndef COLLISION_SYSTEM
#define COLLISION_SYSTEM

#include <memory>
#include "../ECS/System.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector3.hpp"
#include "../SpatialHash.h"

namespace DarkBelow {
	namespace ECS {
		class CollisionSystem : public System {
		public:
			CollisionSystem();
			void init();
			void update();
			
			sf::Vector3f getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal);
			sf::Vector2f resolve(const sf::Vector3f& manifold);

		private:
			std::unique_ptr<SpatialHash> spatialHash;
		};
	}
}
#endif

