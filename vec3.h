#pragma once

#include <cmath>
#include <iostream>
#include <ostream>

class vec3 {
  public:
    vec3() : m_components{0.0, 0.0, 0.0} {}
    vec3(double x, double y, double z): m_components{x, y, z}{}
    double x() const { return m_components[0]; }
    double y() const { return m_components[1]; }
    double z() const { return m_components[2]; }

    vec3 operator-() const {
        return vec3(-m_components[0], -m_components[1], -m_components[2]);
    }

    double operator[](int i) const { return m_components[i];}
    double& operator[](int i) {return m_components[i];}

    vec3& operator+=(const vec3 &v){
        m_components[0] += v.m_components[0];
        m_components[1] += v.m_components[1];
        m_components[2] += v.m_components[2];
        return *this;
    }

    vec3& operator*=(const double t){
        m_components[0] *= t;
        m_components[1] *= t;
        m_components[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t){
        m_components[0] /= t;
        m_components[1] /= t;
        m_components[2] /= t;
        return *this;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return m_components[0] * m_components[0] + m_components[1] * m_components[1] + m_components[2];
    }

  private:
    double m_components[3];
};

// Aliases
using point3 = vec3; // Point in 3D space
using color = vec3; // RGB color


// Utilities functions
inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3 &v, const vec3 &u){
    return vec3(v[0] + u[0], v[1] + u[1], v[2] + u[2]);
}

inline vec3 operator-(const vec3 &v, const vec3 &u){
    return vec3(v[0] - u[0], v[1] - u[1], v[2] - u[2]);
}

inline vec3 operator*(const vec3 &v, const vec3 &u){
    return vec3(v[0] * u[0], v[1] * u[1], v[2] * u[2]);
}

inline vec3 operator*(double t, const vec3 &v){
    return vec3(v[0] * t, v[1] * t, v[2] * t);
}

inline vec3 operator*(const vec3 &v, double t){
    return vec3(v[0] * t, v[1] * t, v[2] * t);
}

inline vec3 operator/(double t, const vec3 &v){
    return 1/t * v;
}

inline vec3 operator/(const vec3 &v, double t){
    return 1/t * v;
}

inline double dot(const vec3 &u, const vec3 &v){
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}
