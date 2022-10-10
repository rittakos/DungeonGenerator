#include "transformation.hpp"


Mat<3, 3, float> Geometry::getRotationMatrix(Angle angle, RotationAxis axis)
{
	float cos = Math::cos(angle);
	float sin = Math::sin(angle);

	Mat3x3f rotationMatrix{ 1.0f, 0.0f,  0.0f,
								0.0f,  cos,  -sin,
								0.0f,  sin,  -cos };

	return rotationMatrix;
}

Vec3f Geometry::rotate(const Vec3f& v, Angle angle, const Vec3f& axis)
{
	Math::Quaternion q(angle, axis);
	Math::Quaternion x(0, v[0], v[1], v[2]);
	Math::Quaternion rotated = q * x * q.conjugation();

	return Math::Vec3f(rotated.i(), rotated.j(), rotated.k());
}

Vec2f Geometry::rotate(const Vec2f& v, Angle angle)
{
	Vec3f result = rotate(Vec3f(v[0], v[1], 0.0f), angle, Math::Constant::z);

	return Math::Vec2f(result[0], result[1]);
}
