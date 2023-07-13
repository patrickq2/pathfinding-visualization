#include "cell.h"
#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

class graph {
    std::vector<std::vector<cell>> cells;
    public:
    graph();
    void update(sf::RenderWindow& window);
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

void graph::update(sf::RenderWindow& window) {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            window.draw(cells[i][j].getImage());
        }
    }
}