#pragma once
#include <cmath>
using namespace std;

class Vector
{
public:
	Vector(int x, int y) :x((double)x), y((double)y) {}
	Vector(double x, double y) :x(x), y(y) {}
	Vector(const Vector& v) :x(v.x), y(v.y) {}

	double x, y;

	const Vector& rotate(double degrees) {
		Vector v(x, y);

		double radians = degrees * 3.14159 / 180;

		double _x = cos(radians) * x - sin(radians) * y;
		double _y = sin(radians) * x + cos(radians) * y;

		x = _x;
		y = _y;
		return *this;
	}

	const Vector operator*(double s) const {
		return Vector(x*s, y*s);
	}

	const Vector& operator+=(const Vector& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	const Vector& operator-(const Vector& rhs) {
		return Vector(x-rhs.x, y -rhs.y);
	}

	double length() {
		return sqrt(x * x + y * y);
	}

};

