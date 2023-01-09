#ifndef SPATIAL_HASH
#define SPATIAL_HASH

#include <unordered_map>
#include <set>
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "ECS/Types.h"

namespace DarkBelow {
	class SpatialHash {
	public:
		void CreateSpatialHash(const std::set<ECS::Entity>& colliders);
		std::vector<ECS::Entity> GetSurroundingCellsEntities(const sf::Vector2f& position);
		int CalculateCellNumber(const sf::Vector2f& position);

	private:
		std::unordered_map<int, std::vector<ECS::Entity>> spatialHash;
	};
}


#endif