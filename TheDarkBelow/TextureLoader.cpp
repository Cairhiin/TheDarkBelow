#include "TextureLoader.h"
#include <iostream>

namespace DarkBelow {
	sf::Texture TextureLoader::getTexture(const std::string& name) {
		if (mTextures.find(name) != mTextures.end()) {
			return mTextures[name];
		}
	}

    sf::Texture TextureLoader::loadTexture(const std::string& name, const std::string& path) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            mTextures[name] = texture;
            return texture;
        } 
    }
}