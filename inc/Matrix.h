// David Sami 2015

#ifndef MATRIX_H
#define MATRIX_H

class Matrix4{
public:
    Matrix4();
    Matrix4(double aM[4][4]);
    bool operator==(const Matrix4 &m2) const;
    bool operator!=(const Matrix4 &m2) const;
    Matrix4 operator*(const Matrix4 &aM) const;
    Matrix4 Transpose();
    Matrix4 Inverse();

    double m[4][4];
};

#endif
