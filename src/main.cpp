#include <iostream>
#include <limits>
#include <cmath>
#include <memory>
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "utils.h"
#include "scene.h"

vec3 color(const ray& r, const hittable* world, int depth = 0) {
    const int max_depth = 50;
    if (depth >= max_depth) return vec3(0.0f, 0.0f, 0.0f);

    hit_record rec;
    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec)) {
        vec3 attenuation;
        ray scattered;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        return vec3(0.0f, 0.0f, 0.0f);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        vec3 white(1.0f, 1.0f, 1.0f);
        vec3 blue(0.5f, 0.7f, 1.0f);
        return (1.0f - t) * white + t * blue;
    }
}

int main() {
    constexpr int nx = 200;     
    constexpr int ny = 100;
    constexpr int ns = 100;     

    std::cout << "P3\n" << nx << ' ' << ny << "\n255\n";

    auto world = random_scene();

    vec3 lookfrom(13.0f, 2.0f, 3.0f);
    vec3 lookat(0.0f, 0.0f, 0.0f);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperture = 0.1f;   

    camera cam(lookfrom, lookat, vec3(0.0f, 1.0f, 0.0f),
               20.0f,                     // vfov
               float(nx) / float(ny),
               aperture,
               dist_to_focus);

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < ns; ++s) {
                float u = (float(i) + random_float()) / float(nx);
                float v = (float(j) + random_float()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world.get());
            }
            col /= float(ns);

            col = vec3(std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]));

            int ir = static_cast<int>(255.99f * col[0]);
            int ig = static_cast<int>(255.99f * col[1]);
            int ib = static_cast<int>(255.99f * col[2]);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}