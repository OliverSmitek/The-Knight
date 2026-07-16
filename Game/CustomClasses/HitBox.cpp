//
// Created by Oliver Šmítek on 09.07.2026.
//

#include "HitBox.h"

#include "../Managers/ColisionsManager.h"
#include "../Managers/SpriteManager.h"
#include "../Tools/ID/IDsetter.h"

HitBox::HitBox(sf::Vector2f scale, Entity* owner) : ownerOfHitBox(owner) {

    std::string name = "hitBox" + std::to_string(IDsetter::getInstance().generateID());
    TextureManager::getInstance().setTexture("HitBox", &hitBoxSp);

    position = {0,0};
    this->scale = scale;

    type = HitBoxType::Unknown;

    ColisionsManager::getInstance().insetHitBoxTouMOfHitBoxs(this);
};


void HitBox::drawHitBox(sf::RenderWindow* window) {
        SpriteManager::getInstance().drawSprite(&hitBoxSp,position.x,position.y, *window);
}

void HitBox::transformHitBox() {
    SpriteManager::getInstance().hitBoxTransformation(&hitBoxSp, scale);
}

void HitBox::updateHitBox() {
    this->position = ownerOfHitBox->position;
    transformHitBox();
};

AttackHitBox::AttackHitBox(bool canBePerryd, bool canPerry, int damage, sf::Vector2f scale, Entity* owner, float lifeTimeInMs): HitBox(scale, owner) {
    this->canBePerryd = canBePerryd;
    this->canPerry = canPerry;
    this->damage = damage;
    type = HitBoxType::Attacking;
    this->lifeTimeInMs = lifeTimeInMs;
}

ResevingHitBox::ResevingHitBox(sf::Vector2f scale, Entity* owner) : HitBox(scale, owner) {

    type = HitBoxType::Reseving;
    infinitLifeTime = true;
}


