#pragma once

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

class Scene {
    public:
        Scene(): m_hittable_list(){}

        void add(std::shared_ptr<Sphere> sphere){
            m_hittable_list.add(sphere);
        }

        bool ray_hit(const Ray& ray, double t_min, double t_max, hit_record& record) const{ 
            return m_hittable_list.hit(ray, t_min, t_max, record);
        }

    private:
        Hittable_list m_hittable_list;
};
