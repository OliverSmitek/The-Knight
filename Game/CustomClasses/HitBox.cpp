//
// Created by Oliver Šmítek on 09.07.2026.
//

#include "HitBox.h"

#include "../Managers/ColisionsManager.h"
#include "../Managers/SpriteManager.h"
#include "../Tools/ID/IDsetter.h"

HitBox::HitBox(sf::Vector2f scale, Entity* owner, sf::Vector2f offSet) : ownerOfHitBox(owner) {

    name = "hitBox" + std::to_string(IDsetter::getInstance().generateID());
    TextureManager::getInstance().setTexture("hitbox", &hitBoxSp);

    position = {0,0};
    this->scale = scale;

    this->offSet = offSet;
    this->truOffSet = offSet;

    type = HitBoxType::Unknown;
};


void HitBox::drawHitBox(sf::RenderWindow* window) {
    SpriteManager::getInstance().drawSprite(&hitBoxSp,position.x + offSet.x,position.y + offSet.y, *window);
}

void HitBox::transformHitBox() {
    offSetHitBox();
    SpriteManager::getInstance().hitBoxTransformation(&hitBoxSp, scale);
}

void HitBox::updateHitBox() {
    this->position = ownerOfHitBox->position;
    transformHitBox();
};

void HitBox::offSetHitBox() {
    if (truOffSet.x > 0 ) {
        if (ownerOfHitBox->facingDirection == "left") {
            offSet.x = - abs(offSet.x);
        }
        else if (ownerOfHitBox->facingDirection == "right") {
            offSet.x = abs(offSet.x);
        }
    }
    else if (truOffSet.x < 0 ) {
        if (ownerOfHitBox->facingDirection == "left") {
            offSet.x = abs(offSet.x);
        }
        else if (ownerOfHitBox->facingDirection == "right") {
            offSet.x = - abs(offSet.x);
        }
    }

    if (truOffSet.y < 0 ) {
        offSet.y = - abs(offSet.x);
    }
}

AttackHitBox::AttackHitBox(bool canBePerryd, bool canPerry, int damage, sf::Vector2f scale, Entity* owner, float lifeTimeInMs, sf::Vector2f offSet, bool intaraptebul): HitBox(scale, owner, offSet) {
    this->canBePerryd = canBePerryd;
    this->canPerry = canPerry;
    this->damage = damage;
    type = HitBoxType::Attacking;
    this->lifeTimeInMs = lifeTimeInMs;
    this->intaraptebul = intaraptebul;
}

ResevingHitBox::ResevingHitBox(sf::Vector2f scale, Entity* owner, sf::Vector2f offSet, bool colideable) : HitBox(scale, owner, offSet) {
    type = HitBoxType::Reseving;
    infinitLifeTime = true;
    this->colideable = colideable;
}


