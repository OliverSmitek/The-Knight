//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "EntityManager.h"



void EntityManager::update(SpriteManager& spriteManager, sf::RenderWindow& window) {
    for (auto& [nameOfEntity, entity]: uMOfEntitys) {
        entity -> update(spriteManager, window);
    }
}