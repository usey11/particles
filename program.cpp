#include "program.hpp"

programLoop::programLoop(sf::RenderWindow &w)
{
	window = &w;
}

void programLoop::loop()
{
  int error  = 0;

  while (window->isOpen())
  {
	  sf::Event event;
	  while (window->pollEvent(event))
	  {
		  if (event.type == sf::Event::Closed)
			  window->close();
	  }

	  window->clear();
	  window->display();
  }
}
