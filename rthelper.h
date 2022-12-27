#pragma once

#include <cmath>
#include <limits>
#include <memory>

// Common headers
#include "ray.h"
#include "vec3.h"

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
inline double degrees_to_radius(double degreees){
    return degreees * pi / 180.0;
}
