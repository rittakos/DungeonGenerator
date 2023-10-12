#include "delaunay.hpp"
#include <matrix.hpp>

namespace Geometry
{
    namespace Delaunay
    {

        std::vector<Triangle> DelaunayTriangulator::triangulate()
        {
            std::vector<Triangle> triangles;

            triangles.push_back(createSuperTriangle());

            for (int vertexIdx = 0; vertexIdx < vertices.size(); ++vertexIdx)
            {
                std::vector<Triangle> badTriangles;
                for (const Triangle& triangle : triangles)
                {
                    if (isPointInTrianglesCircle(triangle, vertexIdx))
                    {
                        badTriangles.push_back(triangle);
                    }
                }

                std::vector<Edge> polygon;
                for (const Triangle& badTriangle : badTriangles)
                {
                    for (const Edge& edge : badTriangle.getEdges())
                    {
                        bool edgeSharedByOtherBadTriangle = false;
                        for (const Triangle& triangle : badTriangles)
                        {
                            if (badTriangle == triangle)
                                continue;
                            if (triangle.hasEdge(edge))
                            {
                                edgeSharedByOtherBadTriangle = true;
                                break;
                            }
                        }
                        if (!edgeSharedByOtherBadTriangle)
                            polygon.push_back(edge);
                    }
                }

                for (const Triangle& triangle : badTriangles)
                {
                    std::vector<Triangle>::iterator iter = std::find(triangles.begin(), triangles.end(), triangle);
                    triangles.erase(iter);
                }

                for (const Edge& edge : polygon)
                {
                    Triangle newTriangle(edge.P0, edge.P1, vertexIdx);
                    triangles.push_back(newTriangle);
                }
            }


            auto hasSuperTrianglePoint = [&](const Triangle& triangle) {
                return triangle.P0.superTriangle || triangle.P1.superTriangle || triangle.P2.superTriangle;
                };

            std::vector<Triangle> triangulation;

            for (const Triangle& triangle : triangles)
                if (!hasSuperTrianglePoint(triangle))
                    triangulation.push_back(triangle);

            //std::remove_if(triangles.begin(), triangles.end(), hasSuperTrianglePoint);

            return triangulation;

        }

        bool DelaunayTriangulator::isPointInTrianglesCircle(Triangle triangle, const PointIndex& P) const
        {
            Math::Vec2f A = getValueOfPoint (triangle.P0);
            Math::Vec2f B = getValueOfPoint (triangle.P1);
            Math::Vec2f C = getValueOfPoint (triangle.P2);
            Math::Vec2f D = getValueOfPoint (P);

            if (isClockWise(triangle)) // if clockwise rotate dir
                std::swap(B, C);

            Math::Mat<3, 3, float> matrix(  A[0] - D[0], A[1] - D[1], (A[0] - D[0]) * (A[0] - D[0]) + (A[1] - D[1]) * (A[1] - D[1]),
                                            B[0] - D[0], B[1] - D[1], (B[0] - D[0]) * (B[0] - D[0]) + (B[1] - D[1]) * (B[1] - D[1]),
                                            C[0] - D[0], C[1] - D[1], (C[0] - D[0]) * (C[0] - D[0]) + (C[1] - D[1]) * (C[1] - D[1]));

            float determinant = Math::det(matrix);

            return determinant > 0;
        }

        Triangle DelaunayTriangulator::createSuperTriangle()
        {
            Triangle superTriangle(PointIndex(0, true), PointIndex(1, true), PointIndex(2, true));

            float minX = vertices[0][0];
            float maxX = vertices[0][0];
            float minY = vertices[0][1];
            float maxY = vertices[0][1];

            for (Math::Vec2f v : vertices)
            {
                float currentX = v[0];
                float currentY = v[1];

                if (currentX > maxX)
                    maxX = currentX;

                if (currentX < minX)
                    minX = currentX;

                if (currentY < minY)
                    minY = currentY;

                if (currentY > maxY)
                    maxY = currentY;
            }

            float dx = maxX - minX;
            float dy = maxY - minY;

            float x = fmaxf(dx, dy) * 1.5f;
            float Px = (minX + maxX) / 2.0f;
            float Py = minY - 0.2f * x;

            superTriangleVertices[0] = Math::Vec2f{ Px - 1.5f * x   , Py            };
            superTriangleVertices[1] = Math::Vec2f{ Px              , Py + 1.5f * x };
            superTriangleVertices[2] = Math::Vec2f{ Px + 1.5f * x   , Py            };

            return superTriangle;
        }

