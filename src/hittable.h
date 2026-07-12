#pragma once

#include "ray.h"
#include "aabb.h"
#include <memory>

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
};

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(aabb& box) const = 0;
};
