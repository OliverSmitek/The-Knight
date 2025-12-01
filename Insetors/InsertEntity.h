//
// Created by Oliver Šmítek on 28.11.2025.
//
#ifndef INSERTENTITY_H
#define INSERTENTITY_H
#include <string>


class EntityManager;
class Entity;

class InsertEntity {

    EntityManager *em;

public:
    InsertEntity(EntityManager *entityManager);
    void insertEntity(std::string entityName, Entity* entity);
};

#endif // INSERTENTITY_H
