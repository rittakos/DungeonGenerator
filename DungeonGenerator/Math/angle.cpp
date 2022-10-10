#include "angle.hpp"
	 
namespace Math
{
	/*inline bool	Angle::operator==(const Angle& other) const
	{
		return isEqual(this->angleInRad, other.angleInRad);
	}

	inline bool	Angle::operator<(const Angle& other) const
	{
		return this->angleInRad < other.angleInRad;
	}

	bool Angle::operator>(const Angle& other) const
	{
		return this->angleInRad > other.angleInRad;
	}

	Angle Angle::operator-() const
	{
		return Angle(-1.0f * angleInRad);
	}*/

	float Angle::getDeg() const { return angleInRad / Math::Constant::Pi * 180.0f; }
	float Angle::getRad() const { return angleInRad; }


	extern Angle operator+(const Angle& angle1, const Angle& angle2);
	extern Angle operator-(const Angle& angle1, const Angle& angle2);
	extern Angle operator*(const Angle& angle1, const Angle& angle2);
	extern Angle operator*(float skalar, const Angle& angle);
	extern Angle operator*(const Angle& angle, float skalar);
	extern Angle operator/(const Angle& angle1, const Angle& angle2);
	extern Angle operator/(const Angle& angle, float skalar);
	extern float sin(const Angle& angle);
	extern float cos(const Angle& angle);
	extern float tan(const Angle& angle);
	extern Angle asin(float sin);
	extern Angle acos(float cos);
	extern Angle atan(float tan);
	extern Angle AngleFromDeg(float deg);
	extern Angle AngleFromRad(float rad);
}