#pragma once
#include "Drawable.h"
#include "SpriteRenderer.h"

class Car : public Drawable
{
	double acceleration{ 0.0 };
	double velocity{ 0.0 };
	double direction{ 0.0 };
	double turnRate{ 0.0 };
	Vector pos{ 0,0 };
	SpriteRenderer* renderer;

	const double MAX_TURN_RATE = 1.5;

public:
	const Vector& getPosition() { return pos; }
	const double getRotation() { return direction; }
	void accelerate(double _accleration) { acceleration += _accleration; }
	void turn(double _turn) { if (abs(turnRate + _turn) < MAX_TURN_RATE) turnRate += _turn; }
	void draw() { renderer->draw(); }
	void init(SpriteRenderer* sr) { renderer = sr; }
	void reset() {
		direction = 0;
		turnRate = 0;
		pos.x = 0;
		pos.y = 0;
	}

	void update(double millisecondsSinceLastUpdate);
};

