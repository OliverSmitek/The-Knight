//
// Created by Oliver Šmítek on 10.07.2026.
//

#ifndef DAMAGECALCULATION_H
#define DAMAGECALCULATION_H
#include "SFML/System/Vector2.hpp"


class DamageCalculation {

    public:

    static DamageCalculation& getInstance(){
        static DamageCalculation theInstance;
        return theInstance;
    }

    DamageCalculation();

    static int calculateDamage(int damage);
    static int calculateDamageVelocityAndPerry(int damage, sf::Vector2f velocity, int multiplayer);
    static int calculateDamagePerry(int damage, int multiplayer);
    static int calculateDamageVelocity(int damage, sf::Vector2f velocity);
};



#endif //DAMAGECALCULATION_H
