#pragma once

#include <random>
#include <chrono>

inline int32_t RandomValue(int32_t min, int32_t max)
{
    std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int32_t> distribution(min, max);
    return distribution(generator);
}

inline float RandomValue(float min, float max)
{
    std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

