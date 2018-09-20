//
// Created by Antoine Botteler on 19/09/2018.
//

#ifndef DESTRUCTIBLEGROUND_GROUND_H
#define DESTRUCTIBLEGROUND_GROUND_H

#include <SFML/Graphics.hpp>

class Ground {
public:
    Ground(sf::Texture *);
    void Destroy(int,int,int);
    void CheckCollision(int,int);
    void CheckCollisionAABB(int,int,int,int);
    void Draw(sf::RenderWindow *);
private:
    sf::Shader maskShader;
    sf::Sprite texture, maskTexture;

    ///test
    void *CopyTextureToImage(sf::Texture *, bool, sf::Image &);
    void CopyImageToTexture(sf::Image, sf::Texture &copyTex);
    void LoadShader();
};

#endif //DESTRUCTIBLEGROUND_GROUND_H
