#pragma once
#include <iostream>

namespace Math
{



	class Vec3
	{
	private:
		int x;
		int y;
		int z;

	public:
		Vec3(int x = 0, int y = 0, int z = 0) : x{ x }, y{ y }, z{ z }
		{
		}

		Vec3(const Vec3& other);

		friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
		friend std::istream& operator>>(std::istream& is, const Vec3& v);
	};

	


	class NormalVector
	{
		Vec3 normal;
	};





} //namespace Math