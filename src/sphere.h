#pragma once
#include "hittable.h"
#include "material.h"
#include <memory>

class sphere : public hittable {
public:
    sphere() = default;
    sphere(const vec3& center, float radius, std::shared_ptr<material> mat)
        : center(center), radius(radius), mat_ptr(mat) {}

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        float a = dot(r.direction(), r.direction());
        float b = dot(oc, r.direction());
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b*b - a*c;

        if (discriminant < 0) return false;

        float sqrt_disc = sqrt(discriminant);
        float temp = (-b - sqrt_disc) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;  
            return true;
        }
        temp = (-b + sqrt_disc) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        return false;
    }

private:
    vec3 center;
    float radius;
    std::shared_ptr<material> mat_ptr;
};