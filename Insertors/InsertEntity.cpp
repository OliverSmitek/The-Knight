//
// Created by Oliver Šmítek on 28.11.2025.
//

#include "InsertEntity.h"
#include "../Managers/EntityManager.h"
#include <string>

InsertEntity::InsertEntity(EntityManager *entityManager) {
    this->em = entityManager;
}

void InsertEntity::insertEntity(std::string entityName, Entity* entity) {
    em->uMOfEntitys[entityName] = entity;
}
