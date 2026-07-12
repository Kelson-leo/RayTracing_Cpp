#pragma once
#include "material.h"
#include "utils.h"
#include <cmath>

inline bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    if (discriminant > 0.0f) {
        refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
        return true;
    }
    return false;
}

inline float schlick(float cosine, float ref_idx) {
    float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * std::pow((1.0f - cosine), 5.0f);
}

class dielectric : public material {
public:
    dielectric(float ri) : ref_idx(ri) {}

    bool scatter(const ray& r_in, const hit_record& rec,
                 vec3& attenuation, ray& scattered) const override {
        attenuation = vec3(1.0f, 1.0f, 1.0f); 

        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        float cosine;

        if (dot(r_in.direction(), rec.normal) > 0.0f) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0f / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }

        vec3 refracted;
        float reflect_prob;

        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            reflect_prob = 1.0f;
        }

        if (random_float() < reflect_prob) {
            scattered = ray(rec.p, reflected);
        } else {
            scattered = ray(rec.p, refracted);
        }
        return true;
    }

private:
    float ref_idx; 
};