#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <thread>
#include <cmath>
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
    void aStar(sf::RenderWindow& window);
    double heuristic(cell* node);
    void fullReset();
    void pReset();
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
                        cells[startP.first][startP.second].reset();
                        startP = std::make_pair(i,j);
                        cells[startP.first][startP.second].setStart();
                    }
                }
            }
        } else if (event.mouseButton.button == sf::Mouse::Right) { // set end point
            for (int i = 0; i < cells.size(); i++) {
                for (int j = 0; j < cells[i].size(); j++) {
                    if (cells[i][j].getImage().getGlobalBounds().contains(mousePos) && cells[i][j].getCellType() == cell::cellOpt::normal) {
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

void graph::solve(string sol) {
    if (sol == "BFS") {
       
    }
}

void graph::fullReset() {
    endP = std::make_pair(0,0);
    startP = std::make_pair(0,0);
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].reset();
        }
    }
}

void graph::pReset() {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].setVisited(false);
            cells[i][j].setParent(nullptr);
            if (cells[i][j].getCellType() == cell::cellOpt::searched || cells[i][j].getCellType() == cell::cellOpt::searching || cells[i][j].getCellType() == cell::cellOpt::path) {
                cells[i][j].reset();
            }
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
    bool found = false;
    std::priority_queue<std::pair<double,cell*>, std::vector<std::pair<double,cell*>>, std::greater<std::pair<double,cell*>>> pq;

    std::vector<std::vector<double>> gDist(cells.size(), std::vector<double>(cells[0].size(), INFINITY));

    gDist[startP.first][startP.second] = 0;

    pq.push(std::make_pair(0, &cells[startP.first][startP.second]));

    while (!pq.empty() && !found) {
        cell* v = pq.top().second;
        pq.pop();

        if (v->getCellType() != cell::cellOpt::startpoint && v->getCellType() != cell::cellOpt::endpoint) {
            v->showSearched();
        }

        draw(window);
        window.display();

        if (v->arrX == endP.first && v->arrY == endP.second) {
            found = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (!v->getVisited()) {
            for (auto& neighbor : v->neighbors) {
                if(gDist[neighbor->arrX][neighbor->arrY] > gDist[v->arrX][v->arrY] + 1 && !neighbor->getVisited() && neighbor->getCellType() != cell::cellOpt::wall) {
                    gDist[neighbor->arrX][neighbor->arrY] = gDist[v->arrX][v->arrY] + 1;
                    neighbor->setParent(v);
                    if (neighbor->getCellType() != cell::cellOpt::startpoint && neighbor->getCellType() != cell::cellOpt::endpoint) {
                        neighbor->showsearching();
                    }
                    pq.emplace(std::make_pair(gDist[neighbor->arrX][neighbor->arrY], neighbor)); //using lazy deletion, much simpler than updating priority queue
                }
            }
        }
        v->setVisited(true);
    }
    if (found) {
        drawpath(window);
    }
}

double graph::heuristic(cell* node) {
    return std::abs(node->arrX - endP.first) + std::abs(node->arrY - endP.second);
}

void graph::aStar(sf::RenderWindow& window) {
        bool found = false;
    std::priority_queue<std::pair<double,cell*>, std::vector<std::pair<double,cell*>>, std::greater<std::pair<double,cell*>>> pq;

    std::vector<std::vector<double>> gDist(cells.size(), std::vector<double>(cells[0].size(), INFINITY));
    std::vector<std::vector<double>> fDist(cells.size(), std::vector<double>(cells[0].size(), INFINITY));

    gDist[startP.first][startP.second] = 0;
    fDist[startP.first][startP.second] = 0;

    pq.push(std::make_pair(0, &cells[startP.first][startP.second]));

    while (!pq.empty() && !found) {
        cell* v = pq.top().second;
        pq.pop();

        if (v->getCellType() != cell::cellOpt::startpoint && v->getCellType() != cell::cellOpt::endpoint) {
            v->showSearched();
        }

        draw(window);
        window.display();

        if (v->arrX == endP.first && v->arrY == endP.second) {
            found = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (!v->getVisited()) {
            for (auto& neighbor : v->neighbors) {
                if(gDist[neighbor->arrX][neighbor->arrY] > gDist[v->arrX][v->arrY] + 1 && !neighbor->getVisited() && neighbor->getCellType() != cell::cellOpt::wall) {
                    gDist[neighbor->arrX][neighbor->arrY] = gDist[v->arrX][v->arrY] + 1;
                    fDist[neighbor->arrX][neighbor->arrY] = gDist[neighbor->arrX][neighbor->arrY] + heuristic(neighbor);
                    neighbor->setParent(v);
                    if (neighbor->getCellType() != cell::cellOpt::startpoint && neighbor->getCellType() != cell::cellOpt::endpoint) {
                        neighbor->showsearching();
                    }
                    pq.emplace(std::make_pair(fDist[neighbor->arrX][neighbor->arrY], neighbor)); //using lazy deletion, much simpler than updating priority queue
                }
            }
        }
        v->setVisited(true);
    }
    if (found) {
        drawpath(window);
    }
}