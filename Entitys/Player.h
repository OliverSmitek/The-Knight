//
// Created by Oliver Šmítek on 25.11.2025.
//
#include "Entity.h"
#include "SFML/Graphics/Sprite.hpp"
#include "../Managers/SpriteManager.h"
#include "SFML/Graphics/RenderWindow.hpp"




#ifndef PLAYER_H
#define PLAYER_H



class Player : public Entity {

  //protected:
    //std::unordered_map<std::string, sf::Texture*> uMOfTextures;
    //sf::Sprite* sprite; //ptr na Sprite
    //sf::Vector2f position;
    //sf::Vector2f velocity;

    public:

        Player(sf::Vector2f position,sf::Vector2f velocity);
        void update(SpriteManager& spriteManager, sf::RenderWindow& window) override;
};



#endif //PLAYER_H
