//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "Player.h"
#include "SFML/Graphics/Sprite.hpp"


Player::Player(sf::Vector2f position,sf::Vector2f velocity) : Entity(position, velocity) {
    if (!tex.loadFromFile("../../textures/_Idle.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    sprite.setTexture(tex);
};


void Player::update(SpriteManager& spriteManager, sf::RenderWindow& window){
    position.x += velocity.x;
    position.y += velocity.y;
  drawEntity(spriteManager,  window);

}