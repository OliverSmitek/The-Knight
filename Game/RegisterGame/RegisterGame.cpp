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
        .scale = {0.5, 0.52},
        .lifeTimeInMs = 180,
        .offSet = {70, 0},
        .intareptebul = true
    });

    ColisionsManager::getInstance().registerAttackingHitBoxType("KnightResevingHitBoxSecendVariant", {
        .canBeParryd = false,
        .canParry = true,
        .damage = 10,
        .scale = {0.5, 0.45},
        .lifeTimeInMs = 180,
        .offSet = {40, 2}
    });

    ColisionsManager::getInstance().registerResevingHitBoxType("KnightResevingHitBox", {
        .scale = {0.2, 0.4},
        .offSet = {0, 0},
        .colideble = false,
        .moveable = true
    });

    // HellHound
    ColisionsManager::getInstance().registerAttackingHitBoxType("HellHoundAttackJump", {
        .canBeParryd = true,
        .canParry = false,
        .damage = 10,
        .scale = {0.3, 0.3},
        .lifeTimeInMs = 200,
        .offSet = {40, 0},
        .intareptebul = true
    });

    ColisionsManager::getInstance().registerResevingHitBoxType("HellHoundResevingHitBox", {
        .scale = {0.5, 0.32},
        .offSet = {0, 0},
        .colideble = false,
        .moveable = true
    });

    //Platform
    ColisionsManager::getInstance().registerResevingHitBoxType("PlatformResevingHitBox", {
    .scale = {0.6f, 0.175f},
    .offSet = {0, 0},
    .colideble = true,
    .moveable = false
    });
}