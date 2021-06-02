#include "Car.h"

void Car::update(double millisecondsSinceLastUpdate)
{
	const double AIR_DRAG = 0.98;
	const double STEERING_RESTORE = 0.99;

	double time = millisecondsSinceLastUpdate / 1000;

	double distance = velocity * time + 0.5 * acceleration * time * time;
	
	velocity = velocity*AIR_DRAG + acceleration * time;

	turnRate *= STEERING_RESTORE;

	pos += direction * distance;

	direction.rotate(distance * turnRate);

	acceleration = 0;
}
