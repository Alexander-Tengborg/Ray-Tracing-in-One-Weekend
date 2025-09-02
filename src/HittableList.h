#pragma once

#include "Hittable.h"

#include <vector>

class HittableList : public Hittable
{
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() = default;
    HittableList(std::shared_ptr<Hittable> object)
    {
        add(object);
    }

    void clear()
    {
        objects.clear();
    }

    void add(std::shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    }

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override
    {
        HitRecord temp_rec;
        bool any_hit = false;
        auto closest_t = ray_t.max;

        for(const auto& object : objects)
        {
            if(object->hit(r, Interval(ray_t.min, closest_t), temp_rec))
            {
                any_hit = true;
                closest_t = temp_rec.t;
                rec = temp_rec;
            }
        }

        return any_hit;
    }

};