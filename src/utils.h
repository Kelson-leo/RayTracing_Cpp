#pragma once
#include <random>
#include "vec3.h"

struct rng {
    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;
    rng() : gen(std::random_device{}()), dis(0.0f, 1.0f) {}
    float next() { return dis(gen); }
};

inline float random_float(rng& r) {
    return r.next();
}

inline vec3 random_in_unit_sphere(rng& r) {
    vec3 p;
    do {
        p = 2.0f * vec3(random_float(r), random_float(r), random_float(r)) - vec3(1.0f, 1.0f, 1.0f);
    } while (p.squared_length() >= 1.0f);
    return p;
}

inline vec3 random_in_unit_disk(rng& r) {
    vec3 p;
    do {
        p = 2.0f * vec3(random_float(r), random_float(r), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
    } while (p.squared_length() >= 1.0f);
    return p;
}
