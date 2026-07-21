//
// Created by Oliver Šmítek on 09.07.2026.
//

#ifndef HITBOX_H
#define HITBOX_H
#include <string>

#include "../Entities/Entity.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "../Tools/HitBoxTypes/HitBoxType.h"


class Entity;

class HitBox {

public:

 std::string name;

 sf::Vector2f position;
 sf::Vector2f scale;
 sf::Sprite hitBoxSp;

 HitBox(sf::Vector2f scale, Entity *owner, sf::Vector2f offSet);

 HitBoxType type;

 Entity *ownerOfHitBox;

 sf::Clock lifeTime;
 bool infinitLifeTime = false;
 float lifeTimeInMs;

 sf::Vector2f offSet;

 virtual void updateHitBox();
 void transformHitBox();

 void offSetHitBox();

 void drawHitBox(sf::RenderWindow* window);

};

class AttackHitBox : public HitBox {
public:
 bool canBePerryd = false;
 bool canPerry = false;
 bool canVelicityIncreaseDamage = false;
 int damage = 0;

 std::vector<std::string> listOfAttackedEntitys;

 AttackHitBox(bool canBePerryd, bool canPerry, int damage, sf::Vector2f scale, Entity *owner, float lifeTimeInMs,  sf::Vector2f offSet);
};

class ResevingHitBox : public HitBox {

public:
 ResevingHitBox(sf::Vector2f scale, Entity *owner, sf::Vector2f offSet);

 bool invincible = false;
};


#endif //HITBOX_H
