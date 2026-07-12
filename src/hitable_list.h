#pragma once
#include <vector>
#include <memory>
#include "hittable.h"

class hitable_list : public hittable {
public:
    hitable_list() = default;

    hitable_list(std::vector<std::shared_ptr<hittable>> objects)
        : objects(std::move(objects)) {}

    hitable_list(hittable** list, int n) {
        for (int i = 0; i < n; ++i) {
            objects.push_back(std::shared_ptr<hittable>(list[i], [](hittable*){}));
        }
    }

    void add(const std::shared_ptr<hittable>& obj) {
        objects.push_back(obj);
    }

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        float closest_so_far = t_max;

        for (const auto& obj : objects) {
            if (obj->hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }

    bool bounding_box(aabb& box) const override {
        if (objects.empty()) return false;

        aabb temp_box;
        bool first = true;

        for (const auto& obj : objects) {
            if (!obj->bounding_box(temp_box)) return false;
            box = first ? temp_box : surrounding_box(box, temp_box);
            first = false;
        }
        return true;
    }

private:
    std::vector<std::shared_ptr<hittable>> objects;
};