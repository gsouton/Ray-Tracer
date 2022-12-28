#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>
#include <chrono>
#include <ratio>


// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
const double close_to_zero = 1e-8;

// Utility functions
inline double degrees_to_radius(double degreees){
    return degreees * pi / 180.0;
}

inline double clamp(double x, double min , double max){
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

// Implementation base on cstdlib
// inline double random_double(){
//     return rand() / (RAND_MAX + 1.0);
// }

inline double random_double(){
    static std::uniform_real_distribution<double>distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);

}

inline double random_double(double min, double max){
    return min + (max - min) * random_double();
}

// Benchmark utils
struct timer {
    std::chrono::system_clock::time_point begin;
    std::chrono::system_clock::time_point end;

    void start(){
        begin = std::chrono::high_resolution_clock::now();
    }
    void stop(){
        end = std::chrono::high_resolution_clock::now();
    }

    std::chrono::duration<double, std::milli> result_ms(){
        std::chrono::duration<double, std::milli> duration = end - begin;
        return duration;
    }
};

