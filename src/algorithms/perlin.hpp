#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <vector>
#include <random>

typedef struct unitVector
{
    float x;
    float y;
} unitVector;


class Perlin
{
private:
    int size = 256;
    std::vector<std::vector<unitVector>> grid;
public:
    Perlin(int size);
    unitVector randomUnitVector();
    float value(float x, float y);
    float dotProd(float x0, float y0, float x1, float y1);
    float interpolate(float a0, float a1, float x);
};


#endif