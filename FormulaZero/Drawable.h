#pragma once
#include "Vector.h"

class Drawable
{
public:
	virtual const Vector& getPosition() = 0;
	virtual const double getRotation() = 0;

	virtual void draw() = 0;

};

