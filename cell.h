#include <vector>
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#pragma once

class cell {
    public:
    int arrX;
    int arrY;
    enum cellOpt {normal, wall, startpoint, endpoint, searched, searching, path};
    cell(float x, float y , int arrx, int arry);
    sf::Sprite getImage();
    cellOpt getCellType();
    bool getVisited();
    cell* getParent();
    std::vector<cell*> getNeighbors();
    void update(sf::RenderWindow& window);
    void change();
    void setStart();
    void setEnd();
    void showPath();
    void reset();
    void showSearched();
    void showsearching();
    void setParent(cell* parent);
    void setVisited(bool visited);
    void setNeighbors(cell* neighbor);
    std::vector<cell*> neighbors;
    private:
    cell* parent;
    bool visited;
    cellOpt cellType;
    float x;
    float y;
    sf::Sprite block;

};

cell::cell(float x, float y, int arrx, int arry) {
    cellType = normal;
    this->x = x;
    this->y = y;
    arrX = arrx;
    arrY = arry;
    visited = false;
    parent = nullptr;
    block.setTexture(TextureManager::GetTexture("tile"));
    block.setPosition(x,y);
}

/*void cell::update(sf::RenderWindow& window) {
    window.draw(block);
}*/

sf::Sprite cell::getImage(){
    return block;
}

cell::cellOpt cell::getCellType() {
    return cellType;
}

cell* cell::getParent() {
    return parent;
}

bool cell::getVisited() {
    return visited;
}

std::vector<cell*> cell::getNeighbors() {
    return neighbors;
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

void cell::setVisited(bool visited) {
    this->visited = visited;
}

void cell::setNeighbors(cell* neighbor) {
    neighbors.push_back(neighbor);
}

void cell::setStart() {
    cellType = startpoint;
    block.setTexture(TextureManager::GetTexture("start"));
}

void cell::setEnd() {
    cellType = endpoint;
    block.setTexture(TextureManager::GetTexture("endpoint"));
}

void cell::setParent(cell* parent) {
    this->parent = parent;
}

void cell::showSearched() {
    cellType = searched;
    block.setTexture(TextureManager::GetTexture("searched"));
}

void cell::showsearching() {
    cellType = searching;
    block.setTexture(TextureManager::GetTexture("searching"));
}

void cell::showPath() {
    cellType = path;
    block.setTexture(TextureManager::GetTexture("path"));
}

void cell::reset() {
    cellType = normal;
    visited = false;
    block.setTexture(TextureManager::GetTexture("tile"));
    parent = nullptr;
}

