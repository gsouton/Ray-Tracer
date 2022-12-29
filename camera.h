#pragma once

#include "ray.h"
#include "rthelper.h"
#include "vec3.h"

class Camera {
  public:
    Camera() {
        double aspect_ratio = 16.0 / 9.0;
        double viewport_height = 2.0;
        double viewport_width = aspect_ratio * viewport_height;
        double focal_length = 1.0;

        m_origin = Point3(0, 0, 0);
        m_horizontal = Vec3(viewport_width, 0, 0);
        m_vertical = Vec3(0, viewport_height, 0);
        // m_lower_left_corner = m_origin - m_horizontal/2 - m_vertical/2 -
        //     Vec3(0,0,focal_length);
        m_top_left_corner = m_origin - m_horizontal / 2 + m_vertical / 2 -
                            Vec3(0, 0, focal_length);
    }

    Ray get_ray(double u, double v) const {
        return Ray(m_origin, m_top_left_corner + u * m_horizontal -
                                 v * m_vertical - m_origin);
    }

  private:
    Point3 m_origin;
    // Point3 m_lower_left_corner;
    Point3 m_top_left_corner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
};