        Math::Vec2f DelaunayTriangulator::getValueOfPoint(const PointIndex& pointIdx) const
        {
            if (pointIdx.superTriangle)
            {
                return superTriangleVertices[pointIdx.index];
            }

            return vertices[pointIdx.index];
        }

        void DelaunayTriangulator::transformAllTriangles(std::vector<Triangle>& triangles, TriangleDirection direction) const
        {
            if (direction == NotMatters)
                return;

            for (Triangle& triangle : triangles)
            {
                if (isClockWise(triangle))
                {
                    if (direction == CounterClockWise)
                        triangle.rotate();
                }
                else
                {
                    if (direction == ClockWise)
                        triangle.rotate();

                }
            }
        }

        bool DelaunayTriangulator::isClockWise(const Triangle& triangle) const
        {
            Math::Vec2f A = getValueOfPoint(triangle.P0);
            Math::Vec2f B = getValueOfPoint(triangle.P1);
            Math::Vec2f C = getValueOfPoint(triangle.P2);

            if (Math::getAngle(A, B, C) < 180.0_deg) // if clockwise rotate dir
                return true;
            return false;
        }

        std::optional<Edge> DelaunayTriangulator::hasCommonEdge(const Triangle& triangle1, const Triangle& triangle2) const
        {
            if (triangle1 == triangle2)
                return {}; // egyezo haromszogeknel nem tekintjuk kozos elnek

            for (const Edge& edge : triangle1.getEdges())
                if (triangle2.hasEdge(edge))
                    return edge;
            return {};
        }

        DelaunayTriangulator::DelaunayTriangulator(std::vector<Math::Vec2f> vertices) : vertices{ vertices }
        {
            if (vertices.size() < 3)
                std::cout << "Not enough points!" << std::endl;
            //Log::warn("Not enough points!");
        }

        Math::Graph<Triangle> DelaunayTriangulator::getNeighbourhoodGraph(const std::vector<Triangle>& triangulation) const
        {
            Math::Graph<Triangle> graph;

            for (const Triangle& triangle : triangulation)
                graph.addNode(triangle);

            for (int idx = 0; idx < triangulation.size() - 1; ++idx)
            {
                for (int next = idx + 1; next < triangulation.size(); ++next)
                {
                    std::optional<Edge> edge = hasCommonEdge(triangulation[idx], triangulation[next]);
                    if (edge.has_value())
                    {
                        graph.addEdge(triangulation[idx], triangulation[next]);
                        graph.addEdge(triangulation[next], triangulation[idx]);
                    }
                }
            }


            return graph;
        }

        DelaunayTriangulation DelaunayTriangulator::Triangulate(TriangleDirection direction /*= CounterClockWise*/) // gives the indexes of the points in the original vector
        {
            DelaunayTriangulation result;

            std::vector<Triangle> triangulation = triangulate();
            transformAllTriangles(triangulation, direction);

            result.Vertices = vertices;
            result.Triangles = triangulation;
            result.Neighbours = getNeighbourhoodGraph(triangulation);

            return result;
        }


        Triangle::Triangle(const PointIndex& p0, const PointIndex& p1, const PointIndex& p2)
            : P0(p0), P1(p1), P2(p2)
        {
            if (P0 == P1 || P0 == P2 || P1 == P2)
                throw std::exception("Invalid Triangle!");
        }

        bool Triangle::hasPoint(const PointIndex& P) const
        {
            if (P0 == P || P1 == P || P2 == P)
                return true;
            return false;
        }

        bool Triangle::hasEdge(const Edge& edge) const
        {
            if (hasPoint(edge.P0) && hasPoint(edge.P1))
                return true;
            return false;
        }

        void Triangle::rotate()
        {
            std::swap(P1, P2);
        }

        bool Triangle::operator==(const Triangle& other) const
        {
            if (other.hasPoint(P0) && other.hasPoint(P1) && other.hasPoint(P2))
                return true;
            return false;
        }

        std::array<Edge, 3> Triangle::getEdges() const
        {
            std::array<Edge, 3> edges;

            edges[0] = Edge(P0, P1);
            edges[1] = Edge(P1, P2);
            edges[2] = Edge(P2, P0);

            return edges;
        }

        std::array<PointIndex, 3> Triangle::getPoints() const
        {
            return { P0, P1, P2 };
        }

        Edge& Edge::operator=(const Edge& other)
        {
            this->P0 = other.P0;
            this->P1 = other.P1;

            return *this;
        }

        PointIndex& PointIndex::operator=(const PointIndex& other)
        {
            this->index = other.index;
            this->superTriangle = other.superTriangle;

            return *this;
        }

        bool PointIndex::operator==(const PointIndex& other) const
        {
            return index == other.index && superTriangle == other.superTriangle;
        }

}
}
