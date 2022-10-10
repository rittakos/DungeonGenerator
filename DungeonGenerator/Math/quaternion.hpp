#pragma once
#include <ostream>
#include "angle.hpp"
#include "vector.hpp"

namespace Math
{
	class Quaternion final
	{
	private:
		float a;
		float b;
		float c;
		float d;

		struct TrigonometricForm
		{

		};

	public:
		Quaternion();
		Quaternion(float a);
		Quaternion(Angle angle, Vec3f v, float N = 0.0f);
		Quaternion(float a, float b, float c, float d);

		Quaternion	Im() const;
		float		Re() const;
		Quaternion	conjugation() const;
		float		norm() const;

		float i() const { return b; }
		float j() const { return c; }
		float k() const { return d; }


		Quaternion operator-() const;

		friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
		friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
		friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
		friend Quaternion operator*(float f, const Quaternion& q);
		friend Quaternion operator*(const Quaternion& q, float f);
		friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
	};

	inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
	{
		float a = q1.a + q2.a;
		float b = q1.b + q2.b;
		float c = q1.c + q2.c;
		float d = q1.d + q2.d;
		return Quaternion(a, b, c, d);
	}

	inline Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
	{
		return q1 + (-q2);
	}

	inline Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
	{

		//		 Q	|	 1	 i	 j	 k	-1	-i	-j	-k
		//----------|-------------------------------------
		//		 1	|	 1	 i	 j	 k	-1	-i	-j	-k
		//		 i	|	 i	-1	 k	-j	-i	 1	 k	 j
		//		 j	|	 j	-k	-1	 i	-j	 k	 1	-i
		//		 k	|	 k	 j	-i	-1	-k	-j	 i	 1
		//		-1	|	-1	-i	-j	-k	 1	 i	 j	 k
		//		-i	|	-i	 1	-k	 j	 i	-1	 k	-j
		//		-j	|	-j	 k	 1	-i	 j	-k	-1	 i
		//		-k	|	-k	-j	 i	 1	 k	 j	-i	-1

		float Sq1 = q1.Re();
		float Sq2 = q2.Re();
		Quaternion Vq1 = q1.Im();
		Quaternion Vq2 = q2.Im();

		float		part1 = Sq1 * Sq2;
		Quaternion	part2 = Vq1 * Sq2;
		Quaternion	part3 = Sq1 * Vq2;

		float		part4a = -(q1.b * q2.b + q1.c * q2.c + q1.d * q2.d);
		float		part4b = (q1.c * q2.d - q1.d * q2.c);
		float		part4c = (q1.d * q2.b - q1.b * q2.d);
		float		part4d = (q1.b * q2.c - q1.c * q2.b);
		Quaternion	part4 = Quaternion(part4a, part4b, part4c, part4d);

		Quaternion result = part1 + part2 + part3 + part4;


		return result;
	}

	inline Quaternion operator*(float f, const Quaternion& q)
	{
		float a = q.a * f;
		float b = q.b * f;
		float c = q.c * f;
		float d = q.d * f;
		return Quaternion(a, b, c, d);
	}

	inline Quaternion operator*(const Quaternion& q, float f)
	{
		return f * q;
	}

	inline std::ostream& operator<<(std::ostream& os, const Quaternion& q)
	{
		float a = q.a;
		float b = q.b;
		float c = q.c;
		float d = q.d;

		os << a;

		if (b >= 0)
			os << " + " << b;
		else
			os << " - " << fabs(b);
		os << "i";

		if (c >= 0)
			os << " + " << c;
		else
			os << " - " << fabs(c);
		os << "j";

		if (d >= 0)
			os << " + " << d;
		else
			os << " - " << fabs(d);
		os << "k";

		return os;
	}
}