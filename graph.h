#include <vector>
#include <queue>
#include <iostream>
#include <thread>
#include "cell.h"
#include <SFML/Graphics.hpp>
#pragma once

class graph{
    enum modes {walls, points};
    modes mode;
    std::pair <int,int> startP;
    std::pair <int,int> endP;
    std::vector<std::vector<cell>> cells;

    public:
    graph();
    void draw(sf::RenderWindow& window);
    void update(sf::Vector2f mousePos, sf::Event& event);
    void solve(string sol);
    void changeMode();
    void BFS(sf::RenderWindow& window);
    void dijkstra(sf::RenderWindow& window);
    void reset();
    void drawpath(sf::RenderWindow& window);
    void findAdjacent();
};

graph::graph() {
    mode = walls;
    for (int i = 0; i < 25; i++) {
        cells.push_back(std::vector<cell>());
        for (int j = 0; j < 25; j++) {
            cell temp(j*32.0f, i*32.0f, i, j);
            cells[i].push_back(temp);
        }
    }
    findAdjacent();
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
                    if (cells[i][j].getImage().getGlobalBounds().contains(mousePos) && cells[i][j].getCellType() == cell::cellOpt::normal) {
                        cells[startP.first][startP.second].fullReset();
                        startP = std::make_pair(i,j);
                        cells[startP.first][startP.second].setStart();
                    }
                }
            }
        } else if (event.mouseButton.button == sf::Mouse::Right) { // set end point
            for (int i = 0; i < cells.size(); i++) {
                for (int j = 0; j < cells[i].size(); j++) {
                    if (cells[i][j].getImage().getGlobalBounds().contains(mousePos) && cells[i][j].getCellType() == cell::cellOpt::normal) {
                        cells[endP.first][endP.second].fullReset();
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

void graph::solve(string sol) {
    if (sol == "BFS") {
       
    }
}

void graph::BFS(sf::RenderWindow& window) {
    bool found = false;
    std::queue<cell*> q;
    q.push(&(cells[startP.first][startP.second]));
    q.front()->setVisited(true);

    while (!q.empty() && !found) {
        cell* v = q.front();
        q.pop();
        if (v->getCellType() != cell::cellOpt::startpoint && v->getCellType() != cell::cellOpt::endpoint) {
            v->showSearched();
        }
        draw(window);
        window.display();

        if (v->arrX == endP.first && v->arrY == endP.second) {
            found = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        for (auto& neighbor : v->neighbors) {
            if(!neighbor->getVisited() && neighbor->getCellType() != cell::cellOpt::wall) {
                q.push(neighbor);
                if (neighbor->getCellType() != cell::cellOpt::startpoint && neighbor->getCellType() != cell::cellOpt::endpoint) {
                    neighbor->showsearching();
                }
                neighbor->setVisited(true);
                neighbor->setParent(v);
            }
            
        }
    }
    if(found) {
        drawpath(window);
    }
}

void graph::dijkstra(sf::RenderWindow& window) {

}

void graph::reset() {

    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].fullReset();
        }
    }
}

void graph::findAdjacent() {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            if (i == 0) {
                if (j == 0) {
                    cells[i][j].setNeighbors(&cells[i][j+1]);
                    cells[i][j].setNeighbors(&cells[i+1][j]);
                } else if (j == cells[i].size()-1) {
                    cells[i][j].setNeighbors(&cells[i+1][j]);
                    cells[i][j].setNeighbors(&cells[i][j-1]);
                } else {
                    cells[i][j].setNeighbors(&cells[i][j+1]);
                    cells[i][j].setNeighbors(&cells[i+1][j]);
                    cells[i][j].setNeighbors(&cells[i][j-1]);
                } 
            } else if (i == cells.size()-1) {
                if (j == 0) {
                    cells[i][j].setNeighbors(&cells[i-1][j]);
                    cells[i][j].setNeighbors(&cells[i][j+1]);
                } else if (j == cells[i].size()-1) {
                    cells[i][j].setNeighbors(&cells[i-1][j]);
                    cells[i][j].setNeighbors(&cells[i][j-1]);
                } else {
                    cells[i][j].setNeighbors(&cells[i-1][j]);
                    cells[i][j].setNeighbors(&cells[i][j+1]);
                    cells[i][j].setNeighbors(&cells[i][j-1]);
                }
            } else if (j == 0) {
                cells[i][j].setNeighbors(&cells[i-1][j]);
                cells[i][j].setNeighbors(&cells[i][j+1]);
                cells[i][j].setNeighbors(&cells[i+1][j]);
            } else if (j == cells[i].size()-1) {
                cells[i][j].setNeighbors(&cells[i-1][j]);
                cells[i][j].setNeighbors(&cells[i+1][j]);
                cells[i][j].setNeighbors(&cells[i][j-1]);
            } else {
                cells[i][j].setNeighbors(&cells[i-1][j]);
                cells[i][j].setNeighbors(&cells[i][j+1]);
                cells[i][j].setNeighbors(&cells[i+1][j]);
                cells[i][j].setNeighbors(&cells[i][j-1]);
            }
        }
    }
}

void graph::drawpath(sf::RenderWindow& window) {
    cell* trav = &cells[endP.first][endP.second];

    while (trav != nullptr) {
        if (trav->getCellType() != cell::cellOpt::startpoint && trav->getCellType() != cell::cellOpt::endpoint) {
        trav->showPath();
        }
        trav = trav->getParent();
    }
}