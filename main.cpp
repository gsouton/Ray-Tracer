#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "image.h"
#include "material.h"
#include "renderer.h"
#include "rthelper.h"
#include "scene.h"
#include "sphere.h"
#include "vec3.h"

int main() {

    // Image
    Image img(1024);

    // Create a scene with 2 spheres
    std::shared_ptr<Lambertian> material_ground =
        std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    std::shared_ptr<Material> material_sphere =
        std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    std::shared_ptr<Material> material_metal_sphere =
        std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
    Scene scene;
    scene.add(
        std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, material_ground));
    // scene.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, material_sphere));
    scene.add(std::make_shared<Sphere>(Point3(1.0, 0, -1), 0.5,
                                       material_metal_sphere));

    // Camera
    Camera cam;
    // Renderer
    Renderer renderer(cam, scene, img);

    Timer t;

    // Render
    t.start();
    renderer.render();
    t.stop();

    std::cerr << "Rendering done in: " << t.result_ms().count() << " ms\n";
    // img.write_img();
    img.write_img(std::cout);
    return 0;
}
