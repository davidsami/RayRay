// David Sami 2015

#include <gtest/gtest.h>
#include "Transform.h"
#include "Vector.h"

TEST(Transform, Identity){
    Vector a(6,2,7);
    Transform id;

    Vector b = id(a);
    ASSERT_DOUBLE_EQ(a.x, b.x);
    ASSERT_DOUBLE_EQ(a.y, b.y);
    ASSERT_DOUBLE_EQ(a.z, b.z);

    Point c(6,2,7);

    Point d = id(c);
    ASSERT_DOUBLE_EQ(c.x, d.x);
    ASSERT_DOUBLE_EQ(c.y, d.y);
    ASSERT_DOUBLE_EQ(c.z, d.z);
}

TEST(Transform, Translate){
    Vector vec(2,5,-8);
    Transform translate = Transform::TranslationTransform(vec);

    // Vector
    Vector a(1,-2,3);

    Vector d = translate(a);

    ASSERT_DOUBLE_EQ(a.x, d.x);
    ASSERT_DOUBLE_EQ(a.y, d.y);
    ASSERT_DOUBLE_EQ(a.z, d.z);

    // Point
    Point e(3,8,-1);

    Point f = translate(e);

    ASSERT_DOUBLE_EQ(5, f.x);
    ASSERT_DOUBLE_EQ(13, f.y);
    ASSERT_DOUBLE_EQ(-9, f.z);
}

TEST(Transform, Scale){
    Vector vec(2,5,-8);
    Transform scale = Transform::ScaleTransform(vec);

    // Vector
    Vector a(1,-2,3);

    Vector b = scale(a);

    ASSERT_DOUBLE_EQ(2, b.x);
    ASSERT_DOUBLE_EQ(-10, b.y);
    ASSERT_DOUBLE_EQ(-24, b.z);

    // Point
    Point c(1,-2,3);

    Point d = scale(c);

    ASSERT_DOUBLE_EQ(2, d.x);
    ASSERT_DOUBLE_EQ(-10, d.y);
    ASSERT_DOUBLE_EQ(-24, d.z);
}

TEST(Transform, Rotate){
}
