#pragma once

#include <random>
#include <chrono>
#include <vector>

using std::string;
using std::vector;
using std::default_random_engine;
using std::chrono::high_resolution_clock;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

namespace tsp_tests
{
	inline int32_t RandomValue(int32_t min, int32_t max)
	{
		default_random_engine generator(
			high_resolution_clock::now().time_since_epoch().count());
		uniform_int_distribution<int32_t> distribution(min, max);
		return distribution(generator);
	}

	inline float RandomValue(float min, float max)
	{
		default_random_engine generator(
			high_resolution_clock::now().time_since_epoch().count());
		uniform_real_distribution<float> distribution(min, max);
		return distribution(generator);
	}

	inline vector<string> RandomNames(size_t count, size_t name_size = 50u)
	{
		vector<string> names;
		for (auto i = 0; i < count; ++i)
		{
			string name;
			for (auto j = 0; j < name_size; ++j)
			{
				default_random_engine generator(
					high_resolution_clock::now().time_since_epoch().count());
				uniform_int_distribution<int32_t> distribution('a', 'z');
				name += distribution(generator);
			}
			names.emplace_back(name);
		}
		return names;
	}

	inline vector<int32_t> RandomCoordinates(size_t count, int32_t min, int32_t max)
	{
		vector<int32_t> coordinates;
		for (auto i = 0; i < count; ++i)
		{
			default_random_engine generator(
				high_resolution_clock::now().time_since_epoch().count());
			uniform_int_distribution<int32_t> distribution(min, max);
			coordinates.emplace_back(distribution(generator));
		}
		return coordinates;
	}

	inline vector<float> RandomCoordinates(size_t count, float min, float max)
	{
		vector<float> coordinates;
		for (auto i = 0; i < count; ++i)
		{
			default_random_engine generator(
				high_resolution_clock::now().time_since_epoch().count());
			uniform_real_distribution<float> distribution(min, max);
			coordinates.emplace_back(distribution(generator));
		}
		return coordinates;
	}
}
