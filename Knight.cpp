#include "Knight.h"

Knight::Knight(SprightManager& sManager) {
    if (!idleTexture.loadFromFile("../../_Idle.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }

    if (!runTexture.loadFromFile("../../_Run.png")) {
        throw std::runtime_error("Nelze načíst Run texturu");
    }

    if (!fightTexture.loadFromFile("../../_Attack.png")) {
        throw std::runtime_error("Nelze načíst Run texturu");
    }

    if (!turnAroundTexture.loadFromFile("../../_TurnAround.png")) {
        throw std::runtime_error("Nelze načíst Run texturu");
    }

    if (!fightTexture2.loadFromFile("../../_Attack2.png")) {
        throw std::runtime_error("Nelze načíst Run texturu");
    }

    if (!jumpTexture.loadFromFile("../../_Jump.png")) {
        throw std::runtime_error("Nelze načíst Run texturu");
    }
    if (!jumpFallInbetweenTexture.loadFromFile("../../_JumpFallInbetween.png")) {
        throw std::runtime_error("Nelze načíst Run texturu");
    }


    allCharacterAnimations["IdleKnight"] = idleTexture;

    allCharacterAnimations["RunKnight"] = runTexture;

    allCharacterAnimations["FightKnight"] = fightTexture;

    allCharacterAnimations["FightKnight2"] = fightTexture2;

    allCharacterAnimations["TurnAroundKnight"] = turnAroundTexture;

    allCharacterAnimations["jumpTexture"] = jumpTexture;
    allCharacterAnimations["jumpFallInbetweenTexture"] = jumpFallInbetweenTexture;



    sManager.poleOfAnimationsFaile.insert({"Knight", this});



}
