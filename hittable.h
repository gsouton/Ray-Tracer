#pragma once

#include "ray.h"

class Material;

struct hit_record {
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> material_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray &ray, const Vec3 &outward_normal) {
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
  public:
    virtual bool hit(const Ray &Ray, double t_min, double t_max,
                     hit_record &record) const = 0;
};
