#include "gtest/gtest.h"
#include "../FormulaZero/Car.h"
#include "../FormulaZero/Vector.h"
#include "CarTest.h"

const double EPSILON = 0.25;
TEST(Car, Accelerate) {

	Car car;

	car.accelerate(0);
	car.update(500);

	EXPECT_DOUBLE_EQ(0.0, car.getPosition().x);

	car.accelerate(1);
	car.update(500);

	//s=0.5at^2
	//s=0.5 * 1 * 0.25 = 0.25
	//v=u+at = 0.5
	EXPECT_DOUBLE_EQ(0.125, car.getPosition().x);

	car.accelerate(2);
	car.update(1000);

	//u= 0.5
	//s=ut+0.5at^2
	//s=0.5* 1 + 0.5 * 2 * 1 = 1.5
	//v=u+at
	//v=0.5 + 2*1 = 2.5 

	EXPECT_DOUBLE_EQ(1.5 + 0.125, car.getPosition().x);

	car.accelerate(0);
	car.update(1000);

	//u = 2.5
	//s= ut +0.5at^2
	//s= 2.5 + 0.5*0*1 = 2.5
	//v= u+at
	//v = 2.5 - air drag
	EXPECT_NEAR(2.5 + 1.5 + 0.125, car.getPosition().x, 0.25);

	//break to zero
	car.accelerate(-2.5);
	car.update(1000);
	double stationaryPosition = car.getPosition().x;

	car.update(1000);
	EXPECT_NEAR(stationaryPosition, car.getPosition().x, 0.25);

}

TEST(Car, NoTurn) {

	Car car;

	car.accelerate(2);
	car.update(1000);
	EXPECT_NEAR(1.0, car.getPosition().x, EPSILON);
	EXPECT_NEAR(0.0, car.getPosition().y, EPSILON);

}
const double ROOT_2 = 1.41421356237;
TEST(Car, DISABLED_Turn) { //TODO: find a way of testing this

	Car car;

	car.accelerate(2);
	car.update(1000);
	//vel is now 2

	car.turn(90);
	car.update(1000);
	EXPECT_NEAR(1.0, car.getPosition().x, EPSILON);
	EXPECT_NEAR(2.0, car.getPosition().y, EPSILON);

	car.turn(-45);
	car.update(1000);

	EXPECT_NEAR(1.0 + ROOT_2, car.getPosition().x, EPSILON);
	EXPECT_NEAR(2.0 + ROOT_2, car.getPosition().y, EPSILON);




}