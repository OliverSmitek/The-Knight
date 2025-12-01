//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <unordered_map>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "../Entitys/Entity.h"
#include "SpriteManager.h"



class EntityManager {

    public:
    std::unordered_map<std::string, Entity*> uMOfEntitys; //unoredred mapa všech entit ve hře

    public:
    void update(SpriteManager& spriteManager, sf::RenderWindow& window);


};



#endif //ENTITYMANAGER_H
