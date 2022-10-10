#include "polygon.hpp"
#include "edge.hpp"

namespace Geometry
{
    void Polygon::calculateConvexity()
    {
        if (n < 3)
        {
            convex = true;
            return;
        }

        convex = false;

        if (Math::getAngle(points[n - 1], points[0], points[1]) > 180.0_deg)
            return;

        for (int idx = 1; idx < n - 1; ++idx)
            if (Math::getAngle(points[idx - 1], points[idx], points[idx + 1]) > 180.0_deg)
                return;


        if (Math::getAngle(points[n - 2], points[n - 1], points[0]) > 180.0_deg)
            return;

        convex = true;
    }

    Polygon::Polygon(std::vector<Math::Vec2f> points)
    {
        this->points = points;
        this->n = points.size();
        calculateConvexity();
    }

    Polygon::Polygon(std::initializer_list<Math::Vec2f> points)
    {
        for (Math::Vec2f v : points)
            this->points.push_back(v);
        this->n = this->points.size();
        calculateConvexity();
    }

    float Polygon::Area() const //shoelace formula
    {
        double area = 0.0f;

        int size = points.size();

        int j = size - 1;
        for (int i = 0; i < size; i++)
        {
            area += (points[j][0] + points[i][0]) * (points[j][1] - points[i][1]);
            j = i; 
        }

        return abs(area / 2.0);
    }

    void	Polygon::addPoint(Math::Vec2f p)
    {
        points.push_back(p);
        ++n;
        calculateConvexity();
    }


    std::vector<Math::Vec2f> getIntersectionPoints(const Line& line, const Polygon& polygon)
    {
        std::vector<Math::Vec2f> intersectionPoints;

        for (int idx = 0; idx < polygon.n; ++idx)
        {
            int otherIdx = 0;
            if (idx != polygon.n - 1)
                otherIdx = idx + 1;

            Math::Vec2f otherPoint = polygon.points[otherIdx];
            Edge edge(polygon.points[otherIdx], otherPoint);

            std::optional<Math::Vec2f> intersection = edge.getIntersectionPoint(line);

            if (intersection.has_value())
                intersectionPoints.push_back(intersection.value());
        }

        return intersectionPoints;
    }

    std::vector<Polygon> dividePolygonByLine(const Line& line, const Polygon& polygon)
    {
        std::vector<Polygon> resultPolygons;
        std::vector<Math::Vec2f> intersectionPoints = getIntersectionPoints(line, polygon);



        return resultPolygons;
    }

    Math::Vec2f cutPartFromPolygon(Math::Vec2f P, float targerArea, Polygon polygon)
    {
        int n = polygon.points.size();

        Edge currentEdge;
        int nextPointIdx = -1;

        for (int idx = 0; idx < n; ++idx)
        {
            nextPointIdx = idx + 1;;
            if (idx == n - 1)
                nextPointIdx = 0;

            currentEdge = Edge(polygon.points[idx], polygon.points[nextPointIdx]);
            if (currentEdge.containsPoint(P))
                break;
            else
                nextPointIdx = -1;
        }

        if (nextPointIdx == -1)
            throw std::exception();

        Math::Vec2f nextPoint = polygon.points[nextPointIdx];

        Polygon cutDown;

        int lastPointIdx = -1;

        cutDown.addPoint(P);
        cutDown.addPoint(nextPoint);

        for (int idx = 1; idx < n; ++idx)
        {
            Math::Vec2f newPoint = polygon.points[nextPointIdx + idx];
            cutDown.addPoint(newPoint);
            if (cutDown.Area() < targerArea)
                continue;

            lastPointIdx = nextPointIdx + idx;
            break;
        }

        float A = cutDown.Area() - targerArea;

        float t = 1.0f;
        Math::Vec2f v;

        return polygon.points[nextPointIdx] + (v * t);
    }
}
