#include "Game/GameManager.h"
#include "Game/Managers/EntityManager.h"
#include "Game/Managers/SpawnManager.h"

#include "Game/Managers/BackGroundManager.h"
#include "Game/Managers/CameraManager.h"
#include "Game/Managers/DrawManager.h"
#include "Game/Managers/EnvironmenAndPhysicsManager.h"
#include "Game/RegisterGame/RegisterGame.h"


int main() {


    RegisterGame::getInstance().performGameRegistration();

    SpawnManager::getInstance().spawnPlayer({835,520}, {0, 0});
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "The Knight");

    while (window.isOpen()) {
        if (GameManager::getInstance().tickClock.getElapsedTime().asMilliseconds() >= GameManager::getInstance().timeInFrames) {
            GameManager::getInstance().addToTicksMade();
            GameManager::getInstance().resetColockForTicks();
            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            EntityManager::getInstance().update(window, EnvironmenAndPhysicsManager::getInstance());
            BackGroundManager::getInstance().logicOfBackground(window);
            CameraManager::getInstance().CameraUpdate(window);
            DrawManager::getInstance().getInstance().drawGame(window, EnvironmenAndPhysicsManager::getInstance());

            window.display();
        }
    }

    return 0;
}

