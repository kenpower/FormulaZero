#pragma once

#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include <chrono>
#include "Window.h"

//#include "Globals.h"   // include Global header file
//#include "Player.h"   // include Player header file

#include "Car.h"

class Game
{
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.


	Window window;
	sf::Texture cars;

	Car car;
	SpriteRenderer carRenderer;


public:	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent();
	void	run();
	void	update(long);
	void	draw();
};
