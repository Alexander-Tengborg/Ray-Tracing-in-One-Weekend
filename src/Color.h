#pragma once

#include "Vec3.h"
#include "Interval.h"

using Color = Vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component <= 0)
        return 0;

    return std::sqrt(linear_component);
}

void writeColor(std::ostream& out, const Color& pixelColor)
{
    auto r = pixelColor.x;
    auto g = pixelColor.y;
    auto b = pixelColor.z;

    // Transform from linear to gamma space (gamma 2)
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Clamp values from [0, 1] to [0, 255]
    static const Interval intensity(0.000, 0.999);

    int ir = static_cast<int>(255.999 * intensity.clamp(r));
    int ig = static_cast<int>(255.999 * intensity.clamp(g));
    int ib = static_cast<int>(255.999 * intensity.clamp(b));

    out << ir << ' ' << ig << ' ' << ib << '\n';
}