#pragma once
#include "Vector.h"

class AABBCollider;
class CircleCollider;
class LineCollider;

class CollisionChecker {
public:
	static bool areColliding(const AABBCollider&, const AABBCollider&);
	static bool areColliding(const AABBCollider&, const CircleCollider&);
	static bool areColliding(const AABBCollider&, const LineCollider&);
	static bool areColliding(const CircleCollider&, const CircleCollider&);
	static bool areColliding(const CircleCollider&, const LineCollider&);
	static bool areColliding(const LineCollider&, const LineCollider&);

};


class Collider {
public:
	virtual bool isCollidingWithAABB(AABBCollider&) = 0;
	virtual bool isCollidingWithCircle(CircleCollider&) = 0;
	virtual bool isCollidingWithLine(LineCollider&) = 0;
	virtual bool isCollidingWith(Collider&) = 0;

};

class AABBCollider : public Collider {
	double left, right, bottom, top;

public:
	friend class CollisionChecker;

	bool isCollidingWithAABB(AABBCollider& other) {
		return CollisionChecker::areColliding(*this, other);
	}

	bool isCollidingWithCircle(CircleCollider& circle) {
		return CollisionChecker::areColliding(*this, circle);
	}
	bool isCollidingWithLine(LineCollider& line) {
		return CollisionChecker::areColliding(*this, line);
	};

	bool isCollidingWith(Collider& collider) {
		return collider.isCollidingWithAABB(*this);
	}

	AABBCollider(double l, double r, double b, double t) :left(l), right(r), bottom(b), top(t) {}

	bool contains(const Vector& pt) const{
		return pt.x > left && pt.x < right&& pt.y > bottom && pt.y < top;
	}

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

	bool isCollidingWithAABB(AABBCollider& aabbCollider) {
		return CollisionChecker::areColliding(aabbCollider, *this);
	}
	bool isCollidingWithCircle(CircleCollider& other) {
		return CollisionChecker::areColliding(other, *this);
	}

	bool isCollidingWithLine(LineCollider& line) {
		return CollisionChecker::areColliding(*this, line);
	}

	bool isCollidingWith(Collider& collider) {
		return collider.isCollidingWithCircle(*this);
	}

	CircleCollider(Vector p, double r) :pos(p), radius(r) {}

	bool contains(const Vector& pt) const{
		Vector d = pos - pt;
		return d.length() < radius;
	}

};

class LineCollider : public Collider {
private:
	Vector start, end;

public:
	friend class CollisionChecker;
	
	bool isCollidingWithAABB(AABBCollider& other) {
		return CollisionChecker::areColliding(other, *this);
	}
	bool isCollidingWithCircle(CircleCollider& other) {
		return CollisionChecker::areColliding(other, *this);
	}
	bool isCollidingWithLine(LineCollider& other) {
		return CollisionChecker::areColliding(other, *this);
	}

	bool isCollidingWith(Collider& collider) {
		return collider.isCollidingWithLine(*this);
	}
	
	LineCollider(Vector start, Vector end) :start(start), end(end) {}

	Vector closestPointTo(const Vector& point) const {
		Vector p = Vector(point - start);

		Vector line = Vector(end - start);
		Vector edge = line.norm();

		Vector closestPoint = start + (edge * (p * edge));
		double t = (p * edge) / line.lengthSq();

		if (0 < t && t < 1) return closestPoint;

		return t <= 0 ? start : end;

	}



};