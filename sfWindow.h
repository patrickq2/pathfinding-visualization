#include "cell.h"
#include <SFML/Graphics.hpp>
#pragma once

class sfWindow {
    enum modes {walls, points};
    modes mode;
    sf::RenderWindow window;
    sf::Event event;
    sf::Mouse mouse;
    bool quitGame;
    std::vector<std::vector<cell>> graph;
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
    mode = walls;
    for (int i = 0; i < 25; i++) {
        graph.push_back(std::vector<cell>());
        for (int j = 0; j < 25; j++) {
            cell temp(j*32.0f, i*32.0f);
            graph[i].push_back(temp);
        }
    }
}

void sfWindow::draw() {
    window.clear();
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            window.draw(graph[i][j].getImage());
        }
    }
    window.display();
}

void sfWindow::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (mode == walls) {
                mode = points;
            } else {
                mode = walls;
            }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        //reset
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // A star
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // Dijikstras
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (mode == walls) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
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

        }
        event.type = sf::Event::MouseButtonReleased;
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