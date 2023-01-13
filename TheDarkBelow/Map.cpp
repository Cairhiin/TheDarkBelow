#include "Map.h"

#include <array>
#include <iostream>
#include <fstream>

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/Collision.h"
#include "TextureLoader.h"

extern DarkBelow::TextureLoader gTextureLoader;
extern DarkBelow::ECS::Coordinator gCoordinator;

namespace DarkBelow {
	Map::Map(const std::string& textureID, sf::Vector2f scale, sf::Vector2i tileSize)
		: mTextureId(textureID), mScale(scale), mTileSize(tileSize) {}

	 void Map::Load() {
		mTileset = gTextureLoader.loadTexture(mTextureId, "images/main_lev_build_1.png");
		this->setScale(this->mScale);	
		
		mVertices.setPrimitiveType(sf::Quads);
		mVertices.resize(3200);
		std::string fileName = "assets/act1_level1.txt";
		std::fstream levelData{ fileName };
		
		if (!levelData.is_open()) {
			std::cout << "failed to open " << fileName << '\n';
		} else {
			int x = 0;
			int y = 0;
			while (levelData) {
				char firstDigit = levelData.get();
				if (firstDigit == ' ' || firstDigit == -1) continue;
				if (firstDigit == '\n') {
					++y;
					x = 0;
					continue;
				}
				char secondDigit = levelData.get();
				std::string tile =	std::to_string(firstDigit - '0') + 
									std::to_string(secondDigit - '0');
				int tileType = std::stoi(tile);
				
				// Setting the position of the corners
				sf::Vertex* quad = &mVertices[(y + x * 20) * 4];
				quad[0].position = sf::Vector2f(x * mTileSize.x, y * mTileSize.y);
				quad[1].position = sf::Vector2f((x + 1) * mTileSize.x, y * mTileSize.y);
				quad[2].position = sf::Vector2f((x + 1) * mTileSize.x, (y + 1) * mTileSize.y);
				quad[3].position = sf::Vector2f(x * mTileSize.x, (y + 1) * mTileSize.y);
				
				quad[0].texCoords = this->GetTextureCoordinates(tileType);
				quad[1].texCoords = {
					this->GetTextureCoordinates(tileType).x + mTileSize.x,
					this->GetTextureCoordinates(tileType).y
				};
				quad[2].texCoords = {
					this->GetTextureCoordinates(tileType).x + mTileSize.x,
					this->GetTextureCoordinates(tileType).y + mTileSize.y
				};
				quad[3].texCoords = {
					this->GetTextureCoordinates(tileType).x,
					this->GetTextureCoordinates(tileType).y + mTileSize.y
				};

				// Add collision component to blocking tiles
				if (tileType != 0) {
					this->AddCollision(
						static_cast<float>(x),
						static_cast<float>(y),
						static_cast<Constants::Level::TileNames>(tileType)
					);
				}
				++x;
			}
		}
	}

	 sf::Vector2f Map::GetTextureCoordinates(int tileType) {
		 float sourceX{ 0.f };
		 float sourceY{ 0.f };
		 switch (tileType) {
		 case 1:
			 sourceX = 224.f;
			 sourceY = 272.f;
			 break;
		 case 2:
			 sourceX = 240.f;
			 sourceY = 272.f;
			 break;
		 case 3:
			 sourceX = 224.f;
			 sourceY = 288.f;
			 break;
		 case 4:
			 sourceX = 240.f;
			 sourceY = 288.f;
			 break;
		 case 5:
			 sourceX = 224.f;
			 sourceY = 304.f;
			 break;
		 case 6:
			 sourceX = 240.f;
			 sourceY = 304.f;
			 break;
		 case 7:
			 sourceX = 16.f;
			 sourceY = 160.f;
			 break;
		 case 8:
			 sourceX = 32.f;
			 sourceY = 160.f;
			 break;
		 case 9:
			 sourceX = 16.f;
			 sourceY = 176.f;
			 break;
		 case 10:
			 sourceX = 32.f;
			 sourceY = 176.f;
			 break;
		 case 11:
			 sourceX = 16.f;
			 sourceY = 192.f;
			 break;
		 case 12:
			 sourceX = 32.f;
			 sourceY = 192.f;
			 break;
		 default:
			 break;
		 }

		 return sf::Vector2f(sourceX, sourceY);
	}

	void Map::AddCollision(float x, float y, Constants::Level::TileNames tileName) {
		float xPos = x * mTileSize.x * mScale.x;
		float yPos = y * mTileSize.y * mScale.y;
		auto collider = gCoordinator.CreateEntity();
		gCoordinator.AddComponent(
			collider,
			ECS::Transform{
				{ xPos, yPos },
				{ 0.f, 0.f },
				{ 1.f, 1.f }
			}
		);
		gCoordinator.AddComponent(
			collider,
			ECS::Collision{
				tileName,
				sf::FloatRect(xPos, yPos, mTileSize.x * mScale.x, mTileSize.y * mScale.y) 
			}
		);
	}

	void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= this->getTransform();
		states.texture = &mTileset;
		target.draw(mVertices, states);
	}
}