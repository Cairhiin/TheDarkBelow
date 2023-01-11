#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <SFML/Graphics/Texture.hpp>
#include <map>

namespace DarkBelow {
	class TextureLoader {
	public:	
		~TextureLoader();
		TextureLoader(const TextureLoader&) = delete;
		TextureLoader& operator=(const TextureLoader&) = delete;
		sf::Texture* getTexture(const std::string& name);
		sf::Texture* loadTexture(const std::string& name, const std::string& path);

	private:
		std::map<const std::string, sf::Texture*> mTextures;
	};
}

#endif

