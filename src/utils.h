#pragma once

#include <random>
#include "vec3.h"

inline std::random_device rd;
inline std::mt19937 gen(rd());
inline std::uniform_real_distribution<float> dis(0.0f, 1.0f);

inline vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0f * vec3(dis(gen), dis(gen), dis(gen)) - vec3(1.0f, 1.0f, 1.0f);
    } while (p.squared_length() >= 1.0f);
    return p;
}