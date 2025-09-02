#include <iostream>

#include "Color.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

#include "MathUtils.h"

#include "Camera.h"


int main()
{
    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(2.0, -0.2, -2), 0.3));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1280;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;

    camera.render(world);

    return 0;
}