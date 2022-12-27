#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable {
    public:
        hittable_list() {}
        hittable_list(std::shared_ptr<hittable> object) { add(object); }
        
        void add(std::shared_ptr<hittable> object) { m_objects.push_back(object);}
        void clear() { m_objects.clear(); }

        virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& record) const override;

    private:
        std::vector<std::shared_ptr<hittable>> m_objects;
};

bool hittable_list::hit(const ray& ray, double t_min, double t_max, hit_record& record) const {
    bool hit_anything = false;
    hit_record temporary_record;
    double closest_so_far = t_max;

    for(const auto& object : m_objects){
        if(object->hit(ray, t_min, closest_so_far, temporary_record)){
            hit_anything = true;
            closest_so_far = temporary_record.t;
            record = temporary_record;
        }
    }
    return hit_anything;
}
