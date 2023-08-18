#pragma once
#include <random>

class Random {
public:
	static float getRandomFloat() {
		static std::random_device rd;
		static std::mt19937 generator(rd());
		std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		return distribution(generator);
	}
};
