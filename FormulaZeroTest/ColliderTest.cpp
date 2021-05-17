#include "gtest/gtest.h"
#include "../FormulaZero/Collider.h"


TEST(Collider, Circles) {

	CircleCollider 
		a(Vector(0,0),2), 
		b(Vector(1, 1), 1),
		c(Vector(3, 0), 0.5);

	EXPECT_TRUE(a.isCollidingWith(b));
	EXPECT_FALSE(a.isCollidingWith(c));
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