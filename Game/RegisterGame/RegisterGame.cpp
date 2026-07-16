//
// Created by Oliver Šmítek on 16.07.2026.
//

#include "RegisterGame.h"

#include "../Managers/ColisionsManager.h"
#include "../Managers/SpawnManager.h"

void RegisterGame::performGameRegistration() {

        // Knight
        ColisionsManager::getInstance().registerAttackingHitBoxType("KnightAttackHitBoxFirstVariant", {
            .canBeParryd = false,
            .canParry = true,
            .damage = 10,
            .scale = {1, 1},
            .lifeTimeInMs = 50
        });

        ColisionsManager::getInstance().registerAttackingHitBoxType("KnightResevingHitBoxSecendVariant", {
            .canBeParryd = false,
            .canParry = true,
            .damage = 10,
            .scale = {2, 1},
            .lifeTimeInMs = 50
        });

        ColisionsManager::getInstance().registerResevingHitBoxType("KnightResevingHitBox", {
            .scale = {1, 1}
        });

        // HellHound
        ColisionsManager::getInstance().registerAttackingHitBoxType("HellHoundAttackJump", {
            .canBeParryd = true,
            .canParry = false,
            .damage = 10,
            .scale = {2, 1},
            .lifeTimeInMs = 80
        });

    ColisionsManager::getInstance().registerResevingHitBoxType("HellHoundResevingHitBox", {
        .scale = {1, 1}
    });




}
