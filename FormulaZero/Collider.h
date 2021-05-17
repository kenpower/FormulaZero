#pragma once
#include "Vector.h"

class AABBCollider;
class CircleCollider;


class Collider {
protected:
	virtual bool isCollidingWithAABB(AABBCollider&) = 0;
	virtual bool isCollidingWithCircle(CircleCollider&) = 0;
public:
	virtual bool isCollidingWith(Collider&) = 0;

	friend class CircleCollider;
	friend class AABBCollider;

};

class AABBCollider : public Collider {
	double left, right, bottom, top;
protected:

	bool isCollidingWithAABB(AABBCollider& other) {
		if (top < other.bottom || bottom > other.top)
			return false;
		if (left > other.right || right < other.left)
			return false;

		return true;
	}

	bool isCollidingWithCircle(CircleCollider&);

public:
	AABBCollider(double l, double r, double b, double t) :left(l), right(r), bottom(b), top(t) {}

	bool isCollidingWith(Collider& collider) {
		return collider.isCollidingWithAABB(*this);
	}

};

class CircleCollider : public Collider {
private:

	Vector pos;
	double radius;

	bool isCollidingWithAABB(AABBCollider& aabbCollider) {
		return true;
	}
	bool isCollidingWithCircle(CircleCollider& other) {
		Vector d = pos - other.pos;
		return d.length() < (radius + other.radius);
	}

public:
	CircleCollider(Vector p, double r) :pos(p), radius(r) {}
	

	bool isCollidingWith(Collider& collider) {
		return collider.isCollidingWithCircle(*this);
	}

	

};