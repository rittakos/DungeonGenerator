#include "geometry.hpp"
#include <equationSystem.hpp>

namespace Geometry
{

	Math::Vec2f calcTriangleOutterCircleCenter(std::array<Math::Vec2f, 3> points)
	{
		Math::Vec2f A = points[0];
		Math::Vec2f B = points[1];
		Math::Vec2f C = points[2];

		Math::Vec2f AB = B - A;
		Math::Vec2f AC = C - A;

		Math::Vec2f Hab = (A + B) / 2.0f;
		Math::Vec2f Hac = (A + C) / 2.0f;


		Math::LinearEquationSystem<2> les;

		Math::LinearEquation<2> e1(AB[0] * Hab[0] + AB[1] * Hab[1], { AB[0], AB[1] });
		Math::LinearEquation<2> e2(AC[0] * Hac[0] + AC[1] * Hac[1], { AC[0], AC[1] });

		les.addLinearEquation(e1);
		les.addLinearEquation(e2);

		if (!les.solve())
			throw(std::exception("Not Solvable Linear Equation System"));

		std::optional<std::vector<float>> solution = les.getSolution();

		Math::Vec2f O(solution.value()[0], solution.value()[1]);

		return O;
	}

	std::optional<Edge> getCommonEdge(Polygon polygon1, Polygon polygon2)
	{
		// MUST ha nem pontosan egyeznek az elek csak reszben fedik egymast
		for (const Edge& edge : polygon1.getEdges())
		{
			for (const Edge& otherEdge : polygon2.getEdges())
			{
				if (edge == otherEdge)
					return edge;
			}
		}

		return {};
	}

}
