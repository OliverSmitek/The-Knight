//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics/Sprite.hpp"
#include "../Managers/SpriteManager.h"
#include <unordered_map>
#include "../Insetors/InsertEntity.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

class Entity {

  protected:
    std::unordered_map<std::string, sf::Texture*> uMOfTextures; //vector of all textures of Entity
    sf::Sprite sprite; //ptr na Sprite
    sf::Vector2f position; //pozice entity
    sf::Vector2f velocity; // velocity směr entity
    sf::Texture tex;

  public:

    virtual void update(SpriteManager& spriteManager, sf::RenderWindow& window); //osobni Update Kazde Entity
    void drawEntity(SpriteManager& spriteManager, sf::RenderWindow& window); // nakresli sam sebe
    Entity(sf::Vector2f position, sf::Vector2f velocity, std::string nameSpace, InsertEntity *insert); //konstruktor Entity

};



#endif //ENTITY_H
