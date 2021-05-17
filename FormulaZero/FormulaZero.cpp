

#include "Game.h"   // include Game header file


//class CircleCollider;
//class BoxCollider;
//
//class Checker {
//public:
//	virtual bool checkCircle(CircleCollider* c) = 0;
//	virtual bool checkBox(BoxCollider* c) = 0;
//};
//
//class Collider {
//public:
//	Checker* checker;
//	virtual Checker* getChecker() = 0;
//	virtual bool isColliding(Checker* checker) = 0;
//};
//
//class BoxCollider: public Collider {
//public:
//	const char* bname = "Box";
//	Checker* getChecker() { return checker; }
//	bool isColliding(Checker* checker) {
//		return checker->checkBox(this);
//	}
//
//};
//
//class CircleCollider : public Collider {
//public:
//	const char* cname = "Circle";
//	Checker* getChecker() { return checker; }
//	bool isColliding(Checker* checker) {
//		return checker->checkCircle(this);
//	}
//
//};
//
//
//class BoxChecker:public Checker {
//public:
//	BoxChecker(BoxCollider* b) :box(b) {}
//	BoxCollider* box;
//	bool checkCircle(CircleCollider* c) { 
//		std::cout << box->bname << c->cname << "\n";
//		return true; };
//	bool checkBox(BoxCollider* c) { std::cout << box->bname << c->bname << "\n"; return true; };
//};
//
//class CircleChecker: public Checker {
//public:
//	CircleChecker(CircleCollider* c) :circle(c) {}
//	CircleCollider* circle;
//	bool checkCircle(CircleCollider* c) { std::cout << circle->cname << c->cname << "\n"; return true; };
//	bool checkBox(BoxCollider* c) { std::cout << circle->cname << c->bname << "\n"; return true; };
//};

class AABBCollider;
class CircleCollider;


class Collider {
public:
	virtual bool isColliding(Collider*) = 0;
	virtual bool isCollidingWithAABB(AABBCollider*) = 0;
	virtual bool isCollidingWithCircle(CircleCollider*) = 0;

};

class AABBCollider : public Collider {
public:
	const char* bname = "Box";

	bool isColliding(Collider* collider) {
		return collider->isCollidingWithAABB(this);
	}

	bool isCollidingWithAABB(AABBCollider* aabbCollider) {
		std::cout << bname << aabbCollider->bname;
		return true;
	}

	bool isCollidingWithCircle(CircleCollider* checker); //defer definition to avoid circular dependency

};

class CircleCollider : public Collider {
public:
	const char* cname = "Circle";

	bool isColliding(Collider* collider) {
		return collider->isCollidingWithCircle(this);
	}

	bool isCollidingWithAABB(AABBCollider* aabbCollider) {
		std::cout << cname << aabbCollider->bname;
		return true;
	}
	bool isCollidingWithCircle(CircleCollider* circleCollider) {
		std::cout << cname << circleCollider->cname;
		return true;
	}

};

bool AABBCollider::isCollidingWithCircle(CircleCollider* circleCollider) {
	std::cout << bname << circleCollider->cname;
	return true;
}

int main()
{
	//AABBCollider* b = new AABBCollider;
	//b->checker = new AABBCollider(b);

	//CircleCollider* c = new CircleCollider;
	//c->checker = new CircleChecker(c);

	//Collider* bb = b;
	//Collider* cc = c;

	//bool iscolliding = cc->isColliding(bb->getChecker());

	Collider* b2 = new AABBCollider;
	Collider* c2 = new CircleCollider;

	b2->isColliding(c2);



	//Game theGame;
	//theGame.loadContent();
	//theGame.run();

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
