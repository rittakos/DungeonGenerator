#include "pch.h"

#include "vector.hpp"

using namespace Math;

class VectorTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		nullVector = Math::Vec3f(0.0f, 0.0f, 0.0f);

		v1 = Math::Vec3f(1.0f, 0.0f, 0.0f);
		v2 = Math::Vec3f(5.0f, 0.5f, -7.0f);
		v3 = Math::Vec3f(-1.9f, 100000.566645654f, -0.0f);
		v4 = Math::Vec3f(3.7f, 8.5f, -0.8f);
	}

	void TearDown() override
	{

	}


	Math::Vec3f nullVector;
	Math::Vec3f v0;
	Math::Vec3f v1;
	Math::Vec3f v2;
	Math::Vec3f v3;
	Math::Vec3f v4;
};

TEST_F(VectorTest, Fault)
{
	EXPECT_TRUE(false);
}

TEST_F(VectorTest, InitVec3Test)
{
	EXPECT_EQ(v0[0], 0);
	EXPECT_EQ(v0[0], 0);
	EXPECT_EQ(v0[0], 0);

	EXPECT_EQ(v3[0], -1.9f);
	EXPECT_EQ(v3[1], 100000.566645654f);
	EXPECT_EQ(v3[2], 0.0f);
}

TEST_F(VectorTest, CopyVec3Test)
{
	Math::Vec3f v = v3;

	EXPECT_EQ(v[0], -1.9f);
	EXPECT_EQ(v[1], 100000.566645654f);
	EXPECT_EQ(v[2], 0.0f);
}

TEST_F(VectorTest, LengthVec3Test)
{
	EXPECT_EQ(v0.length(), 0);
	EXPECT_EQ(v1.length(), 1);
	EXPECT_EQ(v2.length(), 8.61684397f);
}

TEST_F(VectorTest, LogicalOperatorVec3Test)
{
	Math::Vec3f v;
	EXPECT_TRUE(v == v0);

	v = Math::Vec3f{ 6.1f, 4.0f, 3.6f };
	EXPECT_FALSE(v == v1);

	v = Math::Vec3f{ -1.9f, 100000.566645654f, 0.0f };
	EXPECT_TRUE(v == v3);
}

TEST_F(VectorTest, ArithmeticlOperatorVec3fTest)
{
	EXPECT_TRUE(nullVector == v1 - v1);							//-
	EXPECT_TRUE(v2 - v4 == Math::Vec3f(1.3f, -8.0f, -6.2f));	//-
	EXPECT_TRUE(v2 - nullVector == v2);							//-

	EXPECT_TRUE(v2 + v4 == Math::Vec3f(8.7f, 9.0f, -7.8f));		//+
	EXPECT_TRUE(v2 + nullVector == v2);							//+

	EXPECT_TRUE(v2 + v2 == 2 * v2);								//+, *
	EXPECT_TRUE(3.5f * nullVector == nullVector);				//*
	EXPECT_TRUE(-2.9f * v2 == -2.9f * v2);						//*

	EXPECT_TRUE(v2 / -1.3f == Math::Vec3f(-3.846153846f, -0.3846153846f, 5.384615385f)); //:
	EXPECT_TRUE(v2 / -1.3f == Math::Vec3f(-3.846153846f, -0.3846153846f, 5.384615385f)); //:
	//EXPECT_THROW(v2 / 0.0f, Math::ZeroDevisionException);

	EXPECT_TRUE(v2 * nullVector == 0.0f);						//*
	EXPECT_EQ(v2 * v2, v2.length() * v2.length());				//*
	EXPECT_EQ(v2 * v4, 28.35f);									//*
}

TEST_F(VectorTest, NormaliseVec3fTest)
{
	v2.normalise();
	EXPECT_TRUE(abs(v2.length() - 1.0f) < Math::Constant::epsilon);
	EXPECT_TRUE(abs(v2.getNormalised().length() - 1.0f) < Math::Constant::epsilon);
}

TEST_F(VectorTest, VecNfTest)
{
	Math::Vec<5> v;

	for (int idx = 0; idx < 5; ++idx)
		EXPECT_EQ(v[idx], 0.0f);

	v = Math::Vec<5>(0.0f, 1.0f, 2.0f, 3.0f, 4.0f);
	for (int idx = 0; idx < 5; ++idx)
		EXPECT_EQ(v[idx], idx);
}

TEST_F(VectorTest, AngleVec3fTest)
{
	Math::Vec3f v(0.0f, 1.0f, 0.0f);
	EXPECT_EQ(v1.angleWith(v1), 0.0_deg);
	EXPECT_EQ(v1.angleWith(v), 90.0_deg);
	v = Math::Vec3f(1.0f, 1.0f, 0.0f);
	EXPECT_EQ(v1.angleWith(v), 45.0_deg);

}

TEST_F(VectorTest, IOTest)
{
	std::stringstream my_ss;
	my_ss << v4;
	EXPECT_EQ(my_ss.str(), "3.7\t8.5\t-0.8");

	Math::Vec3f in;
	my_ss >> in;
	EXPECT_EQ(in, v4);
}