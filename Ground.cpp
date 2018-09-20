//
// Created by Antoine Botteler on 19/09/2018.
//

#include <iostream>
#include <vector>
#include "Ground.h"

Ground::Ground(sf::Texture *tex) {

    texture.setTexture(*tex);
    auto *image = new sf::Image();
    CopyTextureToImage(tex, false, *image);

    /*for (int i = 0; i < image->getSize().x; i++) {
        for (int j = 0; j < image->getSize().y; j++) {
            printf("%i \n", image->getPixel(i,j).a);
        }
    }*/
    
    auto *newMaskTexture = new sf::Texture();
    CopyImageToTexture(*image, *newMaskTexture);
    maskTexture.setTexture(*newMaskTexture);
    LoadShader();
}

void Ground::CopyImageToTexture(sf::Image image, sf::Texture &copyTex) {
    copyTex.create(image.getSize().x, image.getSize().y);
    copyTex.loadFromImage(image);
}

void Ground::LoadShader() {
    Ground::maskShader.loadFromFile("maskShader.f.glsl", sf::Shader::Fragment);
}

void Ground::Draw(sf::RenderWindow *window) {
    sf::Texture t;
    sf::Image image;

    t = *maskTexture.getTexture();
    image = t.copyToImage();

    maskShader.setUniform("maskTexture", *maskTexture.getTexture());
    maskShader.setUniform("texture", *texture.getTexture());
    window->draw(texture, sf::RenderStates(&maskShader));
}

void *Ground::CopyTextureToImage(sf::Texture *t, const bool inColor, sf::Image &returnedImage) {
    sf::Image blackwhiteImage, tImage;

    if(inColor)
    {
        returnedImage = t->copyToImage();
        return 0;
    }

    sf::Vector2u size = t->getSize();
    blackwhiteImage.create(size.x, size.y);

    //copy to image
    tImage = texture.getTexture()->copyToImage();

    for(int i = 0; i < size.x; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            sf::Color color = tImage.getPixel(i,j);
            if(color.a > 125) {
                blackwhiteImage.setPixel(i,j,sf::Color(255,255,255,255));
            }
            else blackwhiteImage.setPixel(i,j,sf::Color(0,0,0,0));
        }
    }

    returnedImage = blackwhiteImage;
}

void Ground::Destroy(int x, int y, int radius)
{
    // copy mask to image
    sf::Image image;
    const sf::Texture *tt = maskTexture.getTexture();
    image.create(tt->getSize().x, tt->getSize().y);
    image = tt->copyToImage();
    int ra = radius*radius;

    printf("x: %i y: %i\n", x,y);

    for (int i = 0; i < image.getSize().x; ++i) {
        for (int j = 0; j < image.getSize().y; ++j)
        {
            int m1 = i - x;
            int m2 = j - y;
            int rr = m1 * m1 + m2 * m2;
            if(rr < ra) {
                printf("yo\n");
                image.setPixel(i,j,sf::Color(0,0,0,0));
            }
        }
    }

    sf::Texture *tex = new sf::Texture();
    tex->create(tt->getSize().x, tt->getSize().y);
    tex->loadFromImage(image);
    maskTexture.setTexture(*tex);
}
