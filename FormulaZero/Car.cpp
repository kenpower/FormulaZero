#include "Car.h"

void Car::update(double millisecondsSinceLastUpdate)
{
	const double AIR_DRAG = 0.98;
	const double STEERING_RESTORE = 0.001;

	double time = millisecondsSinceLastUpdate / 1000;

	double distance = velocity * time + 0.5 * acceleration * time * time;
	
	velocity = velocity*AIR_DRAG + acceleration * time;

	cout << "ms since last:" << millisecondsSinceLastUpdate << '\n';
	cout << "turn rate    :" << turnRate << '\n';
	turnRate = turnRate * (1 - STEERING_RESTORE * time);

	pos += direction * distance;

	direction.rotate(distance * turnRate);

	acceleration = 0;
}
