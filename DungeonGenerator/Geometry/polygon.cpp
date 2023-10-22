#include "polygon.hpp"

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

    void Polygon::addEdges()
    {
        edges.clear();

        if (n < 2)
            return;

        for (int idx = 0; idx < n - 1; ++idx)
            edges.push_back(Edge(points[idx], points[idx + 1]));

        edges.push_back(Edge(points[n - 1], points[0]));
    }

    Polygon::Polygon(std::vector<Math::Vec2f> points)
    {
        this->points = points;
        this->n = points.size();
        addEdges();
        calculateConvexity();
    }

    Polygon::Polygon(std::initializer_list<Math::Vec2f> points)
    {
        for (Math::Vec2f v : points)
            this->points.push_back(v);
        this->n = this->points.size();
        addEdges();
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
        if (containsPoint(p))
            return;
        points.push_back(p);
        ++n;
        addEdges();
        calculateConvexity();
    }

    bool Polygon::addHole(const Polygon& hole)
    {
        for (const Math::Vec2f& p : hole.getPoints())
            if (!isPointInside(p))
                return false;

        holes.push_back(hole);

        return true;
    }

    bool Polygon::isPointInside(const Math::Vec2f& point) const
    {
        Math::Vec2f v(1.0f, 0.0f);
        Line line(point, point + v);

        int intersectionCount = 0;

        for (const Edge& edge : edges)
        {
            std::optional<Math::Vec2f> i = getIntersectionPoint(edge, line);
            if (!i.has_value())
                continue;

            float x = i.value()[0];
            if (x > point[0])
                ++intersectionCount;
        }

        if (intersectionCount % 2 == 1)
            return true;

        return false;
    }

    bool	Polygon::exists() const
    {
        if (n < 3)
            return false;
        Math::Angle innerAngle = 0.0_deg;

        for (const Edge& e1 : edges)
        {
            for (const Edge& e2 : edges)
            {
                if (e1 == e2)
                    continue;

                std::optional<Math::Vec2f> i = getIntersectionPoint(e1, e2);
                if (!i.has_value())
                    continue;
                
                Math::Vec2f I = i.value();
                Math::Vec2f P1e1 = e1.getPoints()[0];
                Math::Vec2f P2e1 = e1.getPoints()[1];
                Math::Vec2f P1e2 = e2.getPoints()[0];
                Math::Vec2f P2e2 = e2.getPoints()[1];

                float epsilon = 0.001f;

                if (Math::equals(I, P1e1, epsilon) || Math::equals(I, P2e1, epsilon))
                    continue;
                if (Math::equals(I, P1e2, epsilon) || Math::equals(I, P2e2, epsilon))
                    continue;

                return false;
            }
        }

        innerAngle += Math::getAngle(points[n - 1], points[0], points[1]);
        

        for (int idx = 1; idx < n - 1; ++idx)
            innerAngle += Math::getAngle(points[idx - 1], points[idx], points[idx + 1]);

        innerAngle += Math::getAngle(points[n - 2], points[n - 1], points[0]);

        return innerAngle == calcInnerAngle();
    }

    bool	Polygon::containsPoint(const Math::Vec2f& P) const
    {
        if (points.empty())
            return false;

        for (Math::Vec2f p : points)
            if (p == P)
                return true;

        return false;
    }


    std::vector<Math::Vec2f> getIntersectionPoints(const Line& line, const Polygon& polygon)
    {
        std::vector<Math::Vec2f> intersectionPoints;

        for (Edge edge : polygon.edges)
        {
            std::optional<Math::Vec2f> intersection = getIntersectionPoint(edge, line);

            if (intersection.has_value() &&
                std::find(intersectionPoints.begin(), intersectionPoints.end(), intersection.value()) == intersectionPoints.end())
            {
                //std::cout << intersection.value() << std::endl;
                intersectionPoints.push_back(intersection.value());
                //std::cout << intersectionPoints.size() << std::endl;
            }
        }

        return intersectionPoints;
    }

    std::vector<Polygon> dividePolygonByLine(const Line& line, const Polygon& polygon) //convex
    {

        //epitek egy grafot es abban korkereses
        if (!polygon.isConvex())
            throw new std::exception();

        std::vector<Polygon> resultPolygons;
        std::vector<Math::Vec2f> intersectionPoints = getIntersectionPoints(line, polygon);

        if (intersectionPoints.size() == 0 || intersectionPoints.size() == 1)
            return { polygon };

        resultPolygons.push_back(Polygon());
        resultPolygons.push_back(Polygon());

        for (Edge e : polygon.edges)
        {
            if (e.containsPoint(intersectionPoints[0]))
            {
                resultPolygons[0].addPoint(e.getPoints()[0]);
                resultPolygons[0].addPoint(intersectionPoints[0]);
                resultPolygons[1].addPoint(intersectionPoints[0]);
                resultPolygons[1].addPoint(e.getPoints()[1]);
                continue;
            }

            if (e.containsPoint(intersectionPoints[1]))
            {
                resultPolygons[0].addPoint(intersectionPoints[1]);
                resultPolygons[0].addPoint(e.getPoints()[1]);
                resultPolygons[1].addPoint(e.getPoints()[0]);
                resultPolygons[1].addPoint(intersectionPoints[1]);
                continue;
            }

            resultPolygons[0].addPoint(e.getPoints()[0]);
            resultPolygons[0].addPoint(e.getPoints()[1]);
        }

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

        //float A = cutDown.Area() - targerArea;

        float t = 1.0f;
        Math::Vec2f v;

        if (lastPointIdx == -1)
            return Math::Vec2f();

        return polygon.points[lastPointIdx] + (v * t);
        // lehet ez lenne a jo: return polygon.points[nextPointIdx] + (v * t);
    }

    /*std::optional<Polygon> CreatePolygon(std::vector<Math::Vec2f> points)
    {
        std::optional<Polygon> result;



        return result;
    }*/

    std::ostream& operator<<(std::ostream& os, const Polygon& polygon)
    {
        os << "polygon:" << std::endl;
        for (Math::Vec2f p : polygon.points)
            os << p << std::endl;
        os << std::endl;

        return os;
    }


    bool operator==(const Polygon& polygon1, const Polygon& polygon2)
    {
        if (polygon1.n != polygon2.n)
            return false;

        bool foundEqual = false;;

        for (int idx = 0; idx < polygon2.n; ++idx)
        {
            if (polygon2.getPoints()[idx] == polygon1.getPoints()[0])
            {
                foundEqual = true;
                for (int i = 1; i < polygon2.n; ++i)
                {
                    if (polygon1.getPoints()[i] != polygon2.getPoints()[(idx + i) % polygon2.n])
                    {
                        foundEqual = false;
                        break;
                    }
                }
            }
        }
        return foundEqual;
    }


    bool operator!=(const Polygon& polygon1, const Polygon& polygon2)
    {
        return !(polygon1 == polygon2);
    }
}
