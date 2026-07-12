#include <iostream>
#include <limits>
#include <random>
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0.0f, 1.0f);

vec3 color(const ray& r, const hittable* world) {
    hit_record rec;
    if (world->hit(r, 0.0f, std::numeric_limits<float>::max(), rec)) {
        return 0.5f * vec3(rec.normal.x() + 1.0f,
                           rec.normal.y() + 1.0f,
                           rec.normal.z() + 1.0f);
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

    sphere s1(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    sphere s2(vec3(0.0f, -100.5f, -1.0f), 100.0f);
    hittable* list[2] = {&s1, &s2};
    hitable_list world(list, 2);

    camera cam;

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < ns; ++s) {
                float u = (float(i) + dis(gen)) / float(nx);
                float v = (float(j) + dis(gen)) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, &world);
            }
            col /= float(ns);

            int ir = static_cast<int>(255.99f * col[0]);
            int ig = static_cast<int>(255.99f * col[1]);
            int ib = static_cast<int>(255.99f * col[2]);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}