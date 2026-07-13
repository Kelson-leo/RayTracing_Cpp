#pragma once

#include "ray.h"
#include "utils.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         vec3& attenuation, ray& scattered, rng& r) const = 0;
};
