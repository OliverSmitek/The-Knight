//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "SpriteManager.h"



void SpriteManager::drawSprite(sf::Sprite *sprite, float x, float y, sf::RenderWindow& window) {
    sprite->setPosition(x,y);
    window.draw(*sprite);
}

