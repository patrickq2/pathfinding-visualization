#include "cell.h"
#include "graph.h"
#include <SFML/Graphics.hpp>
#pragma once

class sfWindow {
    bool lock;
    graph maze;
    sf::RenderWindow window;
    sf::Event event;
    sf::Mouse mouse;
    bool quitGame;
    public:
    sfWindow();
    void draw();
    void update();
    bool exit();
};

sfWindow::sfWindow() :
window(sf::VideoMode(25*32,25*32),"test")
{
    quitGame = false;
    lock = false;
}

void sfWindow::draw() {
    window.clear();
    maze.draw(window);
    window.display();
}

void sfWindow::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        maze.changeMode();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        maze.reset();
        lock = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // A star
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // Dijkstra
        lock = true;
        maze.dijkstra(window);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        //BFS
        lock = true;
        maze.BFS(window);
    }
    if (!lock) {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            maze.update(mousePos, event);
            /*
            if (mode == walls) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < graph.size(); i++) {
                        for (int j = 0; j < graph[i].size(); j++) {
                            if(graph[i][j].getImage().getGlobalBounds().contains(mousePos)) {
                                graph[i][j].change();
                            }
                        }
                    }
                }
            }
            if (mode == points) {
                if (event.mouseButton.button == sf::Mouse::Left) { // set start point
                    for (int i = 0; i < graph.size(); i++) {
                        for (int j = 0; j < graph[i].size(); j++) {
                            if (graph[i][j].getImage().getGlobalBounds().contains(mousePos)) {
                                graph[][]
                                graph[i][j].setStart();
                            }
                        }
                    }
                } else if (event.mouseButton.button == sf::Mouse::Right) { // set end point
                    for (int i = 0; i < graph.size(); i++) {
                        for (int j = 0; j < graph[i].size(); j++) {
                            if (graph[i][j].getImage().getGlobalBounds().contains(mousePos)) {
                                graph[i][j].setEnd();
                            }
                        }
                    }
                }
            }*/
            event.type = sf::Event::MouseButtonReleased;
        }
    }
}

bool sfWindow::exit(){
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			quitGame = true;
		}
	}
	return quitGame;
}