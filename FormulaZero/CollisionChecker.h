#pragma once
class AABBCollider;
class CircleCollider;
class LineCollider;

class CollisionChecker {
public:
	static Collision areColliding(const AABBCollider&, const AABBCollider&);
	static Collision areColliding(const AABBCollider&, const CircleCollider&);
	static Collision areColliding(const AABBCollider&, const LineCollider&);
	static Collision areColliding(const CircleCollider&, const CircleCollider&);
	static Collision areColliding(const CircleCollider&, const LineCollider&);
	static Collision areColliding(const LineCollider&, const LineCollider&);
};
