#include <iostream>
#include <vector>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Ground.h"
#include "bomb.h"

std::vector<bomb *> bombArray;
Ground *ground;
bool hasFocus = true;

void bombExploded(bomb *bomb) {
    std::printf("Bomb exploded. \n");
    ground->Destroy(bomb->position.x, bomb->position.y, 120);

    // find index of element
    auto it = std::find(bombArray.begin(), bombArray.end(), bomb);
    int index = std::distance(bombArray.begin(), it);

    //remove from array
    bombArray.erase(bombArray.begin()+index);

    bomb->onBombExplode = nullptr;
}

bool justPressed = false;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Destructible Terrain", sf::Style::Close | sf::Style::Titlebar);
    sf::Texture t;
    if (!t.loadFromFile("assets/ground.png")) {
        std::cout << "Could not load asset: ground.";
        return 1;
    }

    ground = new Ground(&t);

    sf::Clock clock;
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::GainedFocus)
                hasFocus = true;
            if(event.type == sf::Event::LostFocus)
                hasFocus = false;
        }
        sf::Time time = clock.restart();

        if(!hasFocus)
            continue;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !justPressed) {
            auto mousePosition = sf::Mouse::getPosition(window);
            if(mousePosition.x < 0 || mousePosition.x > window.getSize().x || mousePosition.y < 0 || mousePosition.y > window.getSize().y)
                continue;

            bomb *b = new bomb();
            sf::Vector2i s = (sf::Vector2i) b->bombSprite.getTexture()->getSize() / 2;

            b->position = sf::Mouse::getPosition(window);
            b->onBombExplode = &bombExploded;

            printf("%i %i \n", b->position.x, b->position.y);

            bombArray.push_back(b);

            justPressed = true;
        } else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && justPressed) {
            justPressed = false;
        }


        window.clear(sf::Color(0, 120, 150));

        ground->Draw(&window);

        for (int i = 0; i < bombArray.size(); i++) {
            bombArray[i]->tick(time.asSeconds(), ground);
        }

        // because the array count might have changed, loop over it again to draw it.
        for(int i = 0; i < bombArray.size(); i++) {
            bombArray[i]->draw(&window);
        }

        window.display();

    }
}