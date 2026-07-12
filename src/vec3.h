#pragma once

#include <cmath>
#include <iostream>

class vec3 {
public:
    using value_type = float;

    vec3() : e{0, 0, 0} {}                     
    constexpr vec3(value_type e0, value_type e1, value_type e2) 
        : e{e0, e1, e2} {}

    constexpr value_type x() const { return e[0]; }
    constexpr value_type y() const { return e[1]; }
    constexpr value_type z() const { return e[2]; }
    constexpr value_type r() const { return e[0]; }
    constexpr value_type g() const { return e[1]; }
    constexpr value_type b() const { return e[2]; }

    constexpr const vec3& operator+() const { return *this; }
    constexpr vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    constexpr value_type operator[](int i) const { return e[i]; }
    constexpr value_type& operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3& v) {
        e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2];
        return *this;
    }
    inline vec3& operator-=(const vec3& v) {
        e[0] -= v.e[0]; e[1] -= v.e[1]; e[2] -= v.e[2];
        return *this;
    }
    inline vec3& operator*=(const vec3& v) {
        e[0] *= v.e[0]; e[1] *= v.e[1]; e[2] *= v.e[2];
        return *this;
    }
    inline vec3& operator/=(const vec3& v) {
        e[0] /= v.e[0]; e[1] /= v.e[1]; e[2] /= v.e[2];
        return *this;
    }
    inline vec3& operator*=(value_type t) {
        e[0] *= t; e[1] *= t; e[2] *= t;
        return *this;
    }
    inline vec3& operator/=(value_type t) {
        value_type k = 1.0f / t;
        e[0] *= k; e[1] *= k; e[2] *= k;
        return *this;
    }

    inline value_type length() const {
        return std::sqrt(squared_length());
    }
    constexpr value_type squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline void make_unit_vector() {
        value_type k = 1.0f / length();
        e[0] *= k; e[1] *= k; e[2] *= k;
    }

private:
    value_type e[3];
};

inline std::istream& operator>>(std::istream& is, vec3& v) {
    is >> v[0] >> v[1] >> v[2];
    return is;
}
inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
    os << v[0] << ' ' << v[1] << ' ' << v[2];
    return os;
}

inline constexpr vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}
inline constexpr vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline constexpr vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}
inline constexpr vec3 operator/(const vec3& u, const vec3& v) {
    return vec3(u[0] / v[0], u[1] / v[1], u[2] / v[2]);
}

inline constexpr vec3 operator*(float t, const vec3& v) {
    return vec3(t * v[0], t * v[1], t * v[2]);
}
inline constexpr vec3 operator*(const vec3& v, float t) {
    return t * v;
}
inline constexpr vec3 operator/(const vec3& v, float t) {
    return vec3(v[0] / t, v[1] / t, v[2] / t);
}

// --- Funções Matemáticas Clássicas ---
inline constexpr float dot(const vec3& u, const vec3& v) {
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

inline constexpr vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u[1]*v[2] - u[2]*v[1],
                u[2]*v[0] - u[0]*v[2],
                u[0]*v[1] - u[1]*v[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}