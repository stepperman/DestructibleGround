//
// Created by Antoine Botteler on 24/09/2018.
//

#include "bomb.h"

sf::Texture *bombTexture;

bomb::bomb() {
    if(bombTexture == nullptr) {
        bombTexture = new sf::Texture();
        bombTexture->loadFromFile("assets/dynamite.png");
    }

    bombSprite.setTexture(*bombTexture);
    bombSprite.setOrigin(bombTexture->getSize().x /2, bombTexture->getSize().y);
    bombSprite.setScale(0.6, 0.6);
}

void bomb::draw(sf::RenderWindow *window) {
    bombSprite.setPosition(position.x, position.y);
    window->draw(bombSprite);
}

void bomb::tick(float deltaTime, Ground *ground)
{
    bombTimer -= deltaTime;

    accel += 400 * deltaTime;

    sf::Vector2i newPosition = position;
    newPosition.y += (int)(accel * deltaTime);

    bool touching = detectCollision(ground->getCollisionTexture().getTexture()->copyToImage(), newPosition.x, newPosition.y);

    if(!touching)
        position = newPosition;
    else
        accel = 0;


    if(bombTimer <= 0) {
        onBombExplode(this);
        delete this;
    }
}

bool bomb::detectCollision(sf::Image img, int x, int y)
{
    int width = static_cast<int>(bombTexture->getSize().x * bombSprite.getScale().x);
    int height = static_cast<int>(bombTexture->getSize().y * bombSprite.getScale().y);
    int startx = (int)(x - bombSprite.getOrigin().x * bombSprite.getScale().x);
    int starty = (int)(y - bombSprite.getOrigin().y * bombSprite.getScale().y);
    for(int i = startx; i < startx + width; i++)
    {
        for(int j = starty; j < starty + height; j++)
        {
            if(img.getPixel(i,j).r == 255) return true;
        }
    }

    return false;
}
