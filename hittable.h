#pragma once

#include "ray.h"

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    std::shared_ptr<material> material_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& ray, const vec3& outward_normal){
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& record) const = 0;
};
