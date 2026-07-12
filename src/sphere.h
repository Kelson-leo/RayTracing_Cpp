#pragma once

#include "hittable.h"

class sphere : public hittable {
public:
    sphere() = default;
    sphere(const vec3& center, float radius) : center(center), radius(radius) {}

    bool hit(const ray& r, float t_min, float t_max, float& t_out) const override {
        vec3 oc = r.origin() - center;
        float a = dot(r.direction(), r.direction());
        float b = 2.0f * dot(oc, r.direction());
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4.0f * a * c;

        if (discriminant < 0.0f) {
            return false;
        }

        float sqrt_disc = sqrt(discriminant);
        float t = (-b - sqrt_disc) / (2.0f * a); 

        if (t < t_min || t > t_max) {
            t = (-b + sqrt_disc) / (2.0f * a);   
            if (t < t_min || t > t_max) {
                return false;
            }
        }

        t_out = t;
        return true;
    }

private:
    vec3 center;
    float radius;
};