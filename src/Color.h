#pragma once

#include "Vec3.h"
#include "Interval.h"

using Color = Vec3;

void writeColor(std::ostream& out, const Color& pixelColor)
{
    auto r = pixelColor.x;
    auto g = pixelColor.y;
    auto b = pixelColor.z;

    static const Interval intensity(0.000, 0.999);

    int ir = static_cast<int>(255.999 * intensity.clamp(r));
    int ig = static_cast<int>(255.999 * intensity.clamp(g));
    int ib = static_cast<int>(255.999 * intensity.clamp(b));

    out << ir << ' ' << ig << ' ' << ib << '\n';
}