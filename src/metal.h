#pragma once
#include "material.h"
#include "utils.h"

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2.0f * dot(v, n) * n;
}

class metal : public material {
public:
    metal(const vec3& albedo, float fuzz = 0.0f)
        : albedo(albedo), fuzz(fuzz < 1.0f ? fuzz : 1.0f) {}

    bool scatter(const ray& r_in, const hit_record& rec,
                 vec3& attenuation, ray& scattered, rng& r) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        vec3 scattered_dir = reflected + fuzz * random_in_unit_sphere(r);
        scattered = ray(rec.p, scattered_dir);
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0.0f;
    }

private:
    vec3 albedo;
    float fuzz;
};
