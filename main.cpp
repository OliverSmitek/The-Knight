#include <iostream>

#include "Managers/EntityManager.h"
#include "Managers/SpriteManager.h"
#include "Entitys/Player.h"
#include "Insetors/InsertEntity.h"
#include "SFML/Graphics.hpp"

int main() {

    SpriteManager spriteManager;
    EntityManager entityManager;
    InsertEntity insertEntity(&entityManager);


    Player player({0,0}, {1,1}, "pepa",&insertEntity);

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "The Knight");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {


        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }


        window.clear();
        entityManager.update(spriteManager, window);
        window.display();
    }

    return 0;
}

