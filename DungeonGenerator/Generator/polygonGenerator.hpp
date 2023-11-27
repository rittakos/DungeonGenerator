#pragma once

#include "generatorAlgorithm.hpp"
#include <memory>
#include "polygon.hpp"

namespace Generator
{
	// MUST ki kene pofozni, atvinni amit lehet cppbe

	class PolygonGeneratorAlgorithm// : public GeneratorAlgorithm
	{
	public:
		virtual Geometry::Polygon generate(int verticesCount) = 0;

		virtual ~PolygonGeneratorAlgorithm() = default;
	};

	enum PolygonGeneratorType { BaseConvex, Custom };

	struct GenerationParameters
	{
		const Math::Vec2f minCoord;
		const Math::Vec2f maxCoord;
		const float angleDistribution;	//in radian
		const float radiusDistribution; //in percentage
		const float sizeDistribution;	//in percentage 

		GenerationParameters(Math::Vec2f minCoord, Math::Vec2f maxCoord,
			float angleDistribution, float radiusDistribution, float sizeDistribution) :
			minCoord(minCoord),
			maxCoord(maxCoord),
			angleDistribution(angleDistribution),
			radiusDistribution(radiusDistribution),
			sizeDistribution(sizeDistribution)
		{
		}
	};

	class BaseConvexPolygonGeneratorAlgorithm final : public PolygonGeneratorAlgorithm
	{
	private:
		const GenerationParameters parameters;

		std::vector<Math::Angle>	getAngles(int verticesCount) const;
		float						getRadius() const;

	public:
		BaseConvexPolygonGeneratorAlgorithm(GenerationParameters parameters);
		virtual Geometry::Polygon generate(int verticesCount) override;

		virtual ~BaseConvexPolygonGeneratorAlgorithm() = default;
	};

	//template <class Algorithm = BaseConvexPolygonGeneratorAlgorithm>
	class PolygonGenerator
	{
	private:
		std::shared_ptr<PolygonGeneratorAlgorithm> algorithm;
		int verticesCount;
		PolygonGeneratorType type;

	public:
		void setCustomGeneratorAlgorithm(std::shared_ptr<PolygonGeneratorAlgorithm> customAlgorithm);

		PolygonGenerator(int verticesCount, PolygonGeneratorType type = BaseConvex);
		Geometry::Polygon generate() const;
	};
}
