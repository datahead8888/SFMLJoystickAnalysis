#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <chrono>

using namespace std;

void handleEvent(sf::Event & event);
void doUpdate(float timeElapsed);
void doRender(sf::RenderWindow & window);

//Global variables - a quick solution for a simple prototype for now
float x = 300, y = 300;  //Position of circle object
sf::Vector2f velocity(0.0f, 0.0f); //Velocity of circle object
bool running = true;  //True if app is running
const float SPEED = 50.0f; //Speed to assign to each component of velocity when moving

int main()
{
	//Test joystick connectivity
	if (!sf::Joystick::isConnected(0))
	{
		cerr << "First joystick is not connected" << endl;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL");

	sf::Clock clock; //Clock to represent time elapsed

	//Main loop
	while (running)
	{
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			handleEvent(windowEvent);
		}

		float timeElapsed = clock.restart().asSeconds();
		doUpdate(timeElapsed);
		doRender(window);
	}

	return 0;
}

//This method responds to SFML events
//Parameter windowEvent - the SFML event to interpret
void handleEvent(sf::Event & windowEvent)
{

	switch(windowEvent.type)
	{
		case sf::Event::Closed:
			running = false;
			break;
		//Keyboard events
		case sf::Event::KeyPressed:
			switch (windowEvent.key.code)
			{
				case sf::Keyboard::Escape:
					running = false;
					break;
				case sf::Keyboard::Up:
					velocity.x = 0.0f; //This is not ideal for diagonal movement but is fine for a first prototype
					velocity.y = -SPEED;
					cout << "Up key pressed" << endl;
					break;
				case sf::Keyboard::Right:
					velocity.x = SPEED;
					velocity.y = 0.0f;
					cout << "Right key pressed" << endl;
					break;
				case sf::Keyboard::Down:
					velocity.x = 0.0f;
					velocity.y = SPEED;
					cout << "Down key pressed" << endl;
					break;
				case sf::Keyboard::Left:
					velocity.x = -SPEED;
					velocity.y = 0.0f;
					cout << "Left key pressed" << endl;

					break;
			}
			break;
		//Joystick events - for now just print them onscreen for our analysis
		case sf::Event::JoystickMoved:
			switch (windowEvent.joystickMove.axis)
			{
				case sf::Joystick::X:
					cout << "Joystick X: " << windowEvent.joystickMove.position << endl;
					break;
				case sf::Joystick::Y:
					cout << "Joystick Y: " << windowEvent.joystickMove.position << endl;
					break;
			}
			break;
	}

}

//Physics update method
//timeElapsed - amount of time elapsed for this time step
void doUpdate(float timeElapsed)
{
	//Integrate the change in position
	x += velocity.x * timeElapsed;
	y += velocity.y * timeElapsed;
}

//Rendering method
//Parameter window - the SFML window object used
void doRender(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);

	sf::CircleShape shape(10);
	shape.setFillColor(sf::Color(100, 250, 50));
	shape.setPosition(sf::Vector2f(x,y));

	window.draw(shape);

	window.display();
}
