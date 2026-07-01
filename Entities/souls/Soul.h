//
// Created by Oliver Šmítek on 01.07.2026.
//

#ifndef SOUL_H
#define SOUL_H
#include "../Entity.h"
#include "../../Managers/EntityManager.h"




class Soul : public Entity {

public:
    Soul(sf::Vector2f position, std::string name, std::string nameOfTexture);

    void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;
    void movmentUpdate() override;

    void drawHitbox(sf::RenderWindow &window) override;

    void passivActionDie();

    void hitBoxUpdateposition() override;
};



#endif //SOUL_H
