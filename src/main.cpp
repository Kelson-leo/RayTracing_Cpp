#include <iostream>
#include <limits>
#include <memory>
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "utils.h"

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

    auto mat_ground = std::make_shared<lambertian>(vec3(0.8f, 0.8f, 0.0f));   
    auto mat_center = std::make_shared<lambertian>(vec3(0.1f, 0.2f, 0.5f));    
    auto mat_left   = std::make_shared<dielectric>(1.5f);                      
    auto mat_right  = std::make_shared<metal>(vec3(0.8f, 0.6f, 0.2f), 0.0f);   

    sphere s1(vec3(0.0f, 0.0f, -1.0f), 0.5f, mat_center);
    sphere s2(vec3(0.0f, -100.5f, -1.0f), 100.0f, mat_ground);
    sphere s3(vec3(1.0f, 0.0f, -1.0f), 0.5f, mat_right);
    sphere s4(vec3(-1.0f, 0.0f, -1.0f), 0.5f, mat_left);
    
    sphere s5(vec3(-1.0f, 0.0f, -1.0f), -0.45f, mat_left);

    hittable* list[5] = {&s1, &s2, &s3, &s4, &s5};
    hitable_list world(list, 5);

    camera cam;

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < ns; ++s) {
                float u = (float(i) + random_float()) / float(nx);
                float v = (float(j) + random_float()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, &world);
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