#pragma once

#include "vec3.h"
#include "rthelper.h"

#include <iostream>

void write_color(std::ostream &out, color color, int sample_per_pixel){
    double r = color.x();
    double g = color.y();
    double b = color.z();

    // Divide the color by the number of sample
    double scale = 1.0 / sample_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    
    // Write the translated [0,255] value of each color component
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';



 }
