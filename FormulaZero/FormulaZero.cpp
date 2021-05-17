

#include "Game.h"   // include Game header file


int main()
{

	Game theGame;
	theGame.loadContent();
	theGame.run();

	return 0;
}

Game::Game()
// Default constructor
{
}

void Game::loadContent()
{
	//2508, 2837, 29, 743
	sf::IntRect rect(29, 2508, 743 - 28, 2837 - 2508);
	cars.loadFromFile("assets\\cars.png", rect);
	carRenderer.init(&car, window.getWindow(), cars, 0.1f);
	car.init(&carRenderer);
}


void Game::run()
// This function contains the main game loop which controls the game. 
{
	int i = 0;
	auto timeOfPreviousFrame = std::chrono::high_resolution_clock::now();

	//auto end = std::chrono::high_resolution_clock::now();
	//std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - timeOfPreviousFrame).count() << "ns" << std::endl;

	double nanosecondsPerFrame = 1000000000.0f / 60.0f;
	while (true)//window.isOpen())
	{
		// check if the close window button is clicked on
		//sf::Event event;
		//while (window.pollEvent(event))
		//{
		//	if (event.type == sf::Event::Closed)
		//		window.close();
		//}

		auto now = std::chrono::high_resolution_clock::now();
		auto nanosecondsSinceLastUpdate = std::chrono::duration_cast<std::chrono::nanoseconds>(now - timeOfPreviousFrame).count();

		if (nanosecondsSinceLastUpdate > nanosecondsPerFrame)
		{
			timeOfPreviousFrame = now;
			
			update(nanosecondsSinceLastUpdate / 1000);
			draw();

		}

	}  // end while loop

}

void Game::update(long ms)
// This function takes the keyboard input and updates the game world
{
	//get keyboard input

	double TURN = 0.025;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		car.turn(-TURN);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		car.turn(+TURN);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		car.accelerate(0.001);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		car.accelerate(-0.001);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		car.reset();
	}


	// update any game variables here ...

	car.update(ms);

}

void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	window.beginFrame();

	car.draw();

	window.displayFrame();
}
