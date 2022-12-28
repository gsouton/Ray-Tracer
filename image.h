#pragma once

const double default_aspect_ratio = 16.0 / 9.0;
const int default_width = 400;
const int default_height = static_cast<int>(default_width/default_aspect_ratio);
const double default_sample_per_pixel = 100;
const int default_depth = 50;


class image {
    public:
        image(double aspect_ratio, int width, int sample_per_pixel, int max_depth)
            : m_aspect_ratio(aspect_ratio), 
            m_width(width), 
            m_height(static_cast<int>(width/aspect_ratio)),
            m_sample_per_pixel(sample_per_pixel),
            m_max_depth(max_depth)
            {}

        image():
            m_aspect_ratio(default_aspect_ratio),
            m_width(default_width),
            m_height(default_height),
            m_sample_per_pixel(default_sample_per_pixel),
            m_max_depth(default_depth)
            {}

        image(int width) :
            m_aspect_ratio(default_aspect_ratio), 
            m_width(width), 
            m_height(static_cast<int>(width/ default_aspect_ratio)),
            m_sample_per_pixel(default_sample_per_pixel)
            {}

        int width() const { return m_width;}
        int height() const { return m_height;}
        int sample_per_pixel() const { return m_sample_per_pixel;}
        int max_depth() const {return m_max_depth;}


    private:
        double m_aspect_ratio;
        int m_width;
        int m_height;
        int m_sample_per_pixel;
        int m_max_depth;

};
