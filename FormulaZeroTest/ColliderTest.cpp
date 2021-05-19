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

	CircleCollider c(Vector(0, 0), 2);

	LineCollider l1(Vector(0, 0), Vector(1, 1));


	EXPECT_TRUE(l1.isCollidingWith(a));
	EXPECT_TRUE(l1.isCollidingWith(c));
	EXPECT_TRUE(c.isCollidingWith(l1));
	EXPECT_TRUE(c.isCollidingWith(l1));

	LineCollider l2(Vector(0, 3), Vector(3, 3));

	EXPECT_FALSE(l2.isCollidingWith(a));
	EXPECT_FALSE(l2.isCollidingWith(c));
	EXPECT_FALSE(c.isCollidingWith(l2));
	EXPECT_FALSE(c.isCollidingWith(l2));

	LineCollider l3(Vector(-10, -10), Vector(10, 10));

	EXPECT_TRUE(l3.isCollidingWith(a));
	EXPECT_TRUE(l3.isCollidingWith(c));
	EXPECT_TRUE(a.isCollidingWith(l3));
	EXPECT_TRUE(c.isCollidingWith(l3));

	LineCollider l4(Vector(-10, +1), Vector(-0.1, +1.0));

	EXPECT_FALSE(l4.isCollidingWith(a));
	EXPECT_FALSE(l4.isCollidingWith(c));
	EXPECT_FALSE(a.isCollidingWith(l4));
	EXPECT_FALSE(c.isCollidingWith(l4));
}