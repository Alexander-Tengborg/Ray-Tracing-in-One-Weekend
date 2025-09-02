#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <limits>
#include <random>

constexpr double PI = 3.14159265358979323846;
constexpr double infinity = std::numeric_limits<double>::infinity();


inline double degrees(double radians)
{
    return radians / PI * 180.0;
}

inline double radians(double degrees)
{
    return degrees * PI / 180.0;
}

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;

    return distribution(generator);
}

inline double random_double(double min, double max)
{
    return min + (max-min)*random_double();
}