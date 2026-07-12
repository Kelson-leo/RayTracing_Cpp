#include <gtest/gtest.h>
#include "../src/vec3.h"

TEST(Vec3Test, ConstructorAndGetters) {
    vec3 v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
    EXPECT_FLOAT_EQ(v.r(), 1.0f);
    EXPECT_FLOAT_EQ(v.g(), 2.0f);
    EXPECT_FLOAT_EQ(v.b(), 3.0f);
}

TEST(Vec3Test, SubscriptOperator) {
    vec3 v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
    
    v[1] = 5.0f;
    EXPECT_FLOAT_EQ(v[1], 5.0f);
}

TEST(Vec3Test, UnaryMinus) {
    vec3 v(1.0f, -2.0f, 3.0f);
    vec3 neg = -v;
    EXPECT_FLOAT_EQ(neg.x(), -1.0f);
    EXPECT_FLOAT_EQ(neg.y(), 2.0f);
    EXPECT_FLOAT_EQ(neg.z(), -3.0f);
}

TEST(Vec3Test, Addition) {
    vec3 a(1.0f, 2.0f, 3.0f);
    vec3 b(4.0f, 5.0f, 6.0f);
    vec3 c = a + b;
    EXPECT_FLOAT_EQ(c.x(), 5.0f);
    EXPECT_FLOAT_EQ(c.y(), 7.0f);
    EXPECT_FLOAT_EQ(c.z(), 9.0f);
}

TEST(Vec3Test, ScalarMultiplication) {
    vec3 v(1.0f, 2.0f, 3.0f);
    vec3 result = v * 2.0f;
    EXPECT_FLOAT_EQ(result.x(), 2.0f);
    EXPECT_FLOAT_EQ(result.y(), 4.0f);
    EXPECT_FLOAT_EQ(result.z(), 6.0f);
}

TEST(Vec3Test, DotProduct) {
    vec3 a(1.0f, 2.0f, 3.0f);
    vec3 b(4.0f, 5.0f, 6.0f);
    float d = dot(a, b);
    EXPECT_FLOAT_EQ(d, 32.0f); // 1*4 + 2*5 + 3*6 = 32
}

TEST(Vec3Test, CrossProduct) {
    vec3 a(1.0f, 0.0f, 0.0f);
    vec3 b(0.0f, 1.0f, 0.0f);
    vec3 c = cross(a, b);
    EXPECT_FLOAT_EQ(c.x(), 0.0f);
    EXPECT_FLOAT_EQ(c.y(), 0.0f);
    EXPECT_FLOAT_EQ(c.z(), 1.0f);
}

TEST(Vec3Test, Length) {
    vec3 v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
    EXPECT_FLOAT_EQ(v.squared_length(), 25.0f);
}

TEST(Vec3Test, UnitVector) {
    vec3 v(3.0f, 4.0f, 0.0f);
    vec3 u = unit_vector(v);
    EXPECT_FLOAT_EQ(u.length(), 1.0f);
    EXPECT_FLOAT_EQ(u.x(), 0.6f);
    EXPECT_FLOAT_EQ(u.y(), 0.8f);
    EXPECT_FLOAT_EQ(u.z(), 0.0f);
}