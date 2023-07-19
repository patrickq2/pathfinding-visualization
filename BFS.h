/*#include <vector>
#include <queue>
#include "cell.h"
#pragma once

class BFS {
    public:
    BFS::BFS();
    void findPath(std::vector<std::vector<cell>>& maze, std::pair<int,int> src, std::pair<int, int> end);
};

BFS::BFS() {

}

void BFS::findPath(std::vector<std::vector<cell>>& maze, std::pair<int,int> src, std::pair<int, int> end) {
    std::queue<cell*> q;
    q.push(&maze[src.first][src.second]);
    maze[src.first][src.second].setVisited(true);

    while (!q.empty()) {
        cell* v = q.front();
        q.pop();

        for (int i = 0; i < v->getNeighbors().size(); i++) {
            if (!v->getNeighbors()[i]->getVisited()) {
                q.push(v->getNeighbors()[i]);
                v->getNeighbors()[i]->setVisited(true);
                v->getNeighbors()[i]->showSearched();
            }
        }
    }
}*/