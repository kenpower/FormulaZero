#include "gtest/gtest.h"
#include "../FormulaZero/Collider.h"


TEST(Collider, Circles) {

	CircleCollider 
		a(Vector(0,0),2), 
		b(Vector(1, 1), 1),
		c(Vector(3, 0), 0.5);

	EXPECT_TRUE(a.isCollidingWith(b));
	EXPECT_TRUE(b.isCollidingWith(a));
	EXPECT_FALSE(a.isCollidingWith(c));
	EXPECT_FALSE(c.isCollidingWith(a));
}

TEST(Collider, AABBs) {

	AABBCollider
		a(0, 2, 0, 2),
		b(1, 3, 1, 3),
		c(3, 4, 3, 4),
		d(0, 0, 1, 1);

	EXPECT_TRUE(a.isCollidingWith(b));
	EXPECT_TRUE(a.isCollidingWith(d));
	EXPECT_TRUE(d.isCollidingWith(a));


	EXPECT_FALSE(a.isCollidingWith(c));
}

TEST(Collider, AABB_Circle) {

	AABBCollider
		a1(0, 2, 0, 2),
		a2(1, 3, 1, 3),
		a3(0, 1, 0, 1),
		a4(0, 0, 1, 1);

	CircleCollider
		c1(Vector(0, 0), 2),
		c2(Vector(1, 1), 1),
		c3(Vector(3, 0), 0.5),
		c4(Vector(2, 2), 1.4);


	EXPECT_TRUE(a1.isCollidingWith(c1));
	EXPECT_TRUE(a2.isCollidingWith(c2));

	EXPECT_TRUE(c1.isCollidingWith(a1));
	EXPECT_TRUE(c2.isCollidingWith(a2));


	EXPECT_FALSE(a4.isCollidingWith(c3));
	EXPECT_FALSE(c3.isCollidingWith(a4));

	EXPECT_FALSE(c4.isCollidingWith(a3)); //reactangles overlap, but not circle

}

TEST(Collider, Lines) {

	AABBCollider a(0, 2, 0, 2);

	CircleCollider circleOnOrigin(Vector(0, 0), 2);

	//line completely in both
	LineCollider l1(Vector(0.1, 0.1), Vector(1, 1));

	EXPECT_TRUE(l1.isCollidingWith(a));
	EXPECT_TRUE(l1.isCollidingWith(circleOnOrigin));
	EXPECT_TRUE(circleOnOrigin.isCollidingWith(l1));
	EXPECT_TRUE(circleOnOrigin.isCollidingWith(l1));

	//line completely above both
	LineCollider lineAboveBoth(Vector(0, 3), Vector(3, 3));

	EXPECT_FALSE(lineAboveBoth.isCollidingWith(a));
	EXPECT_FALSE(lineAboveBoth.isCollidingWith(circleOnOrigin));
	EXPECT_FALSE(circleOnOrigin.isCollidingWith(lineAboveBoth));
	EXPECT_FALSE(circleOnOrigin.isCollidingWith(lineAboveBoth));

	//line through middle of both
	LineCollider diagLineThroughOrigin(Vector(-10, -10), Vector(10, 10));

	EXPECT_TRUE(diagLineThroughOrigin.isCollidingWith(a));
	EXPECT_TRUE(diagLineThroughOrigin.isCollidingWith(circleOnOrigin));
	EXPECT_TRUE(a.isCollidingWith(diagLineThroughOrigin));
	EXPECT_TRUE(circleOnOrigin.isCollidingWith(diagLineThroughOrigin));

	//line continuation through the circle & box
	LineCollider l4(Vector(+4, +1), Vector(+2.1, +1.0));

	EXPECT_FALSE(l4.isCollidingWith(a));
	EXPECT_FALSE(l4.isCollidingWith(circleOnOrigin));
	EXPECT_FALSE(a.isCollidingWith(l4));
	EXPECT_FALSE(circleOnOrigin.isCollidingWith(l4));

	//line oblique through the circle & box
	LineCollider obliqueHorizonal(Vector(+4, +1), Vector(-4, +1));

	EXPECT_TRUE(obliqueHorizonal.isCollidingWith(a));
	EXPECT_TRUE(obliqueHorizonal.isCollidingWith(circleOnOrigin));
	EXPECT_TRUE(a.isCollidingWith(obliqueHorizonal));
	EXPECT_TRUE(circleOnOrigin.isCollidingWith(obliqueHorizonal));
}

TEST(LineCollider, ClosestPointOnLineToPoint) {

	LineCollider diagLine(Vector(0,0), Vector(1, 1));

	Vector p(0, 0);

	EXPECT_DOUBLE_EQ(0, diagLine.closestPointTo(p).x);
	EXPECT_DOUBLE_EQ(0, diagLine.closestPointTo(p).y);

	Vector a(1, 1);

	EXPECT_DOUBLE_EQ(1, diagLine.closestPointTo(a).x);
	EXPECT_DOUBLE_EQ(1, diagLine.closestPointTo(a).y);

	Vector b(0, 1);

	EXPECT_DOUBLE_EQ(0.5, diagLine.closestPointTo(b).x);
	EXPECT_DOUBLE_EQ(0.5, diagLine.closestPointTo(b).y);

	Vector c(0, 3);

	EXPECT_DOUBLE_EQ(1, diagLine.closestPointTo(c).x);
	EXPECT_DOUBLE_EQ(1, diagLine.closestPointTo(c).y);

	Vector d(0, -3);

	EXPECT_DOUBLE_EQ(0, diagLine.closestPointTo(d).x);
	EXPECT_DOUBLE_EQ(0, diagLine.closestPointTo(d).y);


}
