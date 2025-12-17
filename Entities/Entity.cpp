//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "Entity.h"
#include "../Managers/SpriteManager.h"
#include "../Insertors/InsertEntity.h"

//vytvor zasedne zkrze entitiyFactory!
Entity::Entity(sf::Vector2f position, sf::Vector2f velocity){
  this->position = position;
  this->velocity = velocity;
};

void Entity::drawEntity(SpriteManager& spriteManager, sf::RenderWindow& window) {
  spriteManager.drawSprite(&sprite, position.x,  position.y, window);
}


void Entity::setTexture(TextureManager& textureManager, sf::String nameOfTexture) {
  textureManager.setTexture(nameOfTexture, &sprite);
}


void Entity::update(TextureManager &textureManager, SpriteManager& spriteManager, sf::RenderWindow& window) {};

void Entity::actionWalk(TextureManager& textureManager) {};
