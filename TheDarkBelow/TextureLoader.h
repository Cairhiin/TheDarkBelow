#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <map>

namespace DarkBelow {
	class TextureLoader {
	public:
		TextureLoader() = default;
		void init();
		std::shared_ptr<sf::Texture> getTexture(const std::string& name);
		bool addTexture(const std::string& name, const std::string& path);

	private:
		std::map<const std::string, std::shared_ptr<sf::Texture>> mTextures;
	};
}

#endif

