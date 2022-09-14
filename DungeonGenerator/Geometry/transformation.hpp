#pragma once

#include "vector.hpp"
#include "matrix.hpp"

namespace Math
{
	enum RotationAxis { X, Y, Z };


	Mat<3, 3, float> getRotationMatrix(Angle angle, RotationAxis axis = RotationAxis::Z)
	{
		float cos = Math::cos(angle);
		float sin = Math::sin(angle);

		Mat3x3f rotationMatrix   {  1, 0  ,  0  ,
									0, cos, -sin,
									0, sin, -cos };

		return rotationMatrix;
	}

	template<class Type>
	Vec<3, Type> rotate(const Vec<3, Type>& v, Angle angle, RotationAxis axis = RotationAxis::Z/*, Vec<3, Type> center = Vec<3, Type>()*/)
	{
		return v * getRotationMatrix(angle, axis);
	}
}