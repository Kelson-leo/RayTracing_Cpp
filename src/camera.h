#pragma once
#include "ray.h"
#include <cmath>

class camera {
public:
    camera(const vec3& lookfrom, const vec3& lookat, const vec3& vup,
           float vfov, float aspect) {
        float theta = vfov * M_PI / 180.0f;
        float half_height = std::tan(theta / 2.0f);
        float half_width = aspect * half_height;

        w = unit_vector(lookfrom - lookat);   
        u = unit_vector(cross(vup, w));       
        v = cross(w, u);                      

        origin = lookfrom;

        lower_left_corner = origin - half_width * u - half_height * v - w;
        horizontal = 2.0f * half_width * u;
        vertical = 2.0f * half_height * v;
    }

    ray get_ray(float s, float t) const {
        return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
    }

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w; 
};