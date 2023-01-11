#include "TextureLoader.h"
#include <iostream>

namespace DarkBelow {
	TextureLoader::~TextureLoader() {
		for (auto& texture : mTextures) {
			delete &texture;
		}
	}

	sf::Texture* TextureLoader::getTexture(const std::string& name) {
		if (mTextures.find(name) != mTextures.end()) {
			return mTextures[name];
		}
		return nullptr;
	}

    sf::Texture* TextureLoader::loadTexture(const std::string& name, const std::string& path) {
        sf::Texture* texture = new sf::Texture();
        if (texture->loadFromFile(path)) {
            mTextures[name] = texture;
            return texture;
        } else {
            delete texture;
            return nullptr;
        }
    }

	sf::Texture* TextureLoader::getTexture(const std::string& id) {
		return mTextures[id];
	}
}