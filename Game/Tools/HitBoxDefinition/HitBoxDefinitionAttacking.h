#ifndef HITBOXDEFINITIONATTACKING_H
#define HITBOXDEFINITIONATTACKING_H

#include <SFML/System/Vector2.hpp>

struct HitBoxDefinitionAttacking {
    bool canBeParryd;
    bool canParry;
    int damage;
    sf::Vector2f scale;
    float lifeTimeInMs;
    sf::Vector2f offSet;
    bool intareptebul;
};

#endif //HITBOXDEFINITIONATTACKING_H
