#pragma once

#include <stdlib.h>
#include <random>

class Random
{
public:

	class Seed
	{
		unsigned int seed;
	public:
		explicit Seed(const unsigned int seed) : seed{ seed } {}

		unsigned int getUnsignedValue() const { return seed; }
	};

private:
	static Seed seed;
	static std::mt19937 rng;

public:

	static void SetSeed(const Seed seed)
	{
		Random::seed = seed;
		rng = std::mt19937(seed.getUnsignedValue());
	}

	static Seed GetSeed() { return seed; }

	static long int GetInteger(long int min, long int max)
	{
		return std::uniform_int_distribution<int>(min, max)(rng);
	}

	static float GetFloat(float min, float max)
	{
		return std::uniform_real_distribution<float>(min, max)(rng);
	}

	static std::vector<float> GetFloatWithFixedSum(const int count, const float sum, const float spread = 0.0f)
	{
		std::vector<float> result;

		for (int idx = 0; idx < count; ++idx)
			result.push_back(sum / static_cast<float>(count));

		for (int idx = 0; idx < count; ++idx)
		{
			float diff = GetFloat(-spread, spread);
			result[idx] += diff;

			for (int i = 0; i < count; ++i)
			{
				if (i == idx)
					continue;

				result[i] -= diff / static_cast<float>(count - 1);
			}
		}

		return result;
	}

	static bool GetBool()
	{
		return GetInteger(0, 1) == 0;
	}



	Random() = delete;
	Random(const Random&) = delete;
	void operator= (const Random&) = delete;
};
