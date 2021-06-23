#pragma once

#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include <chrono>
#include "Window.h"

#include "Car.h"
#include "Collider.h"
#include "Collision.h"
#include "SFMLSpriteRenderer.h"

class Game
{
	Window window;
	sf::Texture cars;

	Car car;
	SFMLSpriteRenderer carRenderer;

	LineCollider boundaries[4];

public:	
	void	loadContent();
	void	setUp();
	void	run();
	void	update(long);
	void	draw();
};
