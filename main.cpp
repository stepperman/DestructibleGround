#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Ground.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1280,720), "Destructible Terrain", sf::Style::Close | sf::Style::Titlebar);
    sf::Texture t;
    if(!t.loadFromFile("ground.png")){
        std::cout << "Nigger";
        return 1;
    }
    Ground ground(&t);


    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                auto position = sf::Mouse::getPosition(window);
                ground.Destroy(position.x, position.y, 20);
            }

            window.clear(sf::Color(0,120,150));

            ground.Draw(&window);

            window.display();
        }
    }
}