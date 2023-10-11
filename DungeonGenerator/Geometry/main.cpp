#include <vector>
#include <set>
#include <queue>
#include "polygon.hpp"
#include "transformation.hpp"
#include "quaternion.hpp"
#include "delaunay.hpp"

using namespace Geometry;

void polygonTest()
{
    std::vector<Math::Vec2f> points;
    points.push_back(Math::Vec2f(0.0f, 0.0f));
    points.push_back(Math::Vec2f(1.0f, 2.0f));
    points.push_back(Math::Vec2f(2.0f, 0.0f));
    points.push_back(Math::Vec2f(1.0f, -1.0f));

    Line l(Math::Vec2f{ 0.0f, 0.0f }, Math::Vec2f{ 1.0f, 1.0f });
    Polygon p;
    p.addPoint(points[0]);
    p.addPoint(points[1]);
    p.addPoint(points[2]);
    p.addPoint(points[3]);

    //std::cout << (p.isConvex() ? "convex" : "concave") << std::endl;

    Polygon p2({ points });

    Polygon p3(points);

    //std::cout << p2.Area();
    std::vector<Math::Vec2f> intersections = getIntersectionPoints(l, p);
    /*for (auto p : intersections)
        std::cout << p << std::endl;*/

    std::vector<Polygon> dividedPolygons = dividePolygonByLine(l, p);

    for (Polygon poly : dividedPolygons)
        std::cout << poly;
}

void lineTest()
{
    Math::Vec2f P1(0.0f, 0.0f);
    Math::Vec2f P2(1.0f, 1.0f);
    Math::Vec2f P3(0.0f, 2.0f);
    Math::Vec2f P4(2.0f, 0.0f);
    
    Line l1(P1, P2);
    Line l2(P3, P4);

    std::cout << (getIntersectionPoint(l1, l2).value() == Math::Vec2f(1.0f, 1.0f) ? "OK" : "ERROR") << std::endl;


    Math::Vec2f A(-5.43f, 1.5f);
    Math::Vec2f B(1.63f, -2.28f);
    Math::Vec2f C(-6.49f, -3.94f);
    Math::Vec2f D(2.81f, 0.4f);

    Line l3(A, B);
    Line l4(C, D);

    std::cout << (getIntersectionPoint(l3, l4).value() == Math::Vec2f(-0.4949189596683f, -1.1422955145199f) ? "OK" : "ERROR") << std::endl;

    
    Math::Vec2f P5(0.0f, 0.0f);
    Math::Vec2f P6(1.0f, 1.0f);
    Math::Vec2f P7(0.0f, 1.0f);
    Math::Vec2f P8(1.0f, 2.0f);

    Line l5(P5, P6);
    Line l6(P7, P8);

    std::cout << (!getIntersectionPoint(l5, l6).has_value() ? "OK" : "ERROR") << std::endl;
}

void rotateTest()
{
    Math::Vec2f v(0.0f, 1.0f);

    std::cout << Geometry::rotate(v, -90.0_deg);
}

void dividePolygonTest()
{

}


void delanuayTest()
{
    std::vector<Math::Vec2f> vertices;

    /*Math::Vec2f o(0.0f, 0.0f);
    Math::Vec2f v(0.0f, 1.0f);
    Math::Vec2f u(1.0f, 0.0f);*/

    /*std::cout << v.angleWith(u).getDeg() << std::endl;
    std::cout << u.angleWith(v).getDeg() << std::endl;

    std::cout << Math::getAngle(v, o, u).getDeg() << std::endl;
    std::cout << Math::getAngle(u, o, v).getDeg() << std::endl;*/

    //vertices.push_back(Math::Vec2f(0.0f, 0.0f));
    vertices.push_back(Math::Vec2f(1.0f, 0.0f));
    vertices.push_back(Math::Vec2f(0.0f, 1.0f));
    vertices.push_back(Math::Vec2f(2.0f, 1.0f));
    vertices.push_back(Math::Vec2f(1.5f, 2.0f));
    vertices.push_back(Math::Vec2f(1.0f, 1.5f));

    Geometry::Delaunay::DelaunayTriangulator triangulator(vertices);

    Geometry::Delaunay::DelaunayTriangulation triangulation = triangulator.Triangulate();
    
    for(const Delaunay::Triangle triangle : triangulation.Triangles)
        std::cout << triangle.P0.index << "\t" << triangle.P1.index << "\t" << triangle.P2.index << std::endl;

    auto nodes = triangulation.Neighbours.getNodes();
    auto edges = triangulation.Neighbours.getEdges();
    //for(auto& [key, value] : triangulation.Neighbours.getNodes())
}

int main()
{
    //polygonTest();
    //lineTest();
    //rotateTest();

    delanuayTest();
}