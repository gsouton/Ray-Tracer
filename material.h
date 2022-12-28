#pragma once

#include "ray.h"
#include "vec3.h"

#include "hittable.h"


class material {
    public:
        virtual bool scatter(const ray& incoming_ray, const hit_record& record, color& attenuation, ray& scattered_ray) const = 0;
};

class lambertian : public material {
    public:
        lambertian(const color& albedo): m_albedo(albedo) {}

        virtual bool scatter(const ray& incoming_ray, const hit_record& record, color& attenuation, ray& scattered_ray) const override {
            vec3 scatter_direction = record.normal + random_unit_vector();
            if(scatter_direction.near_zero()) scatter_direction = record.normal;
            scattered_ray = ray(record.p, scatter_direction);
            attenuation = m_albedo;
            return true;
        }
    private:
        color m_albedo;
};

class metal : public material {
    public:
        metal(const color& albedo): m_albedo(albedo){}

        virtual bool scatter(const ray& incoming_ray, const hit_record& record, color& attenuation, ray& scattered_ray) const override {
            vec3 reflected = reflect(unit_vector(incoming_ray.direction()), record.normal);
            scattered_ray = ray(record.p, reflected);
            attenuation = m_albedo;
            return (dot(scattered_ray.direction(), record.normal) > 0);
        }

    private:
        color m_albedo;
};
