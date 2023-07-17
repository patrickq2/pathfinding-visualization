#include "cell.h"
#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

class graph{
    public:
    enum modes {walls, points};
    modes mode;
    std::pair <int,int> startP;
    std::pair <int,int> endP;
    std::vector<std::vector<cell>> cells;
    graph();
    void draw(sf::RenderWindow& window);
    void update(sf::Vector2f mousePos, sf::Event& event);
    void changeMode();
};

graph::graph() {
    mode = walls;
    for (int i = 0; i < 25; i++) {
        cells.push_back(std::vector<cell>());
        for (int j = 0; j < 25; j++) {
            cell temp(j*32.0f, i*32.0f);
            cells[i].push_back(temp);
        }
    }
}

void graph::draw(sf::RenderWindow& window) {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            window.draw(cells[i][j].getImage());
        }
    }
}

void graph::update(sf::Vector2f mousePos, sf::Event& event) {
    if (mode == walls) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (int i = 0; i < cells.size(); i++) {
                for (int j = 0; j < cells[i].size(); j++) {
                    if(cells[i][j].getImage().getGlobalBounds().contains(mousePos)) {
                        cells[i][j].change();
                    }
                }
            }
        }
    } else if (mode == points) {
        if (event.mouseButton.button == sf::Mouse::Left) { // set start point
            for (int i = 0; i < cells.size(); i++) {
                for (int j = 0; j < cells[i].size(); j++) {
                    if (cells[i][j].getImage().getGlobalBounds().contains(mousePos)) {
                        cells[startP.first][startP.second].reset();
                        startP = std::make_pair(i,j);
                        cells[startP.first][startP.second].setStart();
                    }
                }
            }
        } else if (event.mouseButton.button == sf::Mouse::Right) { // set end point
            for (int i = 0; i < cells.size(); i++) {
                for (int j = 0; j < cells[i].size(); j++) {
                    if (cells[i][j].getImage().getGlobalBounds().contains(mousePos)) {
                        cells[endP.first][endP.second].reset();
                        endP = std::make_pair(i,j);
                        cells[endP.first][endP.second].setEnd();
                    }
                }
            }
        }
    }
    
} 

void graph::changeMode() {
    if (mode == walls) {
        mode = points;
    } else {
        mode = walls;
    }
}