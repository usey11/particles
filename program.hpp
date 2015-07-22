#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class programLoop
{
public:
  programLoop(sf::RenderWindow &w);
  void loop();
private:
  sf::RenderWindow *window;
};
