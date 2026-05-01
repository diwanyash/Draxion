#pragma once
#include "Core.h"
#include <random>

namespace Draxion
{
	class DRX_API RandomGen
	{
	public:
		RandomGen()
		{};
		template<typename T>
		static T Get(T min, T max);
	private:
		static std::mt19937 rng;
	};
}

