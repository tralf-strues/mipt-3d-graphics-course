#pragma once

class Random {
public:
    static float RandomNormalized();
    static int   RandomRangeInt(int from, int to);
    static float RandomRangeFloat(float from, float to);
};