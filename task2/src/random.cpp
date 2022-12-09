#include "random.hpp"

#include <stdlib.h>
#include <cassert>

float Random::RandomNormalized()
{
    return (rand() % (int) (1e9 + 1)) / 1e9;
}

int Random::RandomRangeInt(int from, int to)
{
    assert(from <= to);
    return from + (rand() % (to - from + 1));
}

float Random::RandomRangeFloat(float from, float to) {
    float alpha = RandomNormalized();
    return (1 - alpha) * from + alpha * to;
}