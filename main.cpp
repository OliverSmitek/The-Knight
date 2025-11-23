#include <vector>
#include "SFML/Graphics.hpp"
#include "SprightManager.h"
#include "Knight.h"
#include <thread>
#include <chrono>
#include "Input.h"


using namespace std;

int main(int argc, char **argv)
{

    SprightManager sManager;
    Knight knight(sManager);
    sManager.defaltSprites();
    Input input;

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Hra");
    window.setFramerateLimit(60);



    while (window.isOpen())
    {



        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        input.inputD(sManager);


        sManager.animationManager();
        window.clear();
        sManager.drawSprite(window);
        window.display();
    }

    return 0;
}