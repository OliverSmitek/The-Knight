//
// Created by Oliver Šmítek on 16.12.2025.
//

#include "TextureManager.h"


TextureManager::TextureManager() {

    sf::Texture texture;
    if (!texture.loadFromFile("../../textures/_Idle.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["idleKnight"] = texture;

    if (!texture.loadFromFile("../../textures/_Run.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    textures["runKnight"] = texture;

}


void TextureManager::setTexture(std::string nameOfTexture, sf::Sprite *spriteToInsertTo) {
    spriteToInsertTo->setTexture(textures.at(nameOfTexture));
}

