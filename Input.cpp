//
// Created by Oliver Šmítek on 03.11.2025.
//

#include "Input.h"
#include "SFML/Graphics.hpp"
#include "SprightManager.h"



void Input::inputD(SprightManager& sManager) {

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
    sManager.attackPlayer("Knight", faceHeading);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
    sManager.jumpPlayer("Knight", faceHeading);
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    faceHeading = "right";
    sManager.movePlayer(faceHeading,"Knight" ,  5);

  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    faceHeading = "left";
    sManager.movePlayer(faceHeading,"Knight", -5);

  }

  else {
    sManager.loadSprite("Knight","IdleKnight", faceHeading);
    sManager.moveAction("Knight",0);
  }





}


