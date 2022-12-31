#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

namespace DarkBelow {
	class Map {
	public:
		Map() = default;
		Map(const std::string& textureID, sf::Vector2f scale, sf::Vector2i tileSize);
		void Load();
		void AddTile(float x, float y);
		void AddCollision(float x, float y, const std::string& tag);

	private:
		std::string mTextureId;
		sf::Vector2f mScale;
		sf::Vector2i mTileSize;
		sf::Texture	mTexturePlatform;
		sf::Sprite mSpritePlatform;
	};
}

#endif

