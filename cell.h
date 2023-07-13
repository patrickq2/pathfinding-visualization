#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#pragma once

class cell {
    enum cellOpt {normal, wall, startpoint, endpoint};
    cellOpt cellType;
    float x;
    float y;
    sf::Sprite block;

    public:
    cell(float x, float y);
    void update(sf::RenderWindow& window);
    sf::Sprite getImage();

};

cell::cell(float x, float y) {
    cellType = normal;
    this->x = x;
    this->y = y;
    block.setTexture(TextureManager::GetTexture("tile"));
    block.setPosition(x,y);
}

/*void cell::update(sf::RenderWindow& window) {
    window.draw(block);
}*/

sf::Sprite cell::getImage(){
    return block;
}