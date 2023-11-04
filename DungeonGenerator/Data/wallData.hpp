#pragma once

namespace Data
{
	class WallData
	{
	private:
		Math::Vec3f P1;
		Math::Vec3f P2;
		// TODO refaktor, hogy itt Edge legyen es ne 3D koordinatat kapjon, azt csak itt szamolja

		std::optional<float> width;
		float height;

	public:
		WallData(Math::Vec3f P1, Math::Vec3f P2) : P1(P1), P2(P2)
		{
			height = 100.0f;
		}

		Geometry::Edge getWallBase() const
		{
			Geometry::Edge wallBase(Math::Vec2f(P1[0], P1[1]), Math::Vec2f(P2[0], P2[1]));
			return wallBase;
		}

		std::vector<Math::Vec3i> getTrianglesClockWise() const
		{
			std::vector<Math::Vec3i> triangles;

			triangles.push_back(Math::Vec3i{ 0, 1, 2 });
			triangles.push_back(Math::Vec3i{ 0, 2, 3 });

			return triangles;
		}

		std::vector<Math::Vec3i> getTrianglesCounterClockwise() const
		{
			std::vector<Math::Vec3i> triangles;

			triangles.push_back(Math::Vec3i{ 2, 1, 0 });
			triangles.push_back(Math::Vec3i{ 3, 2, 0 });

			return triangles;
		}

		std::vector<Math::Vec3f> getPoints() const
		{
			std::vector<Math::Vec3f> points;

			/*points.push_back(Math::Vec3f{   0.0f, 0.0f, 0.0f });
			points.push_back(Math::Vec3f{   0.0f, 100.0f, 0.0f });
			points.push_back(Math::Vec3f{ 100.0f, 100.0f, 0.0f });
			points.push_back(Math::Vec3f{ 100.0f, 0.0f, 0.0f });*/
			//Math::Vec3f v = (P1 - P2).getNormalised();
			Math::Vec3f up(0.0f, 0.0f, 1.0f);
			
			points.push_back(P1);
			points.push_back(P2);
			points.push_back(P2 + height * up);
			points.push_back(P1 + height * up);

			return points;
		}
	};
}