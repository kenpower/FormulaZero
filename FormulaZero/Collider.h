#pragma once
#include <stdexcept>
#include "Vector.h"
#include "Collision.h"
#include "CollisionChecker.h"

class Collider {
public:
	virtual Collision isCollidingWithAABB(const AABBCollider&) const = 0;
	virtual Collision isCollidingWithCircle(const CircleCollider&) const = 0;
	virtual Collision isCollidingWithLine(const LineCollider&) const = 0;
	virtual Collision isCollidingWith(const Collider&) const = 0;
	virtual const Vector normal(const Vector&) const = 0;
	virtual const string toString() const = 0;

};

class AABBCollider : public Collider {
	double left, right, bottom, top;

public:
	friend class CollisionChecker;

	Collision isCollidingWithAABB(const AABBCollider& other) const{
		return CollisionChecker::areColliding(*this, other);
	}

	Collision isCollidingWithCircle(const CircleCollider& circle) const{
		return CollisionChecker::areColliding(*this, circle);
	}
	Collision isCollidingWithLine(const LineCollider& line) const{
		return CollisionChecker::areColliding(*this, line);
	};

	Collision isCollidingWith(const Collider& collider) const{
		return collider.isCollidingWithAABB(*this);
	}

	AABBCollider(double l, double r, double b, double t) :left(l), right(r), bottom(b), top(t) {}

	bool contains(const Vector& pt) const{
		return pt.x > left && pt.x < right&& pt.y > bottom && pt.y < top;
	}

	const Vector normal(const Vector&) const {
		throw std::logic_error("Not Implmented!");
	}

	const string toString() const{
		return string("[ l:" + to_string(left) + ", r:" + to_string(right) + ", b:" + to_string(bottom) + " , t:" + to_string(top) + "]");
	};

	typedef int OutCode;
	const OutCode INSIDE = 0; // 0000
	const OutCode LEFT = 1;   // 0001
	const OutCode RIGHT = 2;  // 0010
	const OutCode BOTTOM = 4; // 0100
	const OutCode TOP = 8;    // 1000

	OutCode outCode(const Vector& p) const// from Cohen–Sutherland algorithm
	{
		OutCode code = INSIDE;          // initialised as being inside of [[clip window]]

		if (p.x < left)           // to the left of clip window
			code |= LEFT;
		else if (p.x > right)      // to the right of clip window
			code |= RIGHT;
		if (p.y < bottom)           // below the clip window
			code |= BOTTOM;
		else if (p.y > top)      // above the clip window
			code |= TOP;

		return code;
	}
};

class CircleCollider : public Collider {
private:
	Vector pos;
	double radius;

public:
	friend class CollisionChecker;

	Collision isCollidingWithAABB(const AABBCollider& aabbCollider)  const {
		return CollisionChecker::areColliding(aabbCollider, *this);
	}
	Collision isCollidingWithCircle(const CircleCollider& other)  const {
		return CollisionChecker::areColliding(other, *this);
	}

	Collision isCollidingWithLine(const LineCollider& line)  const {
		return CollisionChecker::areColliding(*this, line);
	}

	Collision isCollidingWith(const Collider& collider)  const {
		return collider.isCollidingWithCircle(*this);
	}

	CircleCollider(Vector p, double r) :pos(p), radius(r) {}

	bool contains(const Vector& pt) const{
		Vector d = pos - pt;
		return d.length() < radius;
	}

	const Vector normal(const Vector&) const {
		throw std::logic_error("Not Implmented");
	}

	const string toString() const{
		return string("[ p:" + pos.toString() + ", r:" + to_string(radius) +"]");
	};

};

class LineCollider : public Collider {
private:
	Vector start, end;

public:
	friend class CollisionChecker;
	
	Collision isCollidingWithAABB(const AABBCollider& other)  const {
		return CollisionChecker::areColliding(other, *this);
	}
	Collision isCollidingWithCircle(const CircleCollider& other)  const {
		return CollisionChecker::areColliding(other, *this);
	}
	Collision isCollidingWithLine(const LineCollider& other) const{
		return CollisionChecker::areColliding(other, *this);
	}

	Collision isCollidingWith(const Collider& collider)  const {
		return collider.isCollidingWithLine(*this);
	}
	
	LineCollider(){}

	LineCollider(Vector start, Vector end) :start(start), end(end) {}

	void init(Vector& _start, Vector& _end) {
		start = _start;
		end = _end;
	}

	Vector closestPointTo(const Vector& point) const {
		Vector p = Vector(point - start);

		Vector line = Vector(end - start);
		Vector edge = line.norm();

		Vector closestPoint = start + (edge * (p * edge));
		double t = (p * edge) / line.lengthSq();

		if (0 < t && t < 1) return closestPoint;

		return t <= 0 ? start : end;

	}

	const Vector normal(const Vector& _ = Vector()) const {
		return (end - start).perp().norm();
	}

	const string toString() const{
		return string("[ s:" + start.toString() + ", e:" + end.toString() + "]");
	};

};