#pragma once
#include <cmath>
#include <string>
using namespace std;

const double PI{ 3.141592653589793238463 };

class Vector
{
public:
	Vector():x(0), y(0) {}
	Vector(int x, int y) :x((double)x), y((double)y) {}	
	Vector(unsigned x, unsigned int y) :x((double)x), y((double)y) {}
	Vector(double x, double y) :x(x), y(y) {}
	Vector(const Vector& v) :x(v.x), y(v.y) {}

	double x, y;

	const Vector& rotate(double degrees) {
		Vector v(x, y);

		double radians = degrees * PI / 180;

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

	const Vector operator+(const Vector& rhs) const {
		return Vector(x + rhs.x, y + rhs.y);
	}

	const Vector operator-(const Vector& rhs) const{
		return Vector(x-rhs.x, y -rhs.y);
	}

	double length() const {
		return sqrt(lengthSq());
	}

	double lengthSq() const {
		return x * x + y * y;
	}

	double operator*(const Vector& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	const Vector norm() const {
		double len = length();
		return Vector(x/len, y /len);
	}

	const std::string toString() const {
		return string("(" + to_string(x) + ", " + to_string(y) + " )");
	}

	Vector perp() const{
		return Vector(-y, x);
	}

	Vector reflect(const Vector& _n) const {
		Vector n = _n.norm();
		Vector d = *this;

		return d - n * 2 * (d * n);
	}


	double angle() const {
		double quadrantAdjustment{ 0 };
		if (x < 0) quadrantAdjustment = PI;
		if (x > 0 && y<0) quadrantAdjustment = 2*PI;

		return ((atan(y / x) + quadrantAdjustment )/ ( 2 * PI)) * 360;
	}

	static const Vector fromPolar(double angle, double radius) {

		double angleRads = (angle / 360) * 2 * PI;
		return Vector(radius * cos(angleRads), radius * sin(angleRads));
	}


};


