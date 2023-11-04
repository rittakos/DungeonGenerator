#include "delaunayBase.hpp"
#include <exception>
#include "edge.hpp"

namespace Geometry
{
    namespace Delaunay
    {

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