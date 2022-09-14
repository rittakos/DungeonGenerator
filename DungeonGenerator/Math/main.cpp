#include <iostream>

#include "matrix.hpp"


int main(int argc, char* argv[])
{
	//Math::Matrix<3, 3, int> m{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1 } };
	Math::Mat<2, 2, int> m(1, 2, 3, 4);
	/*Math::Vec<2, int> v(1, 2);
	Math::Mat<2, 2, int> m2(v, v);*/
	std::cout << m;
}