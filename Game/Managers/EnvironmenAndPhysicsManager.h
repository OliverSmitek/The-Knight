//
// Created by Oliver Šmítek on 20.01.2026.
//

#ifndef ENVIRONMENANDPHYSICSMANAGER_H
#define ENVIRONMENANDPHYSICSMANAGER_H
#include <string>
#include "SFML/System/Vector2.hpp"
class ResevingHitBox;

class EnvironmenAndPhysicsManager {


    EnvironmenAndPhysicsManager() {}

    public:
    static EnvironmenAndPhysicsManager& getInstance(){
        static EnvironmenAndPhysicsManager theInstance;
        return theInstance;
    }

    public:

    double gravityPower = 1.2;
    double floor = 797;
    void gravity(sf::Vector2f &velocity, bool freez);

    void groundeAndGravity(sf::Vector2f &position, sf::Vector2f &velocity, bool freez, bool ignoreTheFloor, bool isOnTheFloor);

    void platformGeneretion(sf::Vector2f position, std::string structure);

};



#endif //ENVIRONMENANDPHYSICSMANAGER_H
