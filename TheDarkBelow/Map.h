#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "Constants.h"

namespace DarkBelow {
	class Map : public sf::Drawable, sf::Transformable {
	public:
		Map() = default;
		Map(const std::string& textureID, sf::Vector2f scale, sf::Vector2i tileSize);
		void Load();
		sf::Vector2f GetTextureCoordinates(int tile);
		void AddCollision(float x, float y, Constants::Level::TileNames tileName);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::string		mTextureId;
		sf::Vector2f	mScale;
		sf::Vector2i	mTileSize;
		sf::VertexArray mVertices;
		sf::Texture		mTileset;
	};
}

#endif

