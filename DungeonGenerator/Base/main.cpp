
#include "log.h"
#include "random.h"
//import log;

int main(int argc, char* argv[])
{
	/*Log::Logger logger;
	logger.info("dsfdsf");*/
	Log::info("info");
	Log::error("error");

	Random::SetSeed(Random::Seed(100));
	std::cout << Random::GetInteger(0, 100);
}