/*#include "cell.h"
#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

class graph{
    public:
    std::vector<std::vector<cell>> cells;
    graph();
    void draw(sf::RenderWindow& window);
};

graph::graph() {
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
}*/