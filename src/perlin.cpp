#include "perlin.h"

Perlin::Perlin()
{
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);
    std::random_shuffle(p.begin(), p.end());
    p.insert(p.end(), p.begin(), p.end());
}

double Perlin::noise(double x, double y)
{
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);

    double u = fade(x);
    double v = fade(y);

    int aa, ab, ba, bb;
    aa = p[p[X] + Y];
    ab = p[p[X] + Y + 1];
    ba = p[p[X + 1] + Y];
    bb = p[p[X + 1] + Y + 1];

    double res = lerp(v, lerp(u, grad(aa, x, y), grad(ba, x - 1, y)),
                         lerp(u, grad(ab, x, y - 1), grad(bb, x - 1, y - 1)));
    return (res + 1.0) / 2.0;
}

double Perlin::fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double Perlin::grad(int hash, double x, double y)
{
    int h = hash & 7;
    double u = h < 4 ? x : y;
    double v = h < 4 ? y : x;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
