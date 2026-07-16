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

 HitBox(sf::Vector2f scale, Entity *owner);

 HitBoxType type;

 Entity *ownerOfHitBox;

 sf::Clock lifeTime;
 bool infinitLifeTime = false;
 float lifeTimeInMs;

 virtual void updateHitBox();
 void transformHitBox();


 void drawHitBox(sf::RenderWindow* window);

};

class AttackHitBox : public HitBox {
public:
 bool canBePerryd = false;
 bool canPerry = false;
 bool canVelicityIncreaseDamage = false;
 int damage = 0;

 std::vector<std::string> listOfAttackedEntitys;

 AttackHitBox(bool canBePerryd, bool canPerry, int damage, sf::Vector2f scale, Entity *owner, float lifeTimeInMs);
};

class ResevingHitBox : public HitBox {

public:
 ResevingHitBox(sf::Vector2f scale, Entity *owner);

 bool invincible = false;
};

//Knight:-----------------------------------

class KnightAttackHitBoxFirstVariant : public AttackHitBox {
 KnightAttackHitBoxFirstVariant(Entity *owner);
};

class KnightResevingHitBoxSecendVariant : public AttackHitBox {
 KnightResevingHitBoxSecendVariant(Entity *owner);
};

class KnightResevingHitBox : public ResevingHitBox {
 KnightResevingHitBox(Entity *owner);
};

//HellHound:----------------------------------

class HellHoundAttackJump : public AttackHitBox {
 HellHoundAttackJump(Entity *owner);
};

class HellHoundResevingHitBox : public ResevingHitBox {
 HellHoundResevingHitBox(Entity *owner);
};


#endif //HITBOX_H
