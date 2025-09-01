#pragma once

#include "Vec3.h"

using Color = Vec3;

void writeColor(std::ostream& out, const Color& pixelColor)
{
    auto r = pixelColor.x;
    auto g = pixelColor.y;
    auto b = pixelColor.z;

    int ir = static_cast<int>(255.999 * r);
    int ig = static_cast<int>(255.999 * g);
    int ib = static_cast<int>(255.999 * b);

    out << ir << ' ' << ig << ' ' << ib << '\n';
}