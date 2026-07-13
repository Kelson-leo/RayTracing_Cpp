#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include "camera.h"
#include "scene.h"

vec3 color(const ray& r, const hittable* world, rng& rng, int depth = 0) {
    const int max_depth = 50;
    if (depth >= max_depth) return vec3(0.0f, 0.0f, 0.0f);

    hit_record rec;
    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec)) {
        vec3 attenuation;
        ray scattered;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered, rng)) {
            return attenuation * color(scattered, world, rng, depth + 1);
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
               20.0f,
               float(nx) / float(ny),
               aperture,
               dist_to_focus);

    std::vector<vec3> pixels(nx * ny);

    #pragma omp parallel for schedule(dynamic, 8)
    for (int j = ny - 1; j >= 0; --j) {
        rng local_rng;
        for (int i = 0; i < nx; ++i) {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < ns; ++s) {
                float u = (float(i) + random_float(local_rng)) / float(nx);
                float v = (float(j) + random_float(local_rng)) / float(ny);
                ray r = cam.get_ray(u, v, local_rng);
                col += color(r, world.get(), local_rng);
            }
            col /= float(ns);

            col = vec3(std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]));

            int ir = static_cast<int>(255.99f * col[0]);
            int ig = static_cast<int>(255.99f * col[1]);
            int ib = static_cast<int>(255.99f * col[2]);

            pixels[j * nx + i] = vec3(ir, ig, ib);
        }
    }

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            const vec3& p = pixels[j * nx + i];
            std::cout << static_cast<int>(p[0]) << ' '
                      << static_cast<int>(p[1]) << ' '
                      << static_cast<int>(p[2]) << '\n';
        }
    }

    return 0;
}
