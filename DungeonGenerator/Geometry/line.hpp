#pragma once
//#include "vector.hpp"
#include <iostream>
#include "vector.hpp"

namespace Geometry
{
	class Line
	{
	private:
		virtual void print(std::ostream& os) = 0;
		virtual void read(std::istream& is) = 0;

	public:

		virtual float length() = 0;
		virtual Math::Vec3f normal(const Math::Vec3f& at) = 0;
		virtual Math::Vec3f getPointAtX(float x) = 0;
		virtual Math::Vec3f getPointAtY(float y) = 0;



		friend std::ostream& operator<<(std::ostream& os, std::shared_ptr<Line> line);
		friend std::istream& operator>>(std::istream& is, std::shared_ptr<Line> line);
	};

	inline std::ostream& operator<<(std::ostream& os, std::shared_ptr<Line> line)
	{
		line->print(os);
		return os;
	}

	inline std::istream& operator>>(std::istream& is, std::shared_ptr<Line> line)
	{
		line->read(is);
		return is;
	}

}