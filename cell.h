#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#pragma once

class cell {
    enum cellOpt {normal, wall, startpoint, endpoint, searched};
    cellOpt cellType;
    float x;
    float y;
    sf::Sprite block;
    public:
    cell(float x, float y);
    void update(sf::RenderWindow& window);
    sf::Sprite getImage();
    void change();
    void setStart();
    void setEnd();
    void reset();
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

void cell::change() {
    if (cellType == normal) {
        cellType = wall;
        block.setTexture(TextureManager::GetTexture("wall"));
    } else {
        cellType = normal;
        block.setTexture(TextureManager::GetTexture("tile"));
    }
}

void cell::setStart() {
    cellType = startpoint;
    block.setTexture(TextureManager::GetTexture("start"));
}

void cell::setEnd() {
    cellType = endpoint;
    block.setTexture(TextureManager::GetTexture("endpoint"));
}

void cell::reset() {
    cellType = normal;
    block.setTexture(TextureManager::GetTexture("tile"));
}
