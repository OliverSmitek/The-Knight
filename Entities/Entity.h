//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics/Sprite.hpp"
#include "../Managers/SpriteManager.h"
#include "../Managers/TextureManager.h"

#include <unordered_map>
#include "../Insertors/InsertEntity.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"


class Entity {

  protected:
    sf::Sprite sprite; //ptr na Sprite
    sf::Vector2f position; //pozice entityq
    sf::Vector2f velocity; // velocity směr entity
    sf::Texture tex;

  public:

    virtual void update(TextureManager &textureManager, SpriteManager& spriteManager, sf::RenderWindow& window); //osobni Update Kazde Entity
    void drawEntity(SpriteManager& spriteManager, sf::RenderWindow& window); // nakresli sam sebe
    void setTexture(TextureManager& textureManager, sf::String nameOfTexture);// nastaví texturu
    Entity(sf::Vector2f position, sf::Vector2f velocity); //konstruktor Entity


    //Actions:
  virtual void actionWalk(TextureManager& textureManager);
};



#endif //ENTITY_H
