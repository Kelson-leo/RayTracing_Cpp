#include <gtest/gtest.h>
#include <memory>
#include "../src/hitable_list.h"
#include "../src/sphere.h"
#include "../src/lambertian.h"

TEST(HitableListTest, HitSingleSphere) {
    auto mat = std::make_shared<lambertian>(vec3(0.5f, 0.5f, 0.5f));
    auto s1 = std::make_shared<sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f, mat);
    hitable_list world;
    world.add(s1);

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
    auto mat1 = std::make_shared<lambertian>(vec3(0.8f, 0.3f, 0.3f));
    auto mat2 = std::make_shared<lambertian>(vec3(0.5f, 0.5f, 0.5f));
    auto s1 = std::make_shared<sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f, mat1);
    auto s2 = std::make_shared<sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f, mat2);
    hitable_list world;
    world.add(s1);
    world.add(s2);

    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    hit_record rec;
    bool hit = world.hit(r, 0.0f, 1000.0f, rec);

    EXPECT_TRUE(hit);
    EXPECT_NEAR(rec.t, 0.5f, 0.0001f);
    EXPECT_NEAR(rec.p.z(), -0.5f, 0.0001f);
}