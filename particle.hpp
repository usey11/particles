#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
using namespace std;

struct velocity
{
	int i;
	int j;
};

class shape_system
{
public:
	shape_system();
	//~shape_system();

	void addCircle(int, sf::Vector2f);

	void gravity(sf::Time);


	void draw(sf::RenderWindow &window);

private:
	float acceleration = 50;
	vector<velocity> shapesVelocities;
	vector<sf::Shape*> shapes;
	int numberOfShapes = 0;
};

class particle_system
{
public:
	particle_system(int, sf::Vector2u);
	void setSize(int);
	void randomVs();
	void randomPos();
	void draw(sf::RenderWindow &window, sf::View);
	void move(sf::Time);
	void checkBoundry();
	void colourRandom();
	void colourScale();
	void towardsPoint(sf::Vector2i);
private:
	vector<velocity> velocities;
	sf::VertexArray va;
	sf::Vector2u sizeOfWindow;
	int numberOfParticles;
};

