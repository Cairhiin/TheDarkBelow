#include "SpatialHash.h"

#include <iostream>
#include <math.h>

#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Constants.h"

extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	void SpatialHash::CreateSpatialHash(const std::set<ECS::Entity>& colliders) {
		float cellSize = Constants::Level::SPATIAL_HASH_CELL_SIZE;
		int numberOfColumns = Constants::Level::SPATIAL_HASH_COLUMNS;
		int numberOfRows = Constants::Level::SPATIAL_HASH_ROWS;
		int numberOfCells = numberOfColumns * numberOfRows;

		this->spatialHash.clear();
		std::vector<ECS::Entity> bucket{};
		for (int i = 0; i < numberOfColumns * numberOfRows; ++i) {
			this->spatialHash[i] = bucket;
		}

		for (auto const& collider : colliders) {
			sf::Vector2f position = gCoordinator.GetComponent<ECS::Transform>(collider).position;
			int cell = this->CalculateCellNumber(position);
			this->spatialHash.at(cell).push_back(collider);
		}
	}

	std::vector<ECS::Entity> SpatialHash::GetSurroundingCellsEntities(const sf::Vector2f& position) {
		std::vector<ECS::Entity> surroundingEntities;
		int numberOfColumns = Constants::Level::SPATIAL_HASH_COLUMNS;
		int numberOfRows = Constants::Level::SPATIAL_HASH_ROWS;
		int cell = this->CalculateCellNumber(position);
		int rowNumber = static_cast<int>(floor(cell / numberOfColumns));
		int columnNumber = cell % numberOfColumns;

		for (int row = 0; row < 3; ++row) {
			if ((row - 1 + rowNumber) < 0 || (row - 1 + rowNumber) >= numberOfRows) continue;
			for (int column = 0; column < 3; ++column) {
				if ((column - 1 + columnNumber) < 0 || column - 1 + columnNumber >= numberOfColumns) continue;
				surroundingEntities.insert(
					surroundingEntities.end(), 
					this->spatialHash.at((rowNumber + row - 1) * numberOfColumns + columnNumber + column - 1).begin(),
					this->spatialHash.at((rowNumber + row - 1) * numberOfColumns + columnNumber + column - 1).end()
				);
			}
		}

		return surroundingEntities;
	}

	int SpatialHash::CalculateCellNumber(const sf::Vector2f& position) {
		float cellSize = Constants::Level::SPATIAL_HASH_CELL_SIZE;
		int numberOfColumns = Constants::Level::SPATIAL_HASH_COLUMNS;

		int column = static_cast<int>(floor(position.x / cellSize));
		int row = static_cast<int>(floor(position.y / cellSize));

		return column + row * numberOfColumns;
	}
}
