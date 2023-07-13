#include "graph.h"
#include <SFML/Graphics.hpp>
#pragma once

class sfWindow {
    sf::RenderWindow window;
    sf::Event event;
    sf::Mouse mouse;
    bool quitGame;
    graph maze;
    public:
    sfWindow();
    void update();
    void render();
    bool exit();
};

sfWindow::sfWindow() :
window(sf::VideoMode(25*32,25*32),"test")
{
    quitGame = false;
}

void sfWindow::update() {
    window.clear();
    maze.update(window);
    window.display();
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