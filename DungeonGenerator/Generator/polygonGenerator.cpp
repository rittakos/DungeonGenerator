#include "polygonGenerator.hpp"
#include "polygon.hpp"
#include "vector.hpp"
#include "random.h"
#include "transformation.hpp"


namespace Generator
{
	Geometry::Polygon BaseConvexPolygonGeneratorAlgorithm::generate(int verticesCount)
	{
        assert(verticesCount >= 3);

		std::vector<Math::Angle> angles = getAngles(verticesCount);
        float radius = getRadius();

        float X0 = Random::GetFloat(-radius, radius);
        Math::Vec2f firstPoint = Math::Vec2f(X0, std::sqrtf(radius * radius - X0 * X0));
		
		std::vector<Math::Vec2f> points;
        points.push_back(firstPoint);
		
        for (int idx = 1; idx < verticesCount; ++idx)
        {
            Math::Vec2f newPoint = Geometry::rotate(points[idx - 1], angles[idx]);
            newPoint = newPoint * Random::GetFloat(1.0f - parameters.radiusDistribution, 1.0f + parameters.radiusDistribution);
            points.push_back(newPoint);
        }

        for (Math::Vec2f p : points)
            std::cout << p << std::endl;

		Geometry::Polygon randomPolygon(points);
		return randomPolygon;
	}

	std::vector<Math::Angle> BaseConvexPolygonGeneratorAlgorithm::getAngles(int verticesCount) const
	{
		std::vector<Math::Angle> angles;

		for(float a : Random::GetFloatWithFixedSum(verticesCount, Math::Constant::Pi * 2.0f, parameters.angleDistribution))
			angles.push_back(Math::Angle(a));

		return angles;
	}

	float BaseConvexPolygonGeneratorAlgorithm::getRadius() const
	{
		float radiusX = std::abs(parameters.maxCoord[0] - parameters.minCoord[0]) / 2.0f;
		float radiusY = std::abs(parameters.maxCoord[1] - parameters.minCoord[1]) / 2.0f;
		float radiusMax = (radiusX + radiusY) / 2.0f;

		return Random::GetFloat(radiusMax * parameters.sizeDistribution, radiusMax);
	}

	BaseConvexPolygonGeneratorAlgorithm::BaseConvexPolygonGeneratorAlgorithm(GenerationParameters parameters) : parameters(parameters)
	{
	}

}


namespace Generator
{
	void PolygonGenerator::setCustomGeneratorAlgorithm(std::shared_ptr<PolygonGeneratorAlgorithm> customAlgorithm)
	{
		assert(type == Custom && customAlgorithm != nullptr);
		if (type == Custom)
			algorithm = customAlgorithm;
	}


	PolygonGenerator::PolygonGenerator(int verticesCount, PolygonGeneratorType type) 
		: verticesCount(verticesCount), type(type)
	{
        assert(verticesCount >= 3);

		GenerationParameters regularPolygonParameters(Math::Vec2f(-100.0f, -100.0f), Math::Vec2f(100.0f, 100.0f), 0.0f, 0.0f, 0.0f);

		switch (type)
		{
		case Generator::BaseConvex:
			algorithm = std::make_shared<BaseConvexPolygonGeneratorAlgorithm>(regularPolygonParameters);
			break;
		case Generator::Custom:
			algorithm = nullptr;
			break;
		default:
			algorithm = nullptr;
			break;
		}
	}


	Geometry::Polygon PolygonGenerator::generate() const
	{
		assert(algorithm != nullptr);
		return algorithm->generate(verticesCount);
	}
}