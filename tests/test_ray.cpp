#include <gtest/gtest.h>
#include "../src/ray.h"

TEST(RayTest, ConstructorAndGetters) {
    vec3 origin(1.0f, 2.0f, 3.0f);
    vec3 direction(4.0f, 5.0f, 6.0f);
    ray r(origin, direction);
    
    EXPECT_EQ(r.origin().x(), 1.0f);
    EXPECT_EQ(r.origin().y(), 2.0f);
    EXPECT_EQ(r.origin().z(), 3.0f);
    
    EXPECT_EQ(r.direction().x(), 4.0f);
    EXPECT_EQ(r.direction().y(), 5.0f);
    EXPECT_EQ(r.direction().z(), 6.0f);
}

TEST(RayTest, PointAtParameter) {
    vec3 origin(0.0f, 0.0f, 0.0f);
    vec3 direction(1.0f, 2.0f, 3.0f);
    ray r(origin, direction);
    
    vec3 p1 = r.at(0.0f);
    EXPECT_EQ(p1.x(), 0.0f);
    EXPECT_EQ(p1.y(), 0.0f);
    EXPECT_EQ(p1.z(), 0.0f);
    
    vec3 p2 = r.at(2.0f);
    EXPECT_EQ(p2.x(), 2.0f);
    EXPECT_EQ(p2.y(), 4.0f);
    EXPECT_EQ(p2.z(), 6.0f);
}