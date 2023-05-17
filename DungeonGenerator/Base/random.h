#pragma once

#include <stdlib.h>
#include <random>

class Random
{
public:

	class Seed
	{
	private:
		unsigned int seed;
	public:
		explicit Seed(unsigned int seed) : seed{ seed } {}

		unsigned int getUnsignedValue() const { return seed; }
	};

private:
	static Seed seed;
	static std::mt19937 rng;

public:

	static void SetSeed(Seed seed)
	{
		Random::seed = seed;
		rng = std::mt19937(seed.getUnsignedValue());
	}

	static Seed GetSeed() { return seed; }

	static long int GetInteger(long int min, long int max)
	{
		return std::uniform_int_distribution<int>(min, max)(Random::rng);
	}

	static float GetFloat(float min, float max)
	{
		return std::uniform_real_distribution<float>(min, max)(Random::rng);
	}

	static std::vector<float> GetFloatWithFixedSum(int count, float sum, float spread = 0.0f)
	{
		std::vector<float> result;

		for (int idx = 0; idx < count; ++idx)
			result.push_back(sum / (float)count);

		for (int idx = 0; idx < count; ++idx)
		{
			float diff = Random::GetFloat(-spread, spread);
			result[idx] += diff;

			for (int i = 0; i < count; ++i)
			{
				if (i == idx)
					continue;

				result[i] -= diff / (float)(count - 1);
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
