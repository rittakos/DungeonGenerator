
//#include <iostream>
//
#include "matrix.hpp"
#include "vector.hpp"
#include "graph.hpp"

#include "guard.h"
#include "equationSystem.hpp"
#include "quaternion.hpp"


void linerEQTest()
{
	std::array<float, 3> var1 = { 1.0f, 5.0f, -2.0f };
	std::array<float, 3> var2 = { 2.0f, 3.0f, 1.0f };
	std::array<float, 3> var3 = { 2.0f, 4.0f, -3.0f };
	Math::LinearEquation<3> le1(2, var1);
	Math::LinearEquation<3> le2(5, var2);
	Math::LinearEquation<3> le3(2, var3);

	Math::LinearEquationSystem<3> les;

	les.addLinearEquation(le1);
	les.addLinearEquation(le2);
	les.addLinearEquation(le3);


	les.solve();
	std::vector<float> solution = les.getSolution();
}

void quaternionTest()
{
	Math::Quaternion q0;
	Math::Quaternion q1(5);
	Math::Quaternion q2(5, 4, 3, 2);
	Math::Quaternion q3(1, 2, 3, 4);

	/*std::cout << q3.norm() << std::endl;
	std::cout << q3.conjugation().norm() << std::endl;*/

	//std::cout << q2 * q3; //-20 + 20i + 6j + 28k
	Math::Quaternion q(30.0_deg, Math::Vec3f{0.0f, 0.0f, 1.0f});
	Math::Quaternion x(0, 3, 6, 0);
	std::cout << q.conjugation() << std::endl;
	std::cout << q * x * q.conjugation();
}

void angleTest()
{
	Math::Vec2f P1(1.0f, 0.0f);
	Math::Vec2f P2(0.0f, 0.0f);
	Math::Vec2f P3(0.0f, 1.0f);

	std::cout << Math::getAngle(P1, P2, P3).getDeg();
}

int main(int argc, char* argv[])
{
	LeakDetectionGuard leakGuard;
	/*Math::Graph<A> graph;

	A a(2);

	graph.addNode(a);*/

	//quaternionTest();
	angleTest();
}
