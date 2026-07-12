#pragma once

#include "material.h"
#include "utils.h"

class lambertian : public material {
public:
    lambertian(const vec3& albedo) : albedo(albedo) {}

    bool scatter([[maybe_unused]] const ray& r_in, const hit_record& rec,
                 vec3& attenuation, ray& scattered) const override {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

private:
    vec3 albedo;
};