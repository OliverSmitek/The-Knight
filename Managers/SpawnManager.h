//
// Created by Oliver Šmítek on 02.12.2025.
//

#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "../Insertors/InsertEntity.h"
#include <memory>


class SpawnManager {
  public:
    void spawnPlayer(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity, InsertEntity *insert);
};



#endif //SPAWNMANAGER_H
