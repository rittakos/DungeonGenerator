#pragma once

#include "vector.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"

using namespace Math;

namespace Geometry
{
	enum RotationAxis { X, Y, Z };


	Mat<3, 3, float> getRotationMatrix(Angle angle, RotationAxis axis = RotationAxis::Z);

	Vec3f rotate(const Vec3f& v, Angle angle, const Vec3f& axis);
	

	Vec2f rotate(const Vec2f& v, Angle angle);
	

	template<int D, class Type> 
	Vec<D, Type> shift(Vec<D, Type> base, Vec<D, Type> shiftVektor)
	{
		return base + shiftVektor;
	}
}