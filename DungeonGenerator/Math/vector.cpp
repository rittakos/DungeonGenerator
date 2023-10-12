#include "vector.hpp"


namespace Math
{
	Angle getAngle(Vec2f P1, Vec2f P2, Vec2f P3)
	{
		Vec2f v1 = P1 - P2;
		Vec2f v2 = P3 - P2;

		float result = atan2(v2[1], v2[0]) - atan2(v1[1], v1[0]);

		if (result < 0)
			result += Constant::Pi * 2.0f;

		return Angle(result);

		/*Angle a = v1.angleWith(v2);

		if (v1[0] < v2[0])
			a = -a;

		return 180.0_deg - a;*/
	}
}
