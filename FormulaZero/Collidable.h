#pragma once
#include "Collider.h"
class Collidable
{
public:
	virtual Collider& getCollider() = 0;
	virtual void collided(Vector&) = 0;
};

