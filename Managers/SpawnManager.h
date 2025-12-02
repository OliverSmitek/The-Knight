//
// Created by Oliver Šmítek on 02.12.2025.
//

#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include "../Entitys/Entity.h"
#include "../Entitys/Player.h"
#include "../Insetors/InsertEntity.h"
#include <memory>


class SpawnManager {

  public:
    void spawnPlayer(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity, InsertEntity *insert);
};



#endif //SPAWNMANAGER_H
