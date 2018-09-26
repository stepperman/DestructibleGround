//
// Created by Antoine Botteler on 24/09/2018.
//

#ifndef DESTRUCTIBLEGROUND_BOMB_H
#define DESTRUCTIBLEGROUND_BOMB_H

#include "Ground.h"
#include "SFML/Graphics.hpp"

class bomb {
public:

    bomb();

    void tick(float deltaTime, Ground *);
    //returns true if intersecting, false if intersecting nothing.
    bool detectCollision(sf::Image, int, int);
    void draw(sf::RenderWindow *);
    sf::Vector2i position;

    typedef void (*bombExploded)(bomb *);
    bombExploded onBombExplode;
    sf::Sprite bombSprite;
private:
    float bombTimer = 3.0f;
    float accel = 0;
    const int bombRadius = 20;
};


#endif //DESTRUCTIBLEGROUND_BOMB_H
