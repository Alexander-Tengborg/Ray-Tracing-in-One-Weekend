#pragma once

#include "Hittable.h"
#include "Color.h"

class Camera
{
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 100;

    void render(const Hittable& world)
    {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height_ << "\n255\n";

        for (int j = 0; j < image_height_; j++)
        {
            std::clog << "\rProgess: " << static_cast<int>(100.0 * j/image_height_) << "%" << std::flush;
            for (int i = 0; i < image_width; i++)
            {
                Color pixel_color(0.0, 0.0, 0.0);
                for (int sample = 0; sample < samples_per_pixel; sample++)
                {
                    auto r = getRay(i, j);
                    pixel_color += rayColor(r, world);
                }

                writeColor(std::cout, pixel_samples_scale_ * pixel_color);
            }
        }

        std::clog << "\rDone.               \n";
    }

private:
    int image_height_;
    double pixel_samples_scale_;
    Point3 center_;
    Point3 pixel00_loc_;
    Vec3 pixel_delta_u_;
    Vec3 pixel_delta_v_;

    void initialize()
    {
        image_height_ = static_cast<int>(image_width / aspect_ratio);
        image_height_ = (image_height_ < 1) ? 1 : image_height_;

        pixel_samples_scale_ = 1.0 / samples_per_pixel;

        auto center = Point3(0, 0, 0);

        // Viewport dimensions
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * static_cast<double>(image_width) / image_height_;

        // Horizontal and Vertical viewport edges
        auto viewport_u = Vec3(viewport_width, 0, 0);
        auto viewport_v = Vec3(0, -viewport_height, 0);

        // Pixel to pixel deltas
        pixel_delta_u_ = viewport_u / image_width;
        pixel_delta_v_ = viewport_v / image_height_;

        // Upper left viewport and pixel
        auto viewport_upper_left = center_ - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc_ = viewport_upper_left + 0.5 * (pixel_delta_u_ + pixel_delta_v_);

    }

    Ray getRay(int i, int j) const
    {
        auto offset = sampleSquare();
        auto pixel_sample = pixel00_loc_ + (i+offset.x)*pixel_delta_u_ + (j+offset.y)*pixel_delta_v_;

        auto ray_origin = center_;
        auto ray_direction = pixel_sample - ray_origin;
        
        return Ray(ray_origin, ray_direction);
    }

    Vec3 sampleSquare() const
    {
        return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    Color rayColor(const Ray& r, const Hittable& world)
    {
        HitRecord rec;
        if (world.hit(r, Interval(0, infinity), rec))
            return 0.5*(rec.normal+Color(1, 1, 1));

        auto unit_direction = unitVector(r.direction());
        auto a = 0.5*(unit_direction.y + 1.0);

        return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
    }
};