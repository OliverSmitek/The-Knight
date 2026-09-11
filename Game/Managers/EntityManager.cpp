//
// Created by Oliver Šmítek on 25.11.2025.
//
#include "EntityManager.h"
#include "../Entities/Entity.h"
#include "../Managers/EnvironmenAndPhysicsManager.h"
#include <cmath>

#include "ColisionsManager.h"
#include "../GameManager.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "../Entities/souls/Soul.h"


void EntityManager::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {

    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->update(window, environmenAndPhysicsManager);
    }
    ColisionsManager::getInstance().updateAndChackForHitBoxes(&window);
    chackHowLongToFreez();
    SpriteManager::getInstance().resetAnimationTimer();
    killEntities();
}



sf::Vector2f EntityManager::getPositionOfEntity(std::string nameOfEntity) {
    return uMOfEntitys.at(nameOfEntity)->position;
}

sf::Vector2f EntityManager::getVelocityOfEntity(std::string nameOfEntity) {
    return uMOfEntitys.at(nameOfEntity)->getVelocity();
}


bool EntityManager::getAttacIsActiveBool(std::string nameOfEntity) {
    return uMOfEntitys.at(nameOfEntity)->attackHitBoxIsActive;
}




void EntityManager::freezTheGame(int damage) {
    if(gameIsFreezd) return;

    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->freeze = true;
    }
    gameIsFreezd = true;
    timerFreez.restart();
    freezTime = damage;
}

void EntityManager::unFreezTheGame() {
    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->freeze = false;
    }
    gameIsFreezd = false;
}

void EntityManager::chackHowLongToFreez() {
    if (gameIsFreezd) {
        if (timerFreez.getElapsedTime().asMilliseconds() > freezTime) {
            unFreezTheGame();
        }
    }
}

sf::Sprite *EntityManager::getSpriteOfEntity(std::string nameOfEntity) {
    return &uMOfEntitys.at(nameOfEntity)->getSpriteOfEntity();
}


void EntityManager::killEntity(std::string nameOfEntity, Entity *entityToKill) {
    uMOfEntitysToKill[nameOfEntity] = entityToKill;
}

void EntityManager::killEntities() {
    for (auto &[name, entityPtr]: uMOfEntitysToKill) {
        ColisionsManager::getInstance().getRidOfHitBoxsOfOwner(entityPtr);
        auto it = uMOfEntitys.find(name);
        if (it != uMOfEntitys.end()) {
            delete it->second; // uvolní paměť entity
            uMOfEntitys.erase(it);
        }
    }
    uMOfEntitysToKill.clear();
}




void EntityManager::colisionDetection(std::string nameOfEntity) {

}


    void EntityManager::shadowColisionDetection(sf::Vector2f  &shadowPos, std::string name, sf::Vector2f positionOfPlayer) {
        for (auto &[nameOfEntityInMOE, entityColided]: uMOfEntitys) {

            // Can't collide with itself
            if(name.compare(entityColided->name) == 0) continue;

            // Can't collide with intangible entity
            if(entityColided->collidable == false) continue;

            if (positionOfPlayer.y >= entityColided->collisionHitBox.getPosition().y) continue;

            if (shadowPos.x <= entityColided->collisionHitBox.getPosition().x + entityColided->collisionHitBox.getGlobalBounds().width/2
                &&
                entityColided->collisionHitBox.getPosition().x - entityColided->collisionHitBox.getGlobalBounds().width/2 <= shadowPos.x) {
                shadowPos.y = entityColided->position.y - entityColided->collisionHitBox.getGlobalBounds().height + 4;

                }
        }
    }



