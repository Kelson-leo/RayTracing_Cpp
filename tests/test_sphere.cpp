#include <gtest/gtest.h>
#include <memory>
#include "../src/sphere.h"
#include "../src/lambertian.h"

TEST(SphereTest, HitInFront) {
    auto mat = std::make_shared<lambertian>(vec3(0.5f, 0.5f, 0.5f));
    sphere s(vec3(0.0f, 0.0f, -1.0f), 0.5f, mat);
    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    
    hit_record rec;
    bool hit = s.hit(r, 0.0f, 1000.0f, rec);
    
    EXPECT_TRUE(hit);
    EXPECT_NEAR(rec.t, 0.5f, 0.0001f);
    EXPECT_NEAR(rec.p.z(), -0.5f, 0.0001f);
    EXPECT_NEAR(rec.normal.z(), 1.0f, 0.0001f);
}

TEST(SphereTest, Miss) {
    auto mat = std::make_shared<lambertian>(vec3(0.5f, 0.5f, 0.5f));
    sphere s(vec3(0.0f, 0.0f, -1.0f), 0.5f, mat);
    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
    
    hit_record rec;
    bool hit = s.hit(r, 0.0f, 1000.0f, rec);
    
    EXPECT_FALSE(hit);
}

TEST(SphereTest, HitBehindCamera) {
    auto mat = std::make_shared<lambertian>(vec3(0.5f, 0.5f, 0.5f));
    sphere s(vec3(0.0f, 0.0f, 1.0f), 0.5f, mat);
    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    
    hit_record rec;
    bool hit = s.hit(r, 0.0f, 1000.0f, rec);
    
    EXPECT_FALSE(hit);
}