#pragma once
#include "Vector.h"
struct Collision
{
	Vector mtv;
	bool is;

	Collision(const Vector& mtv) :mtv(mtv), is(true) {};
	Collision(bool is) :is(is) {};

	static Collision no() {
		return Collision(false);
	}
};

