#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include <SFML/Graphics/Texture.hpp>
#include <map>

namespace DarkBelow {
	class TextureManager {
	public:
		TextureManager() = default;
		~TextureManager();
		
		void init();
		bool addTexture(const std::string&, const char* path, sf::IntRect sourceRect);
		sf::Texture getTexture(const std::string& id);

	private:
		std::map<const std::string&, sf::Texture> mTextures;
	};
}

#endif

