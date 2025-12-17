//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "Player.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Keyboard.hpp"

Player::Player(sf::Vector2f position,sf::Vector2f velocity) : Entity(position, velocity) {
    if (!tex.loadFromFile("../../textures/_Idle.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    sprite.setTexture(tex);
}

void Player::update(TextureManager &textureManager ,SpriteManager& spriteManager, sf::RenderWindow& window){
    input(textureManager);
    position.x += velocity.x;
    position.y += velocity.y;
    drawEntity(spriteManager,  window);
}

void Player::input(TextureManager &textureManager) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -10;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        actionWalk(textureManager);
    }
    else {
        velocity.x = 0;    // stop when no key is pressed
    }
}


void Player::actionWalk(TextureManager &textureManager) {
    textureManager.setTexture("runKnight",&sprite);
    velocity.x = 10;
}
