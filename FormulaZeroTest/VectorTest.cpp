#include "gtest/gtest.h"
#include "../FormulaZero/Vector.h"

TEST(Vector, Rotate) {
	Vector v(1, 0);
	v.rotate(90);

	EXPECT_NEAR(0.0, v.x, 0.0001);
	EXPECT_NEAR(1.0, v.y, 0.0001);

}