#pragma once

#include "ray.h"

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, float t_min, float t_max, float& t_out) const = 0;
};