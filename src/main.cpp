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

    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.3, 0.1));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<Dielectric>(1.50);
    auto material_bubble = std::make_shared<Dielectric>(1.00 / 1.50);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);
    auto material_close_right = std::make_shared<Metal>(Color(0.2, 0.6, 0.2), 0.0);

    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-0.9, -0.1, -0.8), 0.4, material_left));
    world.add(std::make_shared<Sphere>(Point3(-0.9, -0.1, -0.8), 0.25, material_bubble));
    world.add(std::make_shared<Sphere>(Point3(2.0, -0.2, -2), 0.3, material_right));
    world.add(std::make_shared<Sphere>(Point3(1.2, -0.3, -1), 0.1, material_close_right));

    // auto R = std::cos(PI/4);

    // auto material_left = std::make_shared<Lambertian>(Color(0, 0, 1));
    // auto material_right = std::make_shared<Lambertian>(Color(1, 0, 0));

    // world.add(std::make_shared<Sphere>(Point3(-R, 0, -1), R, material_left));
    // world.add(std::make_shared<Sphere>(Point3(R, 0, -1), R, material_right));

    // Camera
    Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 800;
    camera.samples_per_pixel = 100;
    camera.max_depth = 500;

    camera.vfov = 20;
    camera.look_from = Point3(-2, 2, 1);
    camera.look_at = Point3(-0, 0, -1);
    camera.v_up = Vec3(0, 1, 0);

    camera.render(world);

    return 0;
}