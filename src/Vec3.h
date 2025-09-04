#pragma once

#include <iostream>

#include "MathUtils.h"

class Vec3
{
public:
    double x;
    double y;
    double z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3& operator+=(const Vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }

    Vec3& operator*=(double t)
    {
        x *= t;
        y *= t;
        z *= t;

        return *this;
    }

    Vec3& operator/=(double t)
    {
        return *this *= 1/t;
    }

    double length() const
    {
        return std::sqrt(lengthSquared());
    }

    double lengthSquared() const
    {
        return x * x + y * y + z * z;
    }

    bool near_zero() const
    {
        // Return true if the vector is close to zero in all dimensions.
        auto s = 1e-8;

        return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
    }

    static Vec3 random()
    {
        return Vec3(randomDouble(), randomDouble(), randomDouble());
    }

    static Vec3 random(double min, double max)
    {
        return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }
};

using Point3 = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator*(double t, const Vec3& v)
{
    return Vec3(t * v.x, t * v.y, t * v.z);
}

inline Vec3 operator*(const Vec3& v, double t)
{
    return t * v;
}

inline Vec3 operator/(const Vec3& v, double t)
{
    return (1/t) * v;
}

inline double dot(const Vec3& u, const Vec3& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.y*v.z - u.z*v.y,
                u.z*v.x - u.x*v.z,
                u.x*v.y - u.y*v.z);
}

inline Vec3 unitVector(const Vec3& v)
{
    return v / v.length();
}

inline Vec3 randomUnitVector()
{
    while(true)
    {
        auto p = Vec3::random(-1, 1);
        auto lensq = p.lengthSquared();

        // If a double is too small it can underflow to 0, which may lead to vectors
        // with components that have infinite values.
        // Double safely supports values greater than 1e-160
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline Vec3 randomOnHemisphere(const Vec3& normal)
{
    Vec3 on_unit_sphere = randomUnitVector();

    // If normal and the unit sphere are in the same hemisphere
    if(dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;

    // If not, flip the unit sphere
    return -on_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v - 2*dot(v, n)*n;
}