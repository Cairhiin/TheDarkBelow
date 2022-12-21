#include "TextureLoader.h"
#include <iostream>

namespace DarkBelow {
	void TextureLoader::init() {
		sf::Texture texture;
		if (!texture.loadFromFile("images/knight_idle.png")) {
			std::cout << "[ERROR] Cannot load texture, file not found!" << std::endl;
		}
		else {
			mTextures.emplace("playerChar", texture);
		}
	}

	bool TextureLoader::addTexture(const std::string& id, const char* path, sf::IntRect sourceRect) {
		sf::Texture texture;
		if (!texture.loadFromFile(path, sourceRect)) {
			std::cout << "[ERROR] Cannot load texture, file not found!" << std::endl;
			return false;
		}

		mTextures.emplace(id, texture);
		return true;
	}

	sf::Texture TextureLoader::getTexture(const std::string& id) {
		return mTextures[id];
	}
}