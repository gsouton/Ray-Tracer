#pragma once

#include "rthelper.h"
#include <cmath>
#include <iostream>
#include <ostream>


class Vec3 {
  public:
    Vec3() : m_components{0.0, 0.0, 0.0} {}
    Vec3(double x, double y, double z): m_components{x, y, z}{}
    double x() const { return m_components[0]; }
    double y() const { return m_components[1]; }
    double z() const { return m_components[2]; }

    Vec3 operator-() const {
        return Vec3(-m_components[0], -m_components[1], -m_components[2]);
    }

    double operator[](int i) const { return m_components[i];}
    double& operator[](int i) {return m_components[i];}

    Vec3& operator+=(const Vec3 &v){
        m_components[0] += v.m_components[0];
        m_components[1] += v.m_components[1];
        m_components[2] += v.m_components[2];
        return *this;
    }

    Vec3& operator*=(const double t){
        m_components[0] *= t;
        m_components[1] *= t;
        m_components[2] *= t;
        return *this;
    }

    Vec3& operator/=(const double t){
        m_components[0] /= t;
        m_components[1] /= t;
        m_components[2] /= t;
        return *this;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return m_components[0] * m_components[0] + m_components[1] * m_components[1] + m_components[2] * m_components[2];
    }

    bool near_zero() const {
        return (std::fabs(m_components[0]) < close_to_zero) && (std::fabs(m_components[1]) < close_to_zero) && (std::fabs(m_components[2]) < close_to_zero);
    }

    inline static Vec3 random(){
        return Vec3(random_double(), random_double(), random_double());
    }

    inline static Vec3 random(double min, double max){
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }


  private:
    double m_components[3];
};

// Aliases
using Point3 = Vec3; // Point in 3D space
using Color = Vec3; // RGB color


// Utilities functions
inline std::ostream& operator<<(std::ostream &out, const Vec3 &v){
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline Vec3 operator+(const Vec3 &v, const Vec3 &u){
    return Vec3(v[0] + u[0], v[1] + u[1], v[2] + u[2]);
}

inline Vec3 operator-(const Vec3 &v, const Vec3 &u){
    return Vec3(v[0] - u[0], v[1] - u[1], v[2] - u[2]);
}

inline Vec3 operator*(const Vec3 &v, const Vec3 &u){
    return Vec3(v[0] * u[0], v[1] * u[1], v[2] * u[2]);
}

inline Vec3 operator*(double t, const Vec3 &v){
    return Vec3(v[0] * t, v[1] * t, v[2] * t);
}

inline Vec3 operator*(const Vec3 &v, double t){
    return Vec3(v[0] * t, v[1] * t, v[2] * t);
}

inline Vec3 operator/(double t, const Vec3 &v){
    return 1/t * v;
}

inline Vec3 operator/(const Vec3 &v, double t){
    return 1/t * v;
}

inline double dot(const Vec3 &u, const Vec3 &v){
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

Vec3 random_in_unit_sphere(){
    while(true){
        Vec3 v = Vec3::random(-1, 1);
        if(v.length_squared() >= 1) continue;
        return v;
    }
}

Vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

Vec3 reflect(const Vec3& incoming_vec, const Vec3& normal){
    return incoming_vec - 2 * dot(incoming_vec, normal)*normal;
}
