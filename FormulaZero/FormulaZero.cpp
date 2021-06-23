#include "Game.h"   // include Game header file

int main()
{

	Game theGame;
	theGame.loadContent();
	theGame.setUp();
	theGame.run();

	return 0;
}


void Game::setUp() {
	carRenderer.init(&car, window.getWindow(), cars, 0.1f);
	car.init(&carRenderer);

	auto size = window.getWindow()->getSize();
	Vector upperLeft(0, 0);
	Vector upperRight(size.x, 0u);
	Vector lowerLeft(0u, size.y);
	Vector lowerRight(size.x, size.y);

	boundaries[0].init(upperLeft, upperRight);
	boundaries[1].init(upperRight, lowerRight);
	boundaries[2].init(lowerRight, lowerLeft);
	boundaries[3].init(lowerLeft, upperLeft);
}

void Game::loadContent()
{
	sf::IntRect rect(29, 2508, 743 - 28, 2837 - 2508);
	cars.loadFromFile("assets\\cars.png", rect);

}


void Game::run()
{
	int i = 0;
	auto timeOfPreviousFrame = std::chrono::high_resolution_clock::now();

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

		auto timeNow = std::chrono::high_resolution_clock::now();
		long nanosecondsSinceLastUpdate = std::chrono::duration_cast<std::chrono::nanoseconds>(timeNow - timeOfPreviousFrame).count();

		if (nanosecondsSinceLastUpdate > nanosecondsPerFrame)
		{
			timeOfPreviousFrame = timeNow;
			
			update(nanosecondsSinceLastUpdate / 1000);
			draw();

		}

	}  
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

	car.update(ms);
	for (auto& c : boundaries) {
		Collision col = c.isCollidingWith(car.getCollider());
		if (col.is) {
			car.collided(col);
		}
	}

}

void Game::draw()
{
	window.beginFrame();

	car.draw();

	window.displayFrame();
}
