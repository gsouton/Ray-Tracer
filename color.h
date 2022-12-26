#pragma once

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color color){
    out << static_cast<int>(255.999 * color.x())  << ' '
            << static_cast<int>(255.999 * color.y()) << ' '
            << static_cast<int>(255.999 * color.z()) << '\n';
}
