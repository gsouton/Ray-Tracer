#pragma once

#include "hittable.h"
#include "material.h"
#include <cmath>
#include <memory>

class Sphere: public Hittable {
    public:
        Sphere() {}
        Sphere(Point3 center, double radius, std::shared_ptr<Material> material_ptr): m_center(center), m_radius(radius), m_material_ptr(material_ptr) {}
        virtual bool hit(const Ray& ray, double t_min, double t_max, hit_record& record) const override;

    private:
        Point3 m_center;
        double m_radius;
        std::shared_ptr<Material> m_material_ptr;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& record) const{
    Vec3 oc = r.origin() - m_center;
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
    Vec3 outward_normal = (record.p - m_center) / m_radius;
    record.set_face_normal(r,outward_normal);
    record.material_ptr = m_material_ptr;
    return true;
}
