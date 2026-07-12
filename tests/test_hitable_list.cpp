#include <gtest/gtest.h>
#include "../src/hitable_list.h"
#include "../src/sphere.h"

TEST(HitableListTest, HitSingleSphere) {
    sphere s1(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    hittable* list[1] = {&s1};
    hitable_list world(list, 1);

    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    hit_record rec;
    bool hit = world.hit(r, 0.0f, 1000.0f, rec);

    EXPECT_TRUE(hit);
    EXPECT_NEAR(rec.t, 0.5f, 0.0001f);
    EXPECT_NEAR(rec.p.x(), 0.0f, 0.0001f);
    EXPECT_NEAR(rec.p.y(), 0.0f, 0.0001f);
    EXPECT_NEAR(rec.p.z(), -0.5f, 0.0001f);
    EXPECT_NEAR(rec.normal.x(), 0.0f, 0.0001f);
    EXPECT_NEAR(rec.normal.y(), 0.0f, 0.0001f);
    EXPECT_NEAR(rec.normal.z(), 1.0f, 0.0001f);
}

TEST(HitableListTest, HitMultipleSpheres) {
    sphere s1(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    sphere s2(vec3(0.0f, -100.5f, -1.0f), 100.0f);
    hittable* list[2] = {&s1, &s2};
    hitable_list world(list, 2);

    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    hit_record rec;
    bool hit = world.hit(r, 0.0f, 1000.0f, rec);

    EXPECT_TRUE(hit);
    EXPECT_NEAR(rec.t, 0.5f, 0.0001f);
    EXPECT_NEAR(rec.p.z(), -0.5f, 0.0001f);
}