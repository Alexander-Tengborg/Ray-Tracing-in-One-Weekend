#include <iostream>

#include "Color.h"
#include "Vec3.h"
#include "Ray.h"

Color rayColor(const Ray& r)
{
    auto unit_direction = unitVector(r.direction());

    auto a = 0.5*(unit_direction.y + 1.0);

    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}

int main()
{
    auto aspect_ratio = 16.0 / 9.0;

    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * static_cast<double>(image_width) / image_height;
    auto camera_center = Point3(0, 0, 0);

    // Horizontal and Vertical viewport edges
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);

    // Pixel to pixel deltas
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Upper left viewport and pixel
    auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rProgess: " << static_cast<int>(100.0 * j/image_height) << "%" << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            Ray ray(camera_center, ray_direction);

            auto pixelColor = rayColor(ray);

            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.               \n";

    return 0;
}