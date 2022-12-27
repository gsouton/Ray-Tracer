#include <cmath>
#include <iostream>
#include <ostream>

#include "vec3.h"
#include "ray.h"
#include "color.h"

// double hit_sphere(const point3& center, double radius, const ray& r){
//     vec3 oc = r.origin() - center;
//     double a = dot(r.direction(), r.direction());
//     double b = 2.0 * dot(oc, r.direction());
//     double c = dot(oc, oc) - radius*radius;
//     double discriminant = b*b - 4 *a*c;
//     if(discriminant < 0)
//         return -1.0;
//     else
//         return (-b - std::sqrt(discriminant)) /(2.0*a);
// }
double hit_sphere(const point3& center, double radius, const ray& r){
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius*radius;
    double discriminant = half_b*half_b - a*c;
    if(discriminant < 0)
        return -1.0;
    else
        return (-half_b - std::sqrt(discriminant)) / a;
}


color ray_color(const ray& r){
    double t = hit_sphere(point3(0, 0, -1.0), 0.5, r);
    if(t > 0.0){
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1.0));
        return 0.5*color(N.x()+1,N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0,1.0,1.0) + t * color(0.5,0.7,1.0);
}



int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
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
