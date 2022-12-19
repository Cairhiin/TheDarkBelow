#include "TextureManager.h"
#include <iostream>

namespace DarkBelow {
	TextureManager::~TextureManager() {
		mTextures.clear();
	}

	void TextureManager::init() {
		sf::Texture texture;
		if (!texture.loadFromFile("image.png", sf::IntRect(0, 0, 32, 32))) {
			std::cout << "[ERROR] Cannot load texture, file not found!" << std::endl;
		}
		else {
			mTextures.emplace("playerChar", texture);
		}
	}

	bool TextureManager::addTexture(const std::string& id, const char* path, sf::IntRect sourceRect) {
		sf::Texture texture;
		if (!texture.loadFromFile(path, sourceRect)) {
			std::cout << "[ERROR] Cannot load texture, file not found!" << std::endl;
			return false;
		}

		mTextures.emplace(id, texture);
		return true;
	}

	sf::Texture TextureManager::getTexture(const std::string& id) {
		return mTextures[id];
	}
}