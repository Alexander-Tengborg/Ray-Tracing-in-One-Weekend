#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Interval.h"

class HitRecord
{
public:
    Point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    void setFaceNormal(const Ray& r, const Vec3& outward_normal)
    {
        // Assumes that outward_normal is a unit vector
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};