#include <iostream>

#include "Managers/EntityManager.h"
#include "Managers/SpriteManager.h"
#include "Entities/Player.h"
#include "Managers/SpawnManager.h"

#include "Insertors/InsertEntity.h"
#include "SFML/Graphics.hpp"

int main() {
    TextureManager textureManager;
    SpriteManager spriteManager;
    EntityManager entityManager;
    InsertEntity insertEntity(&entityManager);
    SpawnManager spawnManager;

    spawnManager.spawnPlayer({0, 0}, {0, 0}, &insertEntity);

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "The Knight");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        entityManager.update(textureManager,spriteManager, window);
        window.display();
    }

    return 0;
}
