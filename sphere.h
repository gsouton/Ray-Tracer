#pragma once

#include "hittable.h"
#include "material.h"
#include <cmath>
#include <memory>

class sphere: public hittable {
    public:
        sphere() {}
        sphere(point3 center, double radius, std::shared_ptr<material> material_ptr): m_center(center), m_radius(radius), m_material_ptr(material_ptr) {}
        virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& record) const override;

    private:
        point3 m_center;
        double m_radius;
        std::shared_ptr<material> m_material_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& record) const{
    vec3 oc = r.origin() - m_center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - m_radius*m_radius;
    double discriminant = half_b*half_b - a*c;

    if(discriminant < 0) return false;
    double sqrt_discriminant = std::sqrt(discriminant);
    
    // Find the neareast root that lies in the acceptable range
    double root = (-half_b - sqrt_discriminant) / a;
    if(root < t_min || t_max < root){
        root = (-half_b + sqrt_discriminant) / a;
        if(root < t_min || t_max < root) return false;
    }

    record.t = root;
    record.p = r.at(record.t);
    vec3 outward_normal = (record.p - m_center) / m_radius;
    record.set_face_normal(r,outward_normal);
    record.material_ptr = m_material_ptr;
    return true;
}
