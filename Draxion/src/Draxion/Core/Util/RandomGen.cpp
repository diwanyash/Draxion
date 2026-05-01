#include "RandomGen.h"
namespace Draxion
{
	std::mt19937 RandomGen::rng(std::random_device{}());

	template<>
    int Draxion::RandomGen::Get<int>(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(rng);
	}

	template<>
	float Draxion::RandomGen::Get<float>(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(rng);
	}

}
