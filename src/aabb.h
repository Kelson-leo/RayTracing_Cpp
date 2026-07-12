#pragma once

#include "ray.h"
#include <algorithm>

class aabb {
public:
    aabb() = default;
    aabb(const vec3& min, const vec3& max) : minimum(min), maximum(max) {}

    vec3 min() const { return minimum; }
    vec3 max() const { return maximum; }

    bool hit(const ray& r, float tmin, float tmax) const {
        for (int a = 0; a < 3; ++a) {
            float invD = 1.0f / r.direction()[a];
            float t0 = (minimum[a] - r.origin()[a]) * invD;
            float t1 = (maximum[a] - r.origin()[a]) * invD;
            if (invD < 0.0f) std::swap(t0, t1);
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;
            if (tmax <= tmin) return false;
        }
        return true;
    }

private:
    vec3 minimum;
    vec3 maximum;
};

inline aabb surrounding_box(const aabb& box0, const aabb& box1) {
    vec3 small(
        std::fmin(box0.min().x(), box1.min().x()),
        std::fmin(box0.min().y(), box1.min().y()),
        std::fmin(box0.min().z(), box1.min().z()));
    vec3 big(
        std::fmax(box0.max().x(), box1.max().x()),
        std::fmax(box0.max().y(), box1.max().y()),
        std::fmax(box0.max().z(), box1.max().z()));
    return aabb(small, big);
}
