#include "quaternion.hpp"

#include "math.hpp"
#include <iostream>

namespace Math
{

	Quaternion::Quaternion() : a{0}, b{0}, c{0}, d{0}
	{
	}

	Quaternion::Quaternion(float a) : Quaternion(a, 0, 0, 0)
	{
	}

	Quaternion::Quaternion(Angle angle, Vec3f v, float N)
	{
		angle = angle / 2.0f;
		this->a = cos(angle);
		this->b = v[0] * sin(angle);
		this->c = v[1] * sin(angle);
		this->d = v[2] * sin(angle);
	}

	Quaternion::Quaternion(float a, float b, float c, float d) : a{a}, b{b}, c{c}, d{d}
	{
	}

	Quaternion Quaternion::Im() const
	{
		return Quaternion(0, b, c, d);
	}

	float Quaternion::Re() const
	{
		return a;
	}

	Quaternion Quaternion::conjugation() const
	{
		return Quaternion(a, -b, -c, -d);
	}

	float Quaternion::norm() const
	{
		return sqrt(a * a + b * b + c * c + d * d);
	}

	Quaternion Quaternion::operator-() const
	{
		return (*this) * -1.0f;
	}


	extern Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
	extern Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
	extern Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
	extern Quaternion operator*(float f, const Quaternion& q);
	extern Quaternion operator*(const Quaternion& q, float f);
	extern std::ostream& operator<<(std::ostream& os, const Quaternion& q);
}