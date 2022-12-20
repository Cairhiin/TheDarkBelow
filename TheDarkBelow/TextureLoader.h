#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <SFML/Graphics/Texture.hpp>
#include <map>

namespace DarkBelow {
	class TextureLoader {
	public:	
		void init();
		bool addTexture(const std::string& id, const char* path, sf::IntRect sourceRect);
		sf::Texture getTexture(const std::string& id);

	private:
		std::map<const std::string, sf::Texture> mTextures;
	};
}

#endif

