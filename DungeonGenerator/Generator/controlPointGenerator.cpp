#include "controlPointGenerator.hpp"

namespace Generator
{
	Grid2DControlPointGenerator::Grid2DControlPointGenerator(size_t width, size_t height) : width(width), height(height)
	{
	}

	std::vector<Math::Vec2f> Grid2DControlPointGenerator::generate() const
	{
		std::vector<Math::Vec2f> points;

		float i = 0.0f;

		for (int col = 0; col < width; col++)
		{
			for (int row = 0; row < height; row++)
			{
				Math::Vec2f P(row * 100.0f, col * 100.0f);

				points.push_back(P + GetRandomFloatVector<2>(Math::Vec2f(), Math::Vec2f(10.0f, 10.0f)));
			}
		}

		/*for (int col = 0; col < 10; col++)
		{
			for (int row = 0; row < 10; row++)
			{
				points.push_back(Math::Vec2f{ row * 100.0f, col * 100.0f + i });

				i += 20.0f;
			}
		}*/

		return points;
	}

}
