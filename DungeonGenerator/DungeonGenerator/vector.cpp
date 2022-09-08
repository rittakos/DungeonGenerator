#include "vector.hpp"

namespace Math
{



	std::ostream& operator<<(std::ostream& os, const Vec3& v)
	{
		os << v.x << ", " << v.y << ", " << v.z;
		return os;
	}

	std::istream& operator>>(std::istream& is, const Vec3& v)
	{
		return is;
	}




} //namespace Math