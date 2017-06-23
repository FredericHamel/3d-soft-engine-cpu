#include <gtest/gtest.h>
#include "math/VectF4.h"

#define EXPECT_VECTOR_VALUES_EQ(v, X, Y, Z, W)\
  EXPECT_FLOAT_EQ(v.x, X);\
  EXPECT_FLOAT_EQ(v.y, Y);\
  EXPECT_FLOAT_EQ(v.z, Z);\
  EXPECT_FLOAT_EQ(v.w, W)

class VectF4_Test : public ::testing::Test
{
  protected:
    VectF4 e1, e2, e3, e4;
    VectF4 v1;
    VectF4 v2;
    VectF4 v3;
  public:
    VectF4_Test()
      : e1(1.0f, 0.0f, 0.0f, 0.0f),
        e2(0.0f, 1.0f, 0.0f, 0.0f),
        e3(0.0f, 0.0f, 1.0f, 0.0f),
        e4(0.0f, 0.0f, 0.0f, 1.0f),
        v2(0.25f, 0.35f, 0.45f, 0.50f),
        v3(v2) {
    }

    ~VectF4_Test() {
    }
};

TEST_F(VectF4_Test, default_constructor) {
  EXPECT_VECTOR_VALUES_EQ(v1, 0.0f, 0.0f, 0.0f, 0.0f);
}

TEST_F(VectF4_Test, constructor) {
  EXPECT_VECTOR_VALUES_EQ(v2, 0.25f, 0.35f, 0.45f, 0.50f);
}

TEST_F(VectF4_Test, copy_constructor) {
  EXPECT_VECTOR_VALUES_EQ(v3, 0.25f, 0.35f, 0.45f, 0.50f);
}


TEST_F(VectF4_Test, length) {
  EXPECT_FLOAT_EQ(e1.length(), 1.0f);
  EXPECT_FLOAT_EQ(e2.length(), 1.0f);
  EXPECT_FLOAT_EQ(e3.length(), 1.0f);
  EXPECT_FLOAT_EQ(e4.length(), 1.0f);
  EXPECT_FLOAT_EQ(v2.length(), 0.79843597f);
}

TEST_F(VectF4_Test, length3) {
  EXPECT_FLOAT_EQ(e1.length3(), 1.0f);
  EXPECT_FLOAT_EQ(e2.length3(), 1.0f);
  EXPECT_FLOAT_EQ(e3.length3(), 1.0f);
  EXPECT_FLOAT_EQ(e4.length3(), 0.0f);
  EXPECT_FLOAT_EQ(v2.length3(), 0.6224950f);
}

TEST_F(VectF4_Test, normalize) {
  EXPECT_VECTOR_VALUES_EQ(v2.normalize(), 0.31311215f, 0.438357f, 0.56360186f, 0.62622429f);
}

TEST_F(VectF4_Test, normalize3) {
  EXPECT_VECTOR_VALUES_EQ(v2.normalize3(), 0.40160966f,  0.56225353f,  0.7228974f, 0.0f);
}

TEST_F(VectF4_Test, equals) {
  EXPECT_EQ(v1, v1);
  EXPECT_EQ(v2, v2);
  EXPECT_EQ(v2, v3);
  EXPECT_EQ(v3, v3);
}

TEST_F(VectF4_Test, not_equal) {
  EXPECT_NE(e1, e2);
  EXPECT_NE(e1, e3);
  EXPECT_NE(e1, e4);
  EXPECT_NE(e2, e3);
  EXPECT_NE(e3, e4);
  EXPECT_NE(v1, v2);
  EXPECT_NE(v1, v2);
  EXPECT_NE(v2, e1);
  EXPECT_NE(v2, e2);
  EXPECT_NE(v2, e3);
  EXPECT_NE(v2, e4);
}

TEST_F(VectF4_Test, dot_product) {
  EXPECT_FLOAT_EQ(VectF4::dotProduct(v2,v2), 0.6375f);
}

TEST_F(VectF4_Test, dot_product3) {
  EXPECT_FLOAT_EQ(VectF4::dotProduct3(v2,v2), 0.3875f);
}

TEST_F(VectF4_Test, cross_product) {
  EXPECT_EQ(e1.crossProduct3(e2), e3);
  EXPECT_EQ(e2.crossProduct3(e3), e1);
  EXPECT_EQ(e3.crossProduct3(e1), e2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

