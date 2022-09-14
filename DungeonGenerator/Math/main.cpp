#include <iostream>

#include "matrix.hpp"
#include "vector.hpp"


int main(int argc, char* argv[])
{
	//Math::Mat<3, 3, int> m{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1 } };
	Math::Mat<2, 3, int> m(	 1, 1, 1,
							 2, 2, 2);
	Math::Mat<3, 3, int> m2(1, 1, 0, 
							2, 1, 0, 
							3, 1, 0);

	Math::Mat<4, 4, int> m3(	2, 1, 1, 1,
								4, 3, 6, 4,
								6, 7, 21, 16,
								2, 3, 15, 23);
	/*Math::Vec<2, int> v(1, 2);
	Math::Mat<2, 2, int> m2(v, v);*/
	//Math::Vec<3, int> v(1.0f, 0.0f, 5.0f);
	Math::Vec<3, int> v(1, 0, 5);
	Math::Vec3f v0;
	Math::Mat res = createMatrixFromVector(v) * m2;
	std::cout << m * m2;//(createMatrixFromVector(v) * m2).toVector();
}