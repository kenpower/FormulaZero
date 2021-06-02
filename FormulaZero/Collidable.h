#pragma once
#include "Collider.h"
class Collidable
{
public:
	virtual const Collider& getCollider() = 0;
	virtual void collided(const Collision&) = 0;
};

