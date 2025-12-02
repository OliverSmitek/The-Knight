//
// Created by Oliver Šmítek on 02.12.2025.
//

#include "SpawnManager.h"


void SpawnManager::spawnPlayer(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity, InsertEntity *insert){
  Player* player = new Player(spawnPosition, spawnVelocity);
  insert->insertEntity("Player", player);
}