#include <vector>
#include <vector.hpp>
#include "generatorAlgorithm.hpp"


namespace Generator
{
	template<int D>
	static Math::Vec<D, float> GetRandomFloatVector(Math::Vec<D, float> min, Math::Vec<D, float> max)
	{
		Math::Vec<D, float> randomVector;
		for (int idx = 0; idx < D; ++idx)
		{
			randomVector[idx] = Random::GetFloat(min[idx], max[idx]);
		}

		return randomVector;
	}

	
	class Grid2DControlPointGenerator : public ControlPointGenerator<Math::Vec2f>
	{
		const Math::Vec2f leftUpCorner;
		const Math::Vec2f rightDownCorner;
		
		const size_t height;
		const size_t width;


	public:
		Grid2DControlPointGenerator(size_t width, size_t height);

		std::vector<Math::Vec2f> generate() const override;
	};
}