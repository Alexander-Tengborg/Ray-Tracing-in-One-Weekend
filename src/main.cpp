#include <iostream>

#include "Color.h"
#include "Vec3.h"

int main()
{
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rProgess: " << static_cast<int>(100.0 * j/image_height) << "%" << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            auto pixelColor = Color(r, g, b);

            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.               \n";

    return 0;
}