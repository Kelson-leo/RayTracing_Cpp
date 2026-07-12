#include <gtest/gtest.h>
#include "../src/sphere.h"

TEST(SphereTest, HitInFront) {
    sphere s(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    
    hit_record rec;
    bool hit = s.hit(r, 0.0f, 1000.0f, rec);
    
    EXPECT_TRUE(hit);
    EXPECT_NEAR(rec.t, 0.5f, 0.0001f); 
}

TEST(SphereTest, Miss) {
    sphere s(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
    
    hit_record rec;
    bool hit = s.hit(r, 0.0f, 1000.0f, rec);
    
    EXPECT_FALSE(hit);
}

TEST(SphereTest, HitBehindCamera) {
    sphere s(vec3(0.0f, 0.0f, 1.0f), 0.5f); 
    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    
    hit_record rec;
    bool hit = s.hit(r, 0.0f, 1000.0f, rec);
    
    EXPECT_FALSE(hit);
}