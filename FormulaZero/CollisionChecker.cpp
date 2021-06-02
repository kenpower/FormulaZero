#pragma once
#include "Collider.h"
#include "CollisionChecker.h"


Collision CollisionChecker::areColliding(const AABBCollider& aabb1, const AABBCollider& aabb2) {
	if (aabb1.top < aabb2.bottom || aabb1.bottom > aabb2.top)
		return Collision::no();
	if (aabb1.left > aabb2.right || aabb1.right < aabb2.left)
		return Collision::no();

	return Collision(Vector(0,0));
};

Collision CollisionChecker::areColliding(const AABBCollider& aabb, const CircleCollider& circle) {
	if (circle.pos.x + circle.radius < aabb.left || circle.pos.x - circle.radius> aabb.right)
		return Collision::no();

	if (circle.pos.y + circle.radius < aabb.bottom || circle.pos.x - circle.radius > aabb.top)
		return Collision::no();

	if (
		!circle.contains(Vector(aabb.left, aabb.bottom)) &&
		!circle.contains(Vector(aabb.left, aabb.top)) &&
		!circle.contains(Vector(aabb.right, aabb.bottom)) &&
		!circle.contains(Vector(aabb.right, aabb.top))
		) return Collision::no();

	return Collision(Vector(0,0));
};



Collision CollisionChecker::areColliding(const CircleCollider& circle1, const CircleCollider& circle2) {
	Vector d = circle1.pos - circle2.pos;
	return d.length() < (circle1.radius + circle2.radius);
};

Collision CollisionChecker::areColliding(const CircleCollider& circle, const LineCollider& line) {
	Vector closest = line.closestPointTo(circle.pos);

	if (Vector(circle.pos - closest).length() < circle.radius) {
		Vector circleCentreNotTouching = closest + line.normal() * circle.radius;
		Vector mtv = circleCentreNotTouching - circle.pos;
		return Collision(mtv);
	}

	return Collision::no();
};

Collision CollisionChecker::areColliding(const LineCollider& line1, const LineCollider& line2) {

	double s1_x, s1_y, s2_x, s2_y;
	s1_x = line1.end.x - line1.start.x;     s1_y = line1.end.y - line1.start.y;
	s2_x = line2.end.x - line2.start.x;     s2_y = line2.end.y - line2.start.y;

	double s, t;
	s = (-s1_y * (line1.start.x - line2.start.x) + s1_x * (line1.start.y - line2.start.y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (line1.start.y - line2.start.y) - s2_y * (line1.start.x - line2.start.x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		//// Collision detected
		//if (i_x != NULL)
		//	*i_x = line1.start.x + (t * s1_x);
		//if (i_y != NULL)
		//	*i_y = line1.start.y + (t * s1_y);
		return Collision(Vector(0,0));
	}

	return Collision::no(); // No collision

};

Collision CollisionChecker::areColliding(const AABBCollider& aabb, const LineCollider& line) {
	if (aabb.contains(line.end) || aabb.contains(line.start))
		return Collision(Vector(0,0));
	if ((aabb.outCode(line.start) & aabb.outCode(line.end)) != 0)
		return Collision::no();

	Vector lt(aabb.left, aabb.top);
	Vector rt(aabb.right, aabb.top);
	Vector lb(aabb.left, aabb.bottom);
	Vector rb(aabb.right, aabb.bottom);

	//if (areColliding(line, LineCollider(lt, rt))) return Collision(Vector(0,0));

	//not fully implemented yet

	return Collision(Vector(0,0));
};