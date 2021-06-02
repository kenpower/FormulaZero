#pragma once
#include <iostream>
#include "Drawable.h"
#include "Collidable.h"
#include "SpriteRenderer.h"

class Car : public Drawable, Collidable
{
	double acceleration{ 0.0 };
	double velocity{ 0.0 };
	Vector direction{ 1, 0 };
	double turnRate{ 0.0 };
	Vector pos{ 0,0 };
	SpriteRenderer* renderer{NULL};
	CircleCollider collider{ Vector(0, 0), 0 };

	const double MAX_TURN_RATE = 1.5;

public:

	const Vector& getPosition() { return pos; }
	const double getRotation() { return direction.angle(); }
	void accelerate(double _accleration) { acceleration += _accleration; }
	void turn(double _turn) { if (abs(turnRate + _turn) < MAX_TURN_RATE) turnRate += _turn; }
	void draw() { renderer->draw(); }
	void init(SpriteRenderer* sr) { 
		renderer = sr;
		reset(); 
	}

	void reset() {
		direction = Vector(1, 0);
		turnRate = 0;
		pos.x = 100;
		pos.y = 100;
	}

	void update(double millisecondsSinceLastUpdate);

	const Collider& getCollider() {
		collider = CircleCollider(pos, 30);
		return collider;
	}

	void collided(const Collision& c) {
		pos += c.mtv;
		Vector n = c.mtv.norm();
		direction = direction.reflect(n);
		//std::cout << "touch" << normal.toString() << '\n';
		//std::cout << "pos  " << pos.toString() << '\n';

	}
};

