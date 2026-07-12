#pragma once
#include <random>
#include "vec3.h"

inline std::random_device rd;
inline std::mt19937 gen(rd());
inline std::uniform_real_distribution<float> dis(0.0f, 1.0f);

inline float random_float() {
    return dis(gen);
}

inline vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0f * vec3(random_float(), random_float(), random_float()) - vec3(1.0f, 1.0f, 1.0f);
    } while (p.squared_length() >= 1.0f);
    return p;
}

inline vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0f * vec3(random_float(), random_float(), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
    } while (p.squared_length() >= 1.0f);
    return p;
}