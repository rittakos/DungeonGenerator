#include "pch.h"

//#include "vector.hpp"
#include "polygon.hpp"



class PolygonTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		points.push_back(Math::Vec2f(0.0f, 0.0f));
		points.push_back(Math::Vec2f(1.0f, 2.0f));
		points.push_back(Math::Vec2f(2.0f, 0.0f));
		points.push_back(Math::Vec2f(1.0f, 1.0f));

		p.addPoint(points[0]);
		p.addPoint(points[1]);
		p.addPoint(points[2]);
		p.addPoint(points[3]);
	}

	void TearDown() override
	{

	}

	std::vector<Math::Vec2f> points;

	Geometry::Polygon p;
};


TEST_F(PolygonTest, AreaTest)
{
	EXPECT_TRUE(Math::isEqual(p.Area(), 1.0f));
}