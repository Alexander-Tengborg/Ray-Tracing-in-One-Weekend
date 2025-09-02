#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <limits>

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