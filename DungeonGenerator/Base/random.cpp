#include "random.h"
#include <time.h>
#include <cassert>
#include <random>

Random::Seed  Random::seed = Random::Seed(std::random_device()());
std::mt19937  Random::rng = std::mt19937(seed.getUnsignedValue ());

//Random::Random::Random() : seed(Seed(std::random_device()()))
//{
//	//srand(seed.getUnsignedValue());
//	rng = std::mt19937(seed.getUnsignedValue());
//}
//
//Random::Random::Random(Seed seed) : seed{ seed }
//{
//	//srand(seed.getUnsignedValue());
//	rng = std::mt19937(seed.getUnsignedValue());
//}

//float Random::Random::getFloat()
//{
//	return 0.0f;
//}
//
//long int Random::Random::getInt()
//{
//	return rand();
//}
//
//long int Random::Random::getInt(long int min, long int max)
//{
//	assert("Invalid min and max values", min <= max);
//	long int intervalSize = max - min + 1;
//	return rand() % intervalSize + min;
//}

//long int Random::GetRandomInteger(long int min, long int max)
//{
//	return 0;
//}
