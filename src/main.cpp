#include <iostream>

#include "Color.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

#include "MathUtils.h"

#include "Camera.h"
#include "Material.h"

int main()
{
    // World
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = randomDouble();
            Point3 center(a + 0.9*randomDouble(), 0.2, b + 0.9*randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // Diffuse material
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);

                }
                else if (choose_mat < 0.95)
                {
                    // Metal material
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                }
                else
                {
                    // Glass material
                    sphere_material = std::make_shared<Dielectric>(1.5);
                }

                world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
        }
    }

    // auto material1 = std::make_shared<Dielectric>(1.5);
    // world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    // auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    // world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    // auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    // world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    // Camera
    Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1920;
    camera.samples_per_pixel = 500;
    camera.max_depth = 200;

    camera.vfov = 20;
    camera.look_from = Point3(13, 2, 3);
    camera.look_at = Point3(0, 0,0);
    camera.v_up = Vec3(0, 1, 0);

    camera.defocus_angle = 0.6;
    camera.focus_dist = 10.0;

    camera.render(world);

    return 0;
}