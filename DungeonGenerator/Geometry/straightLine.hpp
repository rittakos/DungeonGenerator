#pragma once

#include "line.hpp"
#include "vector.hpp"

namespace Geometry
{
	class StraightLine final : public Line
	{
	private:
		Math::Vec3f p1;
		Math::Vec3f p2;

	private:
		virtual void print(std::ostream& os) override;
		virtual void read(std::istream& is) override;

	public:
		StraightLine(Math::Vec3f p1, Math::Vec3f p2);

		virtual float length() override;
		virtual Math::Vec3f normal(const Math::Vec3f& at) override;
		virtual Math::Vec3f getPointAtX(float x) override;
		virtual Math::Vec3f getPointAtY(float y) override;
	};
}