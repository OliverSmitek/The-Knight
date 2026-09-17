//
// Created by Oliver Šmítek on 09.07.2026.
//

#ifndef HITBOX_H
#define HITBOX_H

#include <string>
#include "../Tools/HitBoxTypes/HitBoxType.h"
#include <SFML/Graphics.hpp>
#include <vector>

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
 sf::Vector2f truOffSet;

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
 bool intaraptebul = true;

 AttackHitBox(bool canBePerryd, bool canPerry, int damage, sf::Vector2f scale, Entity *owner, float lifeTimeInMs,  sf::Vector2f offSet, bool intaraptebul);
};

class ResevingHitBox : public HitBox {

public:
 ResevingHitBox(sf::Vector2f scale, Entity *owner, sf::Vector2f offSet, bool colideable, bool movable,bool extending);
 bool invincible = false;
 bool colideable = false;
 bool movable = true;
 bool extending = true;
};


#endif //HITBOX_H
