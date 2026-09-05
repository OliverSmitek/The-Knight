//
// Created by Oliver Šmítek on 10.07.2026.
//

#include "ColisionsManager.h"

#include "../Entities/Player/Player.h"
#include "../Tools/DamageCalculator/DamageCalculation.h"

ColisionsManager::ColisionsManager() {};

void ColisionsManager::chackForHitBoxesColisions(HitBox *firstHitBox, HitBox *SecendHitBox) {
    if (firstHitBox->type == HitBoxType::Attacking) {
        auto* atcHitBox = static_cast<AttackHitBox*>(firstHitBox);

        if (std::find(atcHitBox->listOfAttackedEntitys.begin(),
                      atcHitBox->listOfAttackedEntitys.end(),
                      SecendHitBox->name) != atcHitBox->listOfAttackedEntitys.end())
            return;

        if (SecendHitBox->type == HitBoxType::Attacking) {
            auto* second = static_cast<AttackHitBox*>(SecendHitBox);

            if (atcHitBox->hitBoxSp.getGlobalBounds().intersects(second->hitBoxSp.getGlobalBounds()) &&
                atcHitBox->canPerry && second->canBePerryd) {

                atcHitBox->listOfAttackedEntitys.push_back(second->name);

                auto damage = atcHitBox->canVelicityIncreaseDamage
                    ? DamageCalculation::calculateDamageVelocityAndPerry(
                          atcHitBox->damage, atcHitBox->ownerOfHitBox->velocity, perryMultiplayer)
                    : DamageCalculation::calculateDamagePerry(atcHitBox->damage, perryMultiplayer);

                second->ownerOfHitBox->passivActionGetHit(atcHitBox->ownerOfHitBox->facingDirection, damage);
            }
        }

        if (SecendHitBox->type == HitBoxType::Reseving) {
            auto* receiving = static_cast<ResevingHitBox*>(SecendHitBox);

            if (atcHitBox->hitBoxSp.getGlobalBounds().intersects(receiving->hitBoxSp.getGlobalBounds()) &&
                !receiving->invincible) {

                atcHitBox->listOfAttackedEntitys.push_back(receiving->name);

                auto damage = atcHitBox->canVelicityIncreaseDamage
                    ? DamageCalculation::calculateDamageVelocity(atcHitBox->damage, atcHitBox->ownerOfHitBox->velocity)
                    : DamageCalculation::calculateDamage(atcHitBox->damage);

                receiving->ownerOfHitBox->passivActionGetHit(atcHitBox->ownerOfHitBox->facingDirection, damage);
            }
        }
    }
    else if (firstHitBox->type == HitBoxType::Reseving) {
        auto* first = static_cast<ResevingHitBox*>(firstHitBox);

        if (SecendHitBox->type == HitBoxType::Reseving) {
            auto* second = static_cast<ResevingHitBox*>(SecendHitBox);

            if (first->colideable && second->colideable &&
                first->hitBoxSp.getGlobalBounds().intersects(second->hitBoxSp.getGlobalBounds())) {

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
    //works now ale je potřeba předělat :3
    for (const auto& hitBoxFirst : uMOfHitBoxs) {
        if (hitBoxFirst->type == HitBoxType::Attacking) {
            auto* attackHitBox = static_cast<AttackHitBox*>(hitBoxFirst);

            //Perry detection (attack hitboxes detection)
            for (const auto& hitBoxSecond : uMOfHitBoxs) {
                if (hitBoxSecond->type != HitBoxType::Attacking)
                    continue;
                if (hitBoxFirst->name == hitBoxSecond->name)
                    continue;
                if (attackHitBox->ownerOfHitBox->name == hitBoxSecond->ownerOfHitBox->name)
                    continue;
                chackForHitBoxesColisions(attackHitBox, hitBoxSecond);
            }

            //Reseving detection
            for (const auto& hitBoxSecond : uMOfHitBoxs) {
                if (hitBoxFirst->name == hitBoxSecond->name)
                    continue;
                if (attackHitBox->ownerOfHitBox->name == hitBoxSecond->ownerOfHitBox->name)
                    continue;
                chackForHitBoxesColisions(attackHitBox, hitBoxSecond);
            }
        }
        else if (hitBoxFirst->type == HitBoxType::Reseving) {
            auto* firstRes = static_cast<ResevingHitBox*>(hitBoxFirst);

            for (const auto& hitBoxSecond : uMOfHitBoxs) {
                if (hitBoxSecond->type != HitBoxType::Reseving)
                    continue;
                if (hitBoxFirst->name == hitBoxSecond->name)
                    continue;
                if (firstRes->ownerOfHitBox->name == hitBoxSecond->ownerOfHitBox->name)
                    continue;
                chackForHitBoxesColisions(firstRes, hitBoxSecond);
            }
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

void ColisionsManager::getRidOfHitBoxsOfOwner(Entity *owner) {
    for (const auto& hitBox : uMOfHitBoxs) {
        if (hitBox->ownerOfHitBox->name != owner->name) continue;
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

void ColisionsManager::registerResevingHitBoxType(const std::string &typeName, HitBoxDefinitionResevingAndColision def) {
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
        it->second.offSet,
        it->second.intareptebul
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
        it->second.offSet,
        it->second.colideble
    );

    uMOfHitBoxs.push_back(hitBox);
}


void ColisionsManager::intaraptAttack(Entity *owner) {
    for (const auto& hitBox : uMOfHitBoxs) {
        if (hitBox->ownerOfHitBox->name != owner->name) continue;
        if (hitBox->type != HitBoxType::Attacking) continue;
            AttackHitBox* hitBoxAtt = static_cast<AttackHitBox*>(hitBox);
        if (hitBoxAtt->intaraptebul != true) continue;
        uMOfHitBoxsToKill.push_back(hitBox);
    }
}

void ColisionsManager::ColidebleHitBoxesColided() {

}

void ColisionsManager::updateAndChackForHitBoxes(sf::RenderWindow *window) {
    updateTransformationForHitBoxes();
    chackGlobalHitBoxColisions();
    disableHitBoxsOutOfLifeTime();
    killAllHitBoxesSetToDie();
}

