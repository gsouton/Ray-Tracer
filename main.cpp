#include <iostream>
#include <ostream>

#include "vec3.h"
#include "ray.h"
#include "color.h"

color ray_color(const ray& r){
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0,1.0,1.0) + t * color(0.5,0.7,1.0);
}

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 460;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    point3 origin = point3(0, 0, 0);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    point3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y) {
        std::cerr << "\rLines remaining " << y << ' ' << std::flush;
        for (int x = 0; x < image_width; ++x) {
            double u = double(x) / (image_width - 1);
            double v = double(y) / (image_height -1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            // color pixel_color(double(x) / (image_width - 1),
            //                   double(y) / (image_height - 1), 0.25);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone!" << std::endl;
    return 0;
}
