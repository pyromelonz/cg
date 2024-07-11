#pragma once

#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

class Perlin
{
public:
    Perlin();
    double noise(double x, double y);

private:
    std::vector<int> p;
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y);
};
