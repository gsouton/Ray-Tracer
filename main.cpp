#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

#include "rthelper.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


color ray_color(const ray& ray, const hittable& world){
    hit_record record;
    if(world.hit(ray, 0, infinity, record)){
        return 0.5 * (record.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(ray.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}



int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

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
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone!" << std::endl;
    return 0;
}
