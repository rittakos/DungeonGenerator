#include <vector>
#include <vector.hpp>


namespace Generator
{
	template<class Point>
	class ControlPointGenerator
	{
	public:
		virtual std::vector<Point> generate() const = 0;
	};


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