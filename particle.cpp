#include "particle.hpp"
#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>

using namespace std;



shape_system::shape_system(){

	acceleration = 200;
	numberOfShapes = 0;
};

void shape_system::gravity(sf::Time tElapsed)
{


	for (int i = 0; i < numberOfShapes; i++)
	{
		float dt = tElapsed.asSeconds();
		float u = shapesVelocities[i].j;
		float v = dt*acceleration + u;
		float s = u*dt + 0.5*acceleration*dt*dt;

		shapesVelocities[i].j = v;
		//cout << "v = " << v;

		sf::Vector2f  pos = shapes[i]->getPosition();
		pos.y = pos.y + s;
		shapes[i]->setPosition(pos);
	}
}

void shape_system::addCircle(int r, sf::Vector2f pos)
{
	shapes.push_back(new sf::CircleShape(r));
	shapes[numberOfShapes]->setPosition(pos);
	numberOfShapes++;
	velocity v;
	v.i = 0;
	v.j = 0;
	shapesVelocities.push_back(v);
}


void shape_system::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < numberOfShapes; i++){
		window.draw(*shapes[i]);
	}

}


particle_system::particle_system(int particles, sf::Vector2u  sizeWindow) :
va(sf::Points, particles), sizeOfWindow(sizeWindow)
{
	srand(time(NULL));
	numberOfParticles = particles;
	for (int i = 0; i < numberOfParticles; i++)
	{
		velocity k;
		k.i = 0;
		k.j = 0;
		velocities.push_back(k);
		va[i].color = sf::Color::White;
	}
	colourRandom();
}

void particle_system::setSize(int size)
{
	va.resize(size);
	for (int i = numberOfParticles - 1; i > size; i--){
		velocities.pop_back();
	}
	numberOfParticles = size;

}

void particle_system::randomVs()
{

	for (int i = 0; i < numberOfParticles; i++)
	{
		int horizontal = (rand() % 800) - 400;
		int vertical = (rand() % 800) - 400;
		velocities[i].i = horizontal;
		velocities[i].j = vertical;
	}
}

void particle_system::draw(sf::RenderWindow &window, sf::View view)
{
	window.setView(view);
	window.draw(va);
	window.setView(window.getDefaultView());
}

void particle_system::randomPos()
{
	for (int i = 0; i < numberOfParticles; i++)
	{
		int horizontal = (rand() % sizeOfWindow.x);
		int vertical = (rand() % sizeOfWindow.y);
		va[i].position.x = horizontal;
		va[i].position.y = vertical;
		//cout << i << " to " << horizontal << "," << vertical << " with v " << velocities[i].i << "," << velocities[i].j << endl;
	}
}

void particle_system::move(sf::Time time)
{
	float dt = time.asSeconds();

	for (int i = 0; i < numberOfParticles; i++){

		va[i].position.x = va[i].position.x + dt*velocities[i].i;
		va[i].position.y = va[i].position.y + dt*velocities[i].j;
	}
}

void particle_system::checkBoundry()
{
	for (int i = 0; i < numberOfParticles; i++)
	{
		if (va[i].position.x > static_cast<float>(sizeOfWindow.x) || va[i].position.x < 0){
			velocities[i].i = velocities[i].i * (-1);

		}
		else if (va[i].position.y > static_cast<float>(sizeOfWindow.y) || va[i].position.y < 0){
			velocities[i].j = velocities[i].j * (-1);

		}
	}
}

void particle_system::colourRandom()
{
	srand(time(0));
	int random = 0;

	for (int i = 0; i < numberOfParticles; i++)
	{
		random = rand() % 4;
		switch (random)
		{
		case 0:
			va[i].color = sf::Color::Blue;
			break;
		case 1:
			va[i].color = sf::Color::Cyan;
			break;
		case 2:
			va[i].color = sf::Color::Green;
			break;
		case 3:
			va[i].color = sf::Color::Red;
			break;
		}
	}
}

void particle_system::colourScale()
{
	for (int i = 0; i < numberOfParticles; i++)
	{
		va[i].color.g = 55;
		va[i].color.a = 255;
		va[i].color.b = 255 * (va[i].position.x / static_cast<float>(sizeOfWindow.x));
		va[i].color.r = 255 * (va[i].position.y / static_cast<float>(sizeOfWindow.y));
	}
}

void particle_system::towardsPoint(sf::Vector2i p)
{
	for (int i = 0; i < numberOfParticles; i++)
	{
		float magnitude = sqrt((velocities[i].i)*(velocities[i].i) + (velocities[i].j)*(velocities[i].j));

		float difx = static_cast<float>(p.x) - va[i].position.x;
		float dify = static_cast<float>(p.y) - va[i].position.y;

		float tNormalise = sqrt((difx)*(difx)+(dify)*(dify));

		float normalX = difx / tNormalise;
		float normalY = dify / tNormalise;

		velocities[i].i = normalX*magnitude;
		velocities[i].j = normalY*magnitude;
	}
}
