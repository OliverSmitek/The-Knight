//
// Created by Oliver Šmítek on 10.07.2026.
//

#include "DamageCalculation.h"

DamageCalculation::DamageCalculation() {};

int DamageCalculation::calculateDamageVelocityAndPerry(int damage, sf::Vector2f velocity, int multiplayer) {
    int damageFinal = 0;

    damageFinal = multiplayer * (damage * ((velocity.x + velocity.y) / 15));

    return damageFinal;
}

int DamageCalculation::calculateDamage(int damage) {
    return damage;
}

int DamageCalculation::calculateDamageVelocity(int damage, sf::Vector2f velocity) {
    int damageFinal = 0;

    damageFinal = ((velocity.x + velocity.y) / 15 * damage);

    return damageFinal;
}

int DamageCalculation::calculateDamagePerry(int damage, int multiplayer) {
    int damageFinal = 0;
    damageFinal = multiplayer *  damage;

    return damageFinal;
}
