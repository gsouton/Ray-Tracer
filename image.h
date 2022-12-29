#pragma once

#include "vec3.h"
#include <cstdint>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Constants
const double default_aspect_ratio = 16.0 / 9.0;
const int default_width = 400;
const int default_height = static_cast<int>(default_width/default_aspect_ratio);
const double default_sample_per_pixel = 100;
const int default_depth = 10;
const char* default_filename = "image.png";


class Image {
    public:
        Image(double aspect_ratio, int width, int sample_per_pixel, int max_depth)
            : m_aspect_ratio(aspect_ratio), 
            m_width(width), 
            m_height(static_cast<int>(width/aspect_ratio)),
            m_sample_per_pixel(sample_per_pixel),
            m_max_depth(max_depth),
            m_num_pixels(m_width*m_height)
            {
                m_data = new Color[m_num_pixels];
            }

        Image():
            m_aspect_ratio(default_aspect_ratio),
            m_width(default_width),
            m_height(default_height),
            m_sample_per_pixel(default_sample_per_pixel),
            m_max_depth(default_depth),
            m_num_pixels(m_width*m_height)
            {
                m_data = new Color[m_num_pixels];
            }


        Image(int width) :
            m_aspect_ratio(default_aspect_ratio), 
            m_width(width), 
            m_height(static_cast<int>(width/ default_aspect_ratio)),
            m_sample_per_pixel(default_sample_per_pixel),
            m_max_depth(default_depth),
            m_num_pixels(m_width*m_height)
            {
                m_data = new Color[m_num_pixels];
            }
        ~Image(){
            delete [] m_data;
        }

        int width() const { return m_width;}
        int height() const { return m_height;}
        int sample_per_pixel() const { return m_sample_per_pixel;}
        int max_depth() const {return m_max_depth;}

        Color& operator[](int i){
            return m_data[i];
        }

        void set_pixel(int x, int y, Color& pixel_color) {
            m_data[y * width() + x] = pixel_color;
        }

        void write_img(){
            std::cout << "writing Image..." << std::endl;
            //TODO: remove hardcoded value and get the number compoenent from color
            // Color.num_compoenent()
            int num_compoenent = 3;
            int data[m_width*m_height*num_compoenent];
            for(int i = 0, index = 0; i < m_num_pixels; i++, index+=num_compoenent){
                double r = m_data[i].x();
                double g = m_data[i].y();
                double b = m_data[i].z();

                // Divide the color by the number of sample
                double scale = 1.0 / m_sample_per_pixel;
                r = sqrt(scale * r);
                g = sqrt(scale * g);
                b = sqrt(scale * b);

                data[index] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
                data[index+1] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
                data[index+2] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
            }
            for(int i = 0; i < m_width*m_height; i+=num_compoenent){
                std::cerr << data[i] << " " << data[i+1] << " " << data[i+2] << std::endl;
            }
            stbi_write_png(default_filename, m_width, m_height, 
                    3, data, 0);
            // stbi_write_bmp(default_filename, m_width, m_height, 3, data);
        }

        void write_img(std::ostream &out){
            std::cout << "P3\n" << m_width << ' ' << m_height << "\n255\n";
            for(int i = 0; i < m_num_pixels; ++i){
                double r = m_data[i].x();
                double g = m_data[i].y();
                double b = m_data[i].z();

                // Divide the color by the number of sample
                double scale = 1.0 / m_sample_per_pixel;
                r = sqrt(scale * r);
                g = sqrt(scale * g);
                b = sqrt(scale * b);
                
                // Write the translated [0,255] value of each color component
                out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
                    << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
                    << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
                }
        }

    private:
        double m_aspect_ratio;
        int m_width;
        int m_height;
        int m_sample_per_pixel;
        int m_max_depth;
        int m_num_pixels;
        Color *m_data;

};
