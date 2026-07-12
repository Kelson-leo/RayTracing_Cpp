#pragma once

#include "hittable.h"
#include "utils.h"
#include <algorithm>
#include <vector>
#include <memory>

class bvh_node : public hittable {
public:
    bvh_node(std::vector<std::shared_ptr<hittable>>& objects,
             size_t start, size_t end) {
        int axis = static_cast<int>(3.0f * random_float());
        if (axis > 2) axis = 2;

        auto comparator = [axis](const std::shared_ptr<hittable>& a,
                                  const std::shared_ptr<hittable>& b) {
            aabb box_a, box_b;
            if (!a->bounding_box(box_a) || !b->bounding_box(box_b)) return false;
            return box_a.min()[axis] < box_b.min()[axis];
        };

        size_t span = end - start;

        if (span == 1) {
            left = right = objects[start];
        } else if (span == 2) {
            if (comparator(objects[start + 1], objects[start])) {
                left = objects[start + 1];
                right = objects[start];
            } else {
                left = objects[start];
                right = objects[start + 1];
            }
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);
            size_t mid = start + span / 2;
            left = std::make_shared<bvh_node>(objects, start, mid);
            right = std::make_shared<bvh_node>(objects, mid, end);
        }

        aabb box_left, box_right;
        left->bounding_box(box_left);
        right->bounding_box(box_right);
        box = surrounding_box(box_left, box_right);
    }

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override {
        if (!box.hit(r, t_min, t_max)) return false;

        bool hit_left = left->hit(r, t_min, t_max, rec);
        bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

        return hit_left || hit_right;
    }

    bool bounding_box(aabb& b) const override {
        b = box;
        return true;
    }

private:
    std::shared_ptr<hittable> left;
    std::shared_ptr<hittable> right;
    aabb box;
};
