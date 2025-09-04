#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
public:
    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat) : center_(center), radius_(std::fmax(0, radius)), mat_(mat) { }

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override
    {
        auto oc = center_ - r.origin();

        auto a = r.direction().lengthSquared();
        auto h = dot(r.direction(), oc);
        auto c = oc.lengthSquared() - radius_*radius_;

        auto discriminant = h*h - a*c;

        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Pick a root that lies within an acceptable range,
        // if one exists.
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);

        auto outward_normal = (rec.p - center_) / radius_;
        rec.setFaceNormal(r, outward_normal);

        rec.mat = mat_;

        return true;
    }

private:
    Point3 center_;
    double radius_;
    std::shared_ptr<Material> mat_;
};