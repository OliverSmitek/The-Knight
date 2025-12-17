//
// Created by Oliver Šmítek on 16.12.2025.
//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "SFML/Graphics/Sprite.hpp"

class TextureManager {

  public:


    std::unordered_map<std::string, sf::Texture> textures; //obsahuje všechny textury hry


    TextureManager();
    void setTexture(std::string nameOfTexture, sf::Sprite* spriteToInsertTo);

};



#endif //TEXTUREMANAGER_H
