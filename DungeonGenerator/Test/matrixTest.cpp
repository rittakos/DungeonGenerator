#include "pch.h"

#include "../../DungeonGenerator/Math/matrix.hpp"

using namespace Math;

class MatrixTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		m3 = Math::Mat<2, 3, int> (	1, 1, 1,
									2, 2, 2);
		
		m1 = Math::Mat<3, 3, int> (	1, 1, 0,
									2, 1, 0,
									3, 1, 0);

		m2 = Math::Mat<4, 4, int> (	2, 1, 1,  1,
									4, 3, 6,  4,
									6, 7, 21, 16,
									2, 3, 15, 23);

		m4 = Math::Mat<2, 2, float>(-1.6f, 0.0f,
									2.9f, -7.98f);
	}

	void TearDown() override
	{

	}


	Mat<3, 3, int>		zeroMatrix;
	Mat<3, 3, float>	zeroMatrixf;
	Mat<3, 3, int>		m1;
	Mat<4, 4, int>		m2;
	Mat<2, 3, int>		m3;
	Mat<2, 2, float>	m4;
};

TEST_F(MatrixTest, InitTest)
{
	for (int row = 0; row < 3; ++row)
	{
		for(int col = 0; col < 3; ++col)
			EXPECT_EQ(0, zeroMatrix(row, col));
	}
	
}

TEST_F(MatrixTest, LogicalOperatorTest)
{
	Math::Mat r = Math::Mat<2, 2, float>(	-1.6f, 0.0f,
											2.9f, -7.98f);

	EXPECT_EQ(m4, r);
}

TEST_F(MatrixTest, ArithmeticOperatorTest)
{
	Math::Mat r = Math::Mat<2, 3, float>(1.2f, 1.2f, 1.2f,
										2.4f, 2.4f, 2.4f);
	EXPECT_EQ(1.2f * m3, m3 * 1.2f);
	EXPECT_EQ(1.2f * m3, r);

	Math::Mat b = Math::Mat<2, 3, float>(	1.0f, 1.0f, 1.0f,
											2.0f, 2.0f, 2.0f);
	EXPECT_TRUE((r / 1.2f) == b);

	EXPECT_TRUE((m1 + zeroMatrix) == m1);

	EXPECT_TRUE((Math::Mat<2, 3, float>() - r) == -1.0 * r);

	Math::Vec<3, int> v(1, 0, 5);
	Math::Vec<3, int> res(16, 6, 0);
	EXPECT_TRUE((v * m1) == res);

	Mat<2, 3, int>		x(	6, 3, 0,
							12, 6, 0);
	EXPECT_TRUE(m3 * m1 == x);


	Math::Mat<3, 2, int> t(	1, 2, 
							1, 2,
							1, 2);
	EXPECT_TRUE(Math::T(m3) == t);
	
	EXPECT_TRUE(Math::isEqual(Math::det(m2), 12.0f));
}

TEST_F(MatrixTest, IOTest)
{
	std::stringstream my_ss;
	my_ss << m4;
	EXPECT_EQ(my_ss.str(), /*2\t2\n*/"-1.6\t0\t2.9\t-7.98");

	Math::Mat<2, 2, float> in;
	my_ss >> in;
	EXPECT_EQ(in, m4);
}