//
// Created by Oliver Šmítek on 21.10.2025. HARDSTUCK IN C++
//

#include "SprightManager.h"
#include <SFML/Graphics.hpp>
#include "SprightManager.h"
#include <atomic>






void SprightManager::defaltSprites() {
    for (auto& [characterName, characterEntita] : poleOfAnimationsFaile) {
        sf::Sprite tempSprite;
        tempSprite.setScale(1.9f, 1.9f);
        tempSprite.setTextureRect(sf::IntRect(0, 0, 120, 80));
        tempSprite.setOrigin(tempSprite.getLocalBounds().width / 2, tempSprite.getLocalBounds().height / 2);

        for (const auto& [actionName, texture] : characterEntita->all_character_animations()) {

            if (actionName.find("Idle") != std::string::npos) {
                tempSprite.setTexture(texture);
                poleOfSprites.insert({characterName, tempSprite});
                animationsSpritesSize.insert({characterName, 0});
                characterEntita->setDirection("right");
            }
        }
    }
}

void SprightManager::loadSprite(std::string nameCharacter,std::string nameAction, std::string direction) {

    auto& characterEntity = poleOfAnimationsFaile.at(nameCharacter);
        const sf::Texture* texture = &characterEntity -> all_character_animations().at(nameAction);
            auto& spritePole = poleOfSprites.at(nameCharacter);

                spritePole.setScale(direction == "left" ? -1.9f : 1.9f, 1.9f);
                characterEntity->setDirection(direction);

                // 2. ZMĚNA TEXTURY – pouze pokud je JINÁ
                if (spritePole.getTexture() != texture) {
                    spritePole.setTexture(*texture);
                    animationsSpritesSize[nameCharacter] = 0; // začni od 0
                    spritePole.setTextureRect(sf::IntRect(0, 0, 120, 80));   // reset frame index
                }
}


void SprightManager::movePlayer(std::string direction, std::string nameCharacter, int movment) {

    std::string tempDirection;
    if (poleOfSprites.at(nameCharacter).getScale().x < 0.0f  ) {
        tempDirection = "left";
    }
    if (poleOfSprites.at(nameCharacter).getScale().x > 0.0f  ) {
        tempDirection = "right";
    }


    if (tempDirection != direction) {

        loadSprite("Knight","TurnAroundKnight", tempDirection);
        moveAction("Knight",  0);


        if (animationEnd(nameCharacter)) {
            loadSprite("Knight","RunKnight", direction);
            moveAction("Knight",  movment);
        }
    }
    else {
        loadSprite("Knight","RunKnight", direction);
        moveAction("Knight",movment );
    }
}


void SprightManager::attackPlayer(std::string nameCharacter, std::string direction) {

    loadSprite(nameCharacter,"FightKnight", direction);
}


void SprightManager::jumpPlayer(std::string nameCharacter, std::string direction) {
    loadSprite(nameCharacter,"jumpTexture", direction);



    if (poleOfSprites.at("Knight").getPosition().y >= 500) {
    moveUpAction(nameCharacter, -14);

    }
}

bool SprightManager::animationEnd(std::string nameCharacter) {


    int FramePosition = animationsSpritesSize.at(nameCharacter);
    int width  = poleOfSprites.at(nameCharacter).getTexture()->getSize().x/120;


    if (width <= FramePosition) {

        return true;
    }
    return false;
}



void SprightManager::animationManager() {
    if (timer.getElapsedTime().asMilliseconds() >= interval) {
        for (auto& [characterAction, sprite] : poleOfSprites) {
            int width  = sprite.getTexture()->getSize().x/120;

            if (width > animationsSpritesSize.at(characterAction)) {

                sprite.setTextureRect(sf::IntRect( animationsSpritesSize.at(characterAction) * 120, 0, 120, 80));
                std::cout << animationsSpritesSize.at("Knight") << std::endl;
                animationsSpritesSize.at(characterAction)++;

            }
            else {
                animationsSpritesSize.at(characterAction) = 0;
                sprite.setTextureRect(sf::IntRect( animationsSpritesSize.at(characterAction) * 120, 0, 120, 80));
                std::cout << animationsSpritesSize.at("Knight") << std::endl;
                animationsSpritesSize.at(characterAction)++;
            }

        }
        timer.restart();
    }
}


void SprightManager::moveAction(std::string nameCharacter, float x) {
    for (auto& [characterName, characterEntita] : poleOfAnimationsFaile) {
        if (characterName == nameCharacter) {
            characterEntita->set_entita_velocity_x(x);
        }

    }
}

void SprightManager::moveUpAction(std::string nameCharacter, float y) {
    for (auto& [characterName, characterEntita] : poleOfAnimationsFaile) {
        if (characterName == nameCharacter) {
            characterEntita->set_entita_velocity_y(y);
        }

    }
}


void SprightManager::gravityPlayer() {

    for (auto& [characterName, characterEntita] : poleOfAnimationsFaile) {
        if (poleOfSprites.at(characterName).getPosition().y <= 500) {
            float y = characterEntita->entita_velocity_y();
            characterEntita->set_entita_velocity_y(y + 0.75);
        }
        else {
            characterEntita->set_entita_velocity_y(0);
        }
    }
}

void SprightManager::drawSprite(sf::RenderWindow &window) {

    for (auto& [characterName, characterEntita] : poleOfAnimationsFaile) {
        poleOfSprites.at(characterName).setPosition(poleOfSprites.at(characterName).getPosition().x + characterEntita->entita_velocity_x() , poleOfSprites.at(characterName).getPosition().y + characterEntita->entita_velocity_y());
        gravityPlayer();

    }

    for (auto& [characterAction, sprite] : poleOfSprites) {

        window.draw(sprite);
    }
}



