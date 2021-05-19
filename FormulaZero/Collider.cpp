#include "Collider.h"

bool CollisionChecker::areColliding(const AABBCollider& aabb1, const AABBCollider& aabb2) {
	if (aabb1.top < aabb2.bottom || aabb1.bottom > aabb2.top)
		return false;
	if (aabb1.left > aabb2.right || aabb1.right < aabb2.left)
		return false;

	return true;
};

bool CollisionChecker::areColliding(const AABBCollider& aabb, const CircleCollider& circle){
	if (circle.pos.x + circle.radius < aabb.left || circle.pos.x - circle.radius> aabb.right)
		return false;

	if (circle.pos.y + circle.radius < aabb.bottom || circle.pos.x - circle.radius > aabb.top)
		return false;

	if (
		!circle.contains(Vector(aabb.left, aabb.bottom)) &&
		!circle.contains(Vector(aabb.left, aabb.top)) &&
		!circle.contains(Vector(aabb.right, aabb.bottom)) &&
		!circle.contains(Vector(aabb.right, aabb.top))
		) return false;

	return true;
};



bool CollisionChecker::areColliding(const CircleCollider& circle1, const CircleCollider& circle2){
	Vector d = circle1.pos - circle2.pos;
	return d.length() < (circle1.radius + circle2.radius);
};

bool CollisionChecker::areColliding(const CircleCollider& circle, const LineCollider& line){
	if (circle.contains(line.start) || circle.contains(line.end))
		return true;
	if (line.distanceTo(circle.pos) < circle.radius)
		return true;

	return false;
};

bool CollisionChecker::areColliding(const LineCollider& line1, const LineCollider& line2){

	double s1_x, s1_y, s2_x, s2_y;
	s1_x = line1.end.x - line1.start.x;     s1_y = line1.end.y - line1.start.y;
	s2_x = line2.end.x - line2.start.x;     s2_y = line2.end.y - line2.start.y;

	float s, t;
	s = (-s1_y * (line1.start.x - line2.start.x) + s1_x * (line1.start.y - line2.start.y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (line1.start.y - line2.start.y) - s2_y * (line1.start.x - line2.start.x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		//// Collision detected
		//if (i_x != NULL)
		//	*i_x = line1.start.x + (t * s1_x);
		//if (i_y != NULL)
		//	*i_y = line1.start.y + (t * s1_y);
		return true;
	}

	return false; // No collision
	
};

bool CollisionChecker::areColliding(const AABBCollider& aabb, const LineCollider& line) {
	if (aabb.contains(line.end) || aabb.contains(line.start))
		return true;
	if ((aabb.outCode(line.start) & aabb.outCode(line.end) ) != 0)
		return false;

	Vector lt(aabb.left, aabb.top);
	Vector rt(aabb.right, aabb.top);
	Vector lb(aabb.left, aabb.bottom);
	Vector rb(aabb.right, aabb.bottom);

	if (areColliding(line, LineCollider(lt, rt))) return true;


	return true;
};