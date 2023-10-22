#pragma once

#include <array>

#include "vector.hpp"

namespace Geometry
{
	Math::Vec2f calcTriangleOutterCircleCenter(std::array<Math::Vec2f, 3> points);
}