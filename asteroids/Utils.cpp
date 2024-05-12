#include "Utils.h"

#include <random>

std::random_device rd{};
std::mt19937 gen(rd());

float utils::randRangef(const float start, const float end)
{
    std::uniform_real_distribution<float> distribution(start, end);
    return distribution(gen);
}

int utils::randRangei(const int start, const int end)
{
    std::uniform_int_distribution<> distribution(start, end);
    return distribution(gen);
}
