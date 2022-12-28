#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

#include "material.h"
#include "rthelper.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "vec3.h"
#include "image.h"


color ray_color(const ray& r, const hittable& world, int depth){
    hit_record record;
    if(depth <= 0)
        return color(0,0,0);
    if(world.hit(r, 0.001, infinity, record)){
        ray scattered_ray;
        color attenuation;
        if(record.material_ptr->scatter(r, record, attenuation, scattered_ray))
            return attenuation * ray_color(scattered_ray, world, depth-1);
        return color(0,0,0);

        // return 0.5 * (record.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}



int main() {
    // Image
    image img;

    // World
    hittable_list world;
    std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(
            color(0.8, 0.8, 0.0));
    std::shared_ptr<lambertian> material_sphere = std::make_shared<lambertian>(
            color(0.7, 0.3, 0.3));
    std::shared_ptr<metal> material_metal_sphere = std::make_shared<metal>(
            color(0.8, 0.8, 0.8));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5, material_sphere));
    world.add(std::make_shared<sphere>(point3(1.0,0,-1), 0.5, material_metal_sphere));

    // Camera
    camera cam;


    // Render
    timer t;
    t.start();
    std::cout << "P3\n" << img.width() << ' ' << img.height() << "\n255\n";
    for (int y = img.height() - 1; y >= 0; --y) {
        std::cerr << "\rLines remaining " << y << ' ' << std::flush;
        for (int x = 0; x < img.width(); ++x) {
            color pixel_color(0,0,0);
            for(int sample = 0; sample < img.sample_per_pixel(); ++sample){
                double u = (double(x) + random_double()) / (img.width() - 1);
                double v = (double(y) + random_double()) / (img.height() -1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, img.max_depth());
            }
            write_color(std::cout, pixel_color, img.sample_per_pixel());
        }
    }
    t.stop();
    std::cerr << "\nDone!" << std::endl;
    std::cerr << "Rendering took: " << t.result_ms().count() << " ms\n";
    return 0;
}
