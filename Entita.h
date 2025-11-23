//
// Created by Oliver Šmítek on 11.11.2025.
//

#ifndef ENTITA_H
#define ENTITA_H

#include "SprightManager.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>



class Entita {
protected:

    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Texture fightTexture;
    sf::Texture fightTexture2;
    sf::Texture turnAroundTexture;
    sf::Texture jumpTexture;
    sf::Texture jumpFallInbetweenTexture;

    int entitaHP;
    float entitaVelocityX;
    float entitaVelocityY;
    std::string direction;
    std::unordered_map<std::string, sf::Texture> allCharacterAnimations;

public:
    [[nodiscard]] const int& entita_hp() const {
        return entitaHP;
    }

    [[nodiscard]] const float& entita_velocity_x() const {
        return entitaVelocityX;
    }

    [[nodiscard]] const float& entita_velocity_y() const {
        return entitaVelocityY;
    }

    [[nodiscard]] const std::unordered_map<std::string, sf::Texture>& all_character_animations() const {
        return allCharacterAnimations;
    }

    [[nodiscard]] std::string getDirection() const {
        return direction;
    }

    void setDirection(std::string direction) {
        this->direction = direction;
    }


    void set_entita_velocity_y(float v) { entitaVelocityY = v; }
    void set_entita_velocity_x(float t) { entitaVelocityX = t; }

    Entita() = default;
    virtual ~Entita() = default;
};


#endif //ENTITA_H
