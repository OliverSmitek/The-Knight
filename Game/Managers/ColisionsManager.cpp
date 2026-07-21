//
// Created by Oliver Šmítek on 10.07.2026.
//

#include "ColisionsManager.h"

#include "../Entities/Player/Player.h"
#include "../Tools/DamageCalculator/DamageCalculation.h"

ColisionsManager::ColisionsManager() {};

void ColisionsManager::chackForHitBoxesColisions(AttackHitBox *atcHitBox, HitBox *reshitBox) {

    if (std::find(atcHitBox->listOfAttackedEntitys.begin(),
                 atcHitBox->listOfAttackedEntitys.end(),
                 reshitBox->name) != atcHitBox->listOfAttackedEntitys.end())  return;

    if (reshitBox->type == HitBoxType::Attacking) {
        AttackHitBox* attackRes = static_cast<AttackHitBox*>(reshitBox);
        if (atcHitBox->hitBoxSp.getGlobalBounds().intersects(attackRes->hitBoxSp.getGlobalBounds())){

            if (atcHitBox->canPerry && attackRes->canBePerryd) {
                atcHitBox->listOfAttackedEntitys.push_back(attackRes->name);
                if (atcHitBox->canVelicityIncreaseDamage) {
                    //perry and velocity
                    reshitBox->ownerOfHitBox->passivActionGetHit(
                        atcHitBox->ownerOfHitBox->facingDirection,
                        DamageCalculation::calculateDamageVelocityAndPerry(
                            atcHitBox->damage,
                            atcHitBox->ownerOfHitBox->velocity,
                            perryMultiplayer));
                }

                if (!atcHitBox->canVelicityIncreaseDamage) {
                    //perry
                    reshitBox->ownerOfHitBox->passivActionGetHit(
                        atcHitBox->ownerOfHitBox->facingDirection,
                        DamageCalculation::calculateDamagePerry(
                            atcHitBox->damage,
                            perryMultiplayer));
                }
            }
        }
    }

    if (reshitBox->type == HitBoxType::Reseving){
        ResevingHitBox* receiving = static_cast<ResevingHitBox*>(reshitBox);
        if (atcHitBox->hitBoxSp.getGlobalBounds().intersects(receiving->hitBoxSp.getGlobalBounds())){

            if (!receiving->invincible) {
                atcHitBox->listOfAttackedEntitys.push_back(receiving->name);

                if (atcHitBox->canVelicityIncreaseDamage) {
                    //Velocity
                    reshitBox->ownerOfHitBox->passivActionGetHit(
                        atcHitBox->ownerOfHitBox->facingDirection,
                        DamageCalculation::calculateDamageVelocity(atcHitBox->damage,atcHitBox->ownerOfHitBox->velocity));
                }
                if (!atcHitBox->canVelicityIncreaseDamage) {
                    //Normal
                    reshitBox->ownerOfHitBox->passivActionGetHit(
                        atcHitBox->ownerOfHitBox->facingDirection,
                        DamageCalculation::calculateDamage(atcHitBox->damage));
                }
            }
        }
    }
}

void ColisionsManager::drawHitBoxes(sf::RenderWindow *window) {
    for (const auto& hitBox : uMOfHitBoxs) {
        hitBox->drawHitBox(window);
    }
}

void ColisionsManager::insetHitBoxTouMOfHitBoxs(HitBox *insertHitBox) {
    uMOfHitBoxs.push_back(insertHitBox);
}

void ColisionsManager::chackGlobalHitBoxColisions() {
    for (const auto& hitBoxFirst : uMOfHitBoxs) {
        if (hitBoxFirst->type != HitBoxType::Attacking)
            continue;
        auto* attackHitBox = static_cast<AttackHitBox*>(hitBoxFirst);
        for (const auto& hitBoxSecond : uMOfHitBoxs) {
            if (hitBoxFirst != hitBoxSecond)
                continue;
            chackForHitBoxesColisions(attackHitBox, hitBoxSecond);
        }
    }
}

void ColisionsManager::updateTransformationForHitBoxes() {
    for (const auto& hitBox : uMOfHitBoxs) {
        hitBox->updateHitBox();
    }
}

void ColisionsManager::disableHitBoxsOutOfLifeTime() {
    for (const auto& hitBox : uMOfHitBoxs) {
        if (hitBox->infinitLifeTime) continue;
        if (hitBox->lifeTime.getElapsedTime().asMilliseconds() < hitBox->lifeTimeInMs) continue;
        uMOfHitBoxsToKill.push_back(hitBox);
    }
}

void ColisionsManager::killAllHitBoxesSetToDie() {
    for (const auto& hitBoxToKill : uMOfHitBoxsToKill) {
        auto it = std::find(uMOfHitBoxs.begin(), uMOfHitBoxs.end(), hitBoxToKill);
        if (it == uMOfHitBoxs.end()) continue;
            delete *it;
            uMOfHitBoxs.erase(it);
    }
    uMOfHitBoxsToKill.clear();
}

void ColisionsManager::changeHitBoxScale(sf::Vector2f newScale, Entity *owner, HitBox *hitBoxToChange) {
    for (const auto& hitBox : uMOfHitBoxs) {
        if (hitBox->ownerOfHitBox != owner && hitBox->name != hitBoxToChange->name ) continue;
        hitBoxToChange->scale = { newScale.x, newScale.y };
    }
}


void ColisionsManager::registerAttackingHitBoxType(const std::string &typeName, HitBoxDefinitionAttacking def) {
    HitBoxDefinitionAttackingUndM.insert({typeName, std::move(def)});
}

void ColisionsManager::registerResevingHitBoxType(const std::string &typeName, HitBoxDefinitionReseving def) {
    HitBoxDefinitionResevingUndM.insert({typeName, std::move(def)});
}

void ColisionsManager::spawnAttackingHitBox(const std::string& typeName, Entity* owner) {
    auto it = HitBoxDefinitionAttackingUndM.find(typeName);
    if (it == HitBoxDefinitionAttackingUndM.end()) {
        std::cerr << "Attacking hitbox does not exist: " << typeName << std::endl;
        return; // nebo throw / fallback definice
    }
    AttackHitBox* hitBox = new AttackHitBox(
        it->second.canBeParryd,
        it->second.canParry,
        it->second.damage,
        it->second.scale,
        owner,
        it->second.lifeTimeInMs,
        it->second.offSet
    );

    uMOfHitBoxs.push_back(hitBox);
    std::cout << "Attacking hitbox created: " << typeName << std::endl;
}

void ColisionsManager::spawnResevingHitBox(const std::string &typeName, Entity *owner) {
    auto it = HitBoxDefinitionResevingUndM.find(typeName);
    if (it == HitBoxDefinitionResevingUndM.end()) {
        std::cerr << "Attacking hitbox does not exist: " << typeName << std::endl;
    }

    ResevingHitBox* hitBox = new ResevingHitBox(
        it->second.scale,
        owner,
        it->second.offSet
    );

    uMOfHitBoxs.push_back(hitBox);
}


void ColisionsManager::updateAndChackForHitBoxes(sf::RenderWindow *window) {
    updateTransformationForHitBoxes();
    chackGlobalHitBoxColisions();
    disableHitBoxsOutOfLifeTime();
    killAllHitBoxesSetToDie();
}
