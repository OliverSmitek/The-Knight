//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "Entity.h"
#include "../Managers/SpriteManager.h"
#include "../Insetors/InsertEntity.h"

//vytvor zasedne zkrze entitiyFactory!
Entity::Entity(sf::Vector2f position, sf::Vector2f velocity, std::string nameSpace, InsertEntity *insert){
  this->position = position;
  this->velocity = velocity;

  insert->insertEntity(nameSpace, this);

};

void Entity::drawEntity(SpriteManager& spriteManager, sf::RenderWindow& window) {
  spriteManager.drawSprite(&sprite, position.x, position.y, window);
};

void Entity::update(SpriteManager& spriteManager, sf::RenderWindow& window){};
