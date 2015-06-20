// David Sami 2015

#include "Vector.h"
#include "Matrix.h"
#include <gtest/gtest.h>
#include <cstdlib>
#include <time.h>

// Arbitrary tests

TEST(Vector, Operations){
    Vector a(2.152,2.7893,3.1257);
    Vector b(9.371,6.1528,6.6654);

    Vector c = a + b;
    ASSERT_DOUBLE_EQ(c.x, 11.523);
    ASSERT_DOUBLE_EQ(c.y, 8.9421);
    ASSERT_DOUBLE_EQ(c.z, 9.7911);

    Vector d = a - b;
    ASSERT_DOUBLE_EQ(d.x, -7.219);
    ASSERT_DOUBLE_EQ(d.y, -3.3635);
    ASSERT_DOUBLE_EQ(d.z, -3.5397);

    Vector e = a * b;
    ASSERT_DOUBLE_EQ(e.x, 20.166392);
    ASSERT_DOUBLE_EQ(e.y, 17.16200504);
    ASSERT_DOUBLE_EQ(e.z, 20.83404078);

    Vector f = a / b;
    ASSERT_NEAR(f.x, 0.22964464838, 0.000000001);
    ASSERT_NEAR(f.y, 0.453338317, 0.000000001);
    ASSERT_NEAR(f.z, 0.468944099, 0.000000001);
}

TEST(Vector, Length){
    Vector a(3,4,0);
    ASSERT_DOUBLE_EQ(a.Length(), 5);

    Vector b = a.Normal();
    ASSERT_DOUBLE_EQ(b.x, (double)3/5);
    ASSERT_DOUBLE_EQ(b.y, (double)4/5);
    ASSERT_DOUBLE_EQ(b.z, 0);

    ASSERT_DOUBLE_EQ(Vector::Distance(a,a), 0);
    Vector c = a * 2;
    ASSERT_DOUBLE_EQ(Vector::Distance(a,c), 5);
}

TEST(Vector, DotCross){
    Vector a(2.152,2.7893,3.1257);
    Vector b(9.371,6.1528,6.6654);
    ASSERT_DOUBLE_EQ(Vector::Dot(a,b), 20.166392 + 17.16200504 + 20.83404078);

    Vector c = Vector::Cross(a,b);
    // Lots of double operations build up error
    ASSERT_NEAR(c.x, -0.640007, 0.00001);
    ASSERT_NEAR(c.y, 14.947, 0.00001);
    ASSERT_NEAR(c.z, -12.8977, 0.00001);
}

TEST(Matrix, Inverse){
    double a[4][4] = {{-5,75,-31,-14}, {5,-9,-79,-49}, {49,88,-54,100}, {43,-61,-55,-96}};

    // Calculated using determinant method
    double aInv[4][4] = {{58459./23424632, -210597./11712316, 45167./5856158, 394655./23424632}, {639619./46849264, -163661./23424632, 4429./11712316, 92247./46849264}, {239101./46849264, -390931./23424632, -28137./11712316, 246969./46849264}, {-2790./266189, 1583./266189, 1222./266189, -1901./266189}};

    Matrix4 c(a);
    Matrix4 d = c.Inverse();

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            ASSERT_NEAR(d.m[i][j], aInv[i][j], 0.000000001);
        }
    }
}

TEST(Matrix, Transpose){
    double a[4][4] = {{99,40,-26,-28}, {-53,22,-45,-43}, {-93,-58,78,-15}, {4,8,-71,-90}};
    double aTrans[4][4] = {{99, -53, -93, 4}, {40, 22, -58, 8}, {-26, -45, 78, -71}, {-28, -43, -15, -90}};

    Matrix4 b(a);
    Matrix4 c = b.Transpose();

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            ASSERT_DOUBLE_EQ(c.m[i][j], aTrans[i][j]);
        }
    }
}

TEST(Matrix, ZeroInverse){
    Matrix4 id = Matrix4::Identity;

    double a[4][4] = {{0,1,2,3}, {4,5,6,7}, {8,8,7,6}, {5,4,3,1}};
    Matrix4 mat(a);
    Matrix4 inverse = mat.Inverse();

    Matrix4 newId = mat * inverse;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            ASSERT_NEAR(newId.m[i][j], id.m[i][j], 0.000000001);
        }
    }
}

static Matrix4 getRandomMatrix(){
    Matrix4 m;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            bool neg = rand() % 2;
            m.m[i][j] = (neg?1:-1) * (rand() % 50); }
    }

    return m;
}

TEST(Matrix, MassInverse){
    srand(time(NULL));
    Matrix4 id = Matrix4::Identity;
    for(int k = 0; k < 10000000; k++){
        //std::cout << "Mass Inverse Test Number: " << k << std::endl;
        Matrix4 m = getRandomMatrix();
        while (m.Determinant() == 0){
            m = getRandomMatrix();
        }
        Matrix4 inverse = m.Inverse();
        // Test [A] * [A]-1 = [I]
        Matrix4 newId = m * inverse;

        //m.Debug();
        //inverse.Debug();
        //newId.Debug();

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                ASSERT_NEAR(newId.m[i][j], id.m[i][j], 1e-7);
            }
        }
    }
}
