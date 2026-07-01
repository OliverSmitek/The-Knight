//
// Created by Oliver Šmítek on 01.07.2026.
//

#include "Soul.h"

Soul::Soul(sf::Vector2f position, std::string name, std::string nameOfTexture) : Entity(position, {0,0}, name) {
    isSoul = true;
    float x = 2.2f;
    float y = 2.2f;

    trueScale = sf::Vector2f(x, y);
    //Docasne:{


    setTexture(nameOfTexture);

    hitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);
    //docasne}

    scale = sf::Vector2f(x, y);
    facingDirection = "right";
}

void Soul::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {


    if (!freeze) {
        transformationSprite(currentTexture);
    }
    hitBoxUpdateposition();

    if (!freeze) {
        movmentUpdate();
    }
}

void Soul::hitBoxUpdateposition() {
    collisionHitBox.setPosition(collisionBoxPosition);
    hitBox.setPosition(hitBoxPosition);
    attackHitBox.setPosition(attackHitBoxPosition);
}

void Soul::movmentUpdate() {
    position.x += velocity.x;
    hitBoxPosition.x += velocity.x;

    position.y += velocity.y;
    hitBoxPosition.y += velocity.y;
}

void Soul::drawHitbox(sf::RenderWindow &window) {
    spriteManager->getInstance().drawSprite(&hitBox, hitBoxPosition.x,  hitBoxPosition.y, window);
}

void Soul::passivActionDie() {
    EntityManager::getInstance().killEntity(name,this);
}
