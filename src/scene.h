#pragma once

#include <memory>
#include <vector>
#include "bvh.h"
#include "hitable_list.h"
#include "sphere.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "utils.h"

inline std::unique_ptr<hittable> random_scene() {
    rng r;
    std::vector<std::shared_ptr<hittable>> objects;

    auto ground_mat = std::make_shared<lambertian>(vec3(0.5f, 0.5f, 0.5f));
    objects.push_back(std::make_shared<sphere>(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, ground_mat));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            float choose_mat = random_float(r);
            vec3 center(float(a) + 0.9f * random_float(r),
                        0.2f,
                        float(b) + 0.9f * random_float(r));

            if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                std::shared_ptr<material> mat;

                if (choose_mat < 0.8f) {
                    vec3 albedo(random_float(r) * random_float(r),
                                random_float(r) * random_float(r),
                                random_float(r) * random_float(r));
                    mat = std::make_shared<lambertian>(albedo);
                } else if (choose_mat < 0.95f) {
                    vec3 albedo(0.5f * (1.0f + random_float(r)),
                                0.5f * (1.0f + random_float(r)),
                                0.5f * (1.0f + random_float(r)));
                    float fuzz = 0.5f * random_float(r);
                    mat = std::make_shared<metal>(albedo, fuzz);
                } else {
                    mat = std::make_shared<dielectric>(1.5f);
                }

                objects.push_back(std::make_shared<sphere>(center, 0.2f, mat));
            }
        }
    }

    auto glass_mat = std::make_shared<dielectric>(1.5f);
    objects.push_back(std::make_shared<sphere>(vec3(0.0f, 1.0f, 0.0f), 1.0f, glass_mat));

    auto diffuse_mat = std::make_shared<lambertian>(vec3(0.4f, 0.2f, 0.1f));
    objects.push_back(std::make_shared<sphere>(vec3(-4.0f, 1.0f, 0.0f), 1.0f, diffuse_mat));

    auto metal_mat = std::make_shared<metal>(vec3(0.7f, 0.6f, 0.5f), 0.0f);
    objects.push_back(std::make_shared<sphere>(vec3(4.0f, 1.0f, 0.0f), 1.0f, metal_mat));

    return std::make_unique<bvh_node>(objects, 0, objects.size(), r);
}
