#include <SFML/Graphics.hpp>
#include "program.hpp"


int main()
{

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	programLoop p1(window);
	p1.loop();

	return 0;
}
