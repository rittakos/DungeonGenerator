#include "pch.h"

#include "../../DungeonGenerator/Math/angle.hpp"

class AngleTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		a1 = 180.0_deg;
		a2 = Math::Angle(Math::Constant::Pi);
		a3 = 60.0_deg;
		a4 = 45.0_deg;
		a5 = 1.34_rad;
		a6 = 20.3_rad;
		a7 = -0.53_rad;
	}

	void TearDown() override
	{

	}


	Math::Angle a0;
	Math::Angle a1;
	Math::Angle a2;
	Math::Angle a3;
	Math::Angle a4;
	Math::Angle a5;
	Math::Angle a6;
	Math::Angle a7;
};


TEST_F(AngleTest, InitTest)
{
	EXPECT_EQ(a1, a2);
	EXPECT_EQ(a3.getRad(), Math::Constant::Pi / 3.0f);
	EXPECT_EQ(a4.getRad(), Math::Constant::Pi / 4.0f);
	EXPECT_EQ(a0.getDeg(), a0.getRad());
}

TEST_F(AngleTest, ArithmeticOperatorTest)
{
	EXPECT_EQ(a1 + a2, 360.0_deg);
	EXPECT_EQ(a3 - a4, 15.0_deg);
	EXPECT_EQ(a3 - (-a4), 105.0_deg);
	EXPECT_EQ(2.0f * a4, 90.0_deg);
	EXPECT_EQ(a3 / 2.0, 30.0_deg);
}

TEST_F(AngleTest, TrigonometrialOperatorTest)
{
	EXPECT_TRUE(Math::isEqual(sin(180.0_deg), 0.0));
	EXPECT_TRUE(Math::isEqual(cos(60.0_deg), 0.5));
	EXPECT_TRUE(Math::isEqual(tan(45.0_deg), 1.0));

	EXPECT_TRUE(Math::asin(0.0) == 0.0_deg);
	EXPECT_TRUE(Math::acos(0.5) == 60.0_deg);
	EXPECT_TRUE(Math::atan(1.0) == 45.0_deg);
}

TEST_F(AngleTest, LogicalOperatorTest)
{

}

TEST_F(AngleTest, OtherTest)
{

}