//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/RenderWindow.hpp"
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/Sprite.hpp"


class SpriteManager{


    public:
    void drawSprite(sf::Sprite *sprite, float x, float y, sf::RenderWindow& window); //drawFunkce(Vlastní každá Entita či oběkt)
};



#endif //SPRITEMANAGER_H
