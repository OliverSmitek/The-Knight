#ifndef KNIGHT_H
#define KNIGHT_H

#include "SprightManager.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Entita.h"


class Knight : public Entita{
public:
    Knight(SprightManager& sManager);
};

#endif // KNIGHT_H
