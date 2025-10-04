#pragma once

#include "Hittable.h"
#include "Color.h"
#include "Material.h"

class Camera
{
public:
    double aspect_ratio = 1.0; // Ratio of image width and height
    int image_width = 100; // The width of the image in pixels
    int samples_per_pixel = 10; // Amount of random samples for each pixel
    int max_depth = 10; // Amount of times a ray can bounce

    double vfov = 90.0; // Vertical view angle / field of view in degrees
    Point3 look_from = Point3(0, 0, 0); // The position the camera is looking from
    Point3 look_at = Point3(0, 0, -1); // The position the camera is looking at
    Vec3 v_up = Vec3(0, 1, 0); // Camera-relative up direction

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
                    pixel_color += rayColor(r, max_depth, world);
                }

                writeColor(std::cout, pixel_samples_scale_ * pixel_color);
            }
        }

        std::clog << "\rDone.               \n";
    }

private:
    int image_height_; // The height of the image in pixels
    double pixel_samples_scale_; // Color scale factor for a sum of pixel samples
    Point3 center_; // Camera center
    Point3 pixel00_loc_; // Location of pixel (0, 0)
    Vec3 pixel_delta_u_; // Offset to pixel to the right
    Vec3 pixel_delta_v_; // Offset to pixel below
    Vec3 u_, v_, w_; // Camera frame basis vectors

    void initialize()
    {
        image_height_ = static_cast<int>(image_width / aspect_ratio);
        image_height_ = (image_height_ < 1) ? 1 : image_height_;

        pixel_samples_scale_ = 1.0 / samples_per_pixel;

        center_ = look_from;

        // Viewport dimensions
        auto focal_length = (look_from - look_at).length();
        auto theta = radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2.0 * h * focal_length;
        auto viewport_width = viewport_height * aspect_ratio; // static_cast<double>(image_width) / image_height_;

        // Calculate the frame basis vectors u_, v_ and w_ for the camera coordinate frame
        w_ = unitVector(look_from - look_at);
        u_ = unitVector(cross(v_up, w_));
        v_ = cross(w_, u_);

        // Horizontal and Vertical viewport edges
        Vec3 viewport_u = viewport_width * u_;
        Vec3 viewport_v = viewport_height * -v_;

        // Pixel to pixel deltas
        pixel_delta_u_ = viewport_u / image_width;
        pixel_delta_v_ = viewport_v / image_height_;

        // Upper left viewport and pixel
        auto viewport_upper_left = center_ - (focal_length * w_) - viewport_u/2 - viewport_v/2;
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
        return Vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
    }

    Color rayColor(const Ray& r, int depth, const Hittable& world)
    {
        if (depth <= 0)
            return Color(0.0, 0.0, 0.0);

        HitRecord rec;

        // Uses 0.001 instead of 0 to get rid off "shadow acne"
        if (world.hit(r, Interval(0.001, infinity), rec))
        {
            Color attenuation;
            Ray scattered_ray;

            if (rec.mat->scatter(r, rec, attenuation, scattered_ray))
                return attenuation * rayColor(scattered_ray, depth-1, world);

            return Color(0.0, 0.0, 0.0);
        }

        auto unit_direction = unitVector(r.direction());
        auto a = 0.5*(unit_direction.y + 1.0);

        return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
    }
};