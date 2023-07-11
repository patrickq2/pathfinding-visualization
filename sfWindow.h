#include <SFML/Graphics.hpp>
#pragma once

class sfWindow {
    sf::RenderWindow window;
    sf::Event event;
    sf::Mouse mouse;
    bool quitGame;
    public:
    sfWindow();
    void update();
    void render();
    bool exit();
};

sfWindow::sfWindow() :
window(sf::VideoMode(300,300),"test")
{
    quitGame = false;
}

void sfWindow::update() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.clear();
    window.draw(shape);
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