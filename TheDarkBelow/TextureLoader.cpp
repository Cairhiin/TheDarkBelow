#include "TextureLoader.h"
#include <iostream>

namespace DarkBelow {
    void TextureLoader::init() {
        this->addTexture("playerCharIdle", "images/player/idle.png");
        this->addTexture("playerCharRun", "images/player/run.png");
        this->addTexture("playerCharAttack_1", "images/player/attack_1.png");
    }

    std::shared_ptr<sf::Texture> TextureLoader::getTexture(const std::string& name) {
		if (mTextures.find(name) != mTextures.end()) {
            return mTextures.find(name)->second;
        }
        else {
            return nullptr;
        }
	}

    bool TextureLoader::addTexture(const std::string& name, const std::string& path) {
        auto it = mTextures.find(name);
        if (it != mTextures.end()) return false;
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        if (texture->loadFromFile(path)) {
            mTextures.emplace(name, texture);
            return true;
        }
        return false;
    }
}