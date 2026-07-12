#include <iostream>
#include "ray.h"

inline constexpr vec3 lerp(const vec3& a, const vec3& b, float t) {
    return (1.0f - t) * a + t * b;
}

vec3 color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    
    vec3 white(1.0f, 1.0f, 1.0f);
    vec3 blue(0.5f, 0.7f, 1.0f);
    return lerp(white, blue, t);
}

int main() {
    constexpr int nx = 200;
    constexpr int ny = 100;

    std::cout << "P3\n" << nx << ' ' << ny << "\n255\n";

    constexpr vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    constexpr vec3 horizontal(4.0f, 0.0f, 0.0f);
    constexpr vec3 vertical(0.0f, 2.0f, 0.0f);
    constexpr vec3 origin(0.0f, 0.0f, 0.0f);

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            vec3 direction = lower_left_corner + u * horizontal + v * vertical - origin;
            ray r(origin, direction);

            vec3 col = color(r);

            int ir = static_cast<int>(255.99f * col[0]);
            int ig = static_cast<int>(255.99f * col[1]);
            int ib = static_cast<int>(255.99f * col[2]);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}