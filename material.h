#pragma once

#include "ray.h"
#include "rthelper.h"
#include "vec3.h"

#include "hittable.h"

class Material {
  public:
    virtual bool scatter(const Ray &incoming_ray, const hit_record &record,
                         Color &attenuation, Ray &scattered_ray) const = 0;
};

class Lambertian : public Material {
  public:
    Lambertian(const Color &albedo) : m_albedo(albedo) {}

    virtual bool scatter(const Ray &incoming_ray, const hit_record &record,
                         Color &attenuation,
                         Ray &scattered_ray) const override {
        Vec3 scatter_direction = record.normal + random_unit_vector();
        if (scatter_direction.near_zero())
            scatter_direction = record.normal;
        scattered_ray = Ray(record.p, scatter_direction);
        attenuation = m_albedo;
        return true;
    }

  private:
    Color m_albedo;
};

class Metal : public Material {
  public:
    Metal(const Color &albedo, double fuzziness)
        : m_albedo(albedo)  {
            m_fuzz = fuzziness < 1 ? fuzziness : 1;
        }

    virtual bool scatter(const Ray &incoming_ray, const hit_record &record,
                         Color &attenuation,
                         Ray &scattered_ray) const override {
        Vec3 reflected =
            reflect(unit_vector(incoming_ray.direction()), record.normal);
        scattered_ray = Ray(record.p, reflected + m_fuzz*random_in_unit_sphere());
        attenuation = m_albedo;
        return (dot(scattered_ray.direction(), record.normal) > 0);
    }

  private:
    Color m_albedo;
    double m_fuzz;
};
