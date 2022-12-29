#pragma once
#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "image.h"
#include "omp.h"
#include "scene.h"

class Renderer {
  public:
    Renderer(Camera &cam, Scene &scene, Image &img)
        : m_cam(cam), m_scene(scene), m_img(img){};

    void render() {
        // renderSequential();
        renderOpenMP();
        // renderForEach();
    }

    void computeForPixel(int x, int y) {
        Color pixel_color(0, 0, 0);
        for (int sample = 0; sample < m_img.sample_per_pixel(); ++sample) {
            double u = (double(x) + random_double()) / (m_img.width() - 1);
            double v = (double(y) + random_double()) / (m_img.height() - 1);
            Ray ray = m_cam.get_ray(u, v);
            pixel_color += compute_ray(ray, m_img.max_depth());
        }
        m_img.set_pixel(x, y, pixel_color);
    }

    void renderSequential() {
        for (int y = 0; y < m_img.height(); ++y) {
            for (int x = 0; x < m_img.width(); ++x) {
                computeForPixel(x, y);
            }
        }
    }

    void renderOpenMP() {
#pragma omp parallel for schedule(dynamic) shared(m_cam, m_scene, m_img)       \
    collapse(2)
        for (int y = 0; y < m_img.height(); ++y) {
            for (int x = 0; x < m_img.width(); ++x) {
                computeForPixel(x, y);
            }
        }
    }

    void renderForEach() {
        initIterators();

        std::for_each(std::execution::par, m_vertical_image_iterator.begin(),
                      m_vertical_image_iterator.end(), [this](int y) {
                          std::for_each(
                              std::execution::par,
                              m_horizontal_image_iterator.begin(),
                              m_horizontal_image_iterator.end(),
                              [this, y](int x) { computeForPixel(x, y); });
                      });
    }

    void initIterators() {
        m_horizontal_image_iterator.resize(m_img.width());
        m_vertical_image_iterator.resize(m_img.height());

        for (int i = 0; i < m_img.width(); ++i) {
            m_horizontal_image_iterator[i] = i;
        }
        for (int i = 0; i < m_img.height(); ++i) {
            m_vertical_image_iterator[i] = i;
        }
    }

    Color compute_ray(const Ray &r, int depth) {
        hit_record record;
        if (depth <= 0)
            return Color(0, 0, 0);
        if (m_scene.ray_hit(r, 0.001, infinity, record)) {
            Ray scattered_ray;
            Color attenuation;
            if (record.material_ptr->scatter(r, record, attenuation,
                                             scattered_ray))
                return attenuation * compute_ray(scattered_ray, depth - 1);
            return Color(0, 0, 0);
        }
        Vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }

  private:
    Camera &m_cam;
    Scene &m_scene;
    Image &m_img;
    std::vector<int> m_horizontal_image_iterator;
    std::vector<int> m_vertical_image_iterator;
};
