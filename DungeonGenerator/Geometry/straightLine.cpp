#include "straightLine.hpp"

void Geometry::StraightLine::print(std::ostream& os)
{
}

void Geometry::StraightLine::read(std::istream& is)
{
}

Geometry::StraightLine::StraightLine(Math::Vec3f p1, Math::Vec3f p2)
{
}

float Geometry::StraightLine::length()
{
    return Math::distance(p1, p2);
}

Math::Vec3f Geometry::StraightLine::normal(const Math::Vec3f& at)
{
    return Math::Vec3f();
}

Math::Vec3f Geometry::StraightLine::getPointAtX(float x)
{
    return Math::Vec3f();
}

Math::Vec3f Geometry::StraightLine::getPointAtY(float y)
{
    return Math::Vec3f();
}
