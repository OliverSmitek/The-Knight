//
// Created by Oliver Šmítek on 21.10.2025.
//

#ifndef SPRIGHTMANAGER_H
#define SPRIGHTMANAGER_H

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Entita.h"


class SprightManager {




public:
    std::unordered_map<std::string, int> animationsSpritesSize;
    std::unordered_map<std::string, sf::Sprite> poleOfSprites;
    std::unordered_map<std::string, Entita*> poleOfAnimationsFaile;
    sf::Clock timer;
    const float interval = 52.0f;


    void defaltSprites();
    void drawSprite(sf::RenderWindow& window);
    void loadSprite(std::string nameCharacter,std::string nameAction, std::string direction);
    void animationManager();
    void moveAction(std::string nameCharacter, float x);
    void moveUpAction(std::string nameCharacter, float y);
    void movePlayer(std::string direction, std::string nameCharacter, int movment);
    bool animationEnd(std::string nameCharacter);
    void attackPlayer(std::string nameCharacter, std::string direction);
    void jumpPlayer(std::string nameCharacter, std::string direction);
    void gravityPlayer();


};


#endif //SPRIGHTMANAGER_H
