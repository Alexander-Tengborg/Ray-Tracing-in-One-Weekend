#pragma once

#include "MathUtils.h"

class Interval
{
public:
    double min;
    double max;

    Interval() : min(-infinity), max(infinity) {}

    Interval(double min, double max) : min(min), max(max) {}

    double size() const
    {
        return max - min;
    }

    bool contains(double x) const
    {
        return x >= min && x <= max;
    }

    bool surrounds(double x) const
    {
        return x > min && x < max;
    }

    static const Interval empty, universe;
};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);