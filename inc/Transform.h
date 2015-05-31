// David Sami 2015

#ifndef TRANSFORM_H
#define TRANSFORM_H

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

class Transform{
public:
    Transform() {}

    static Transform TranslationTransform(Vector &d);
    static Transform ScaleTransform(Vector &d);
    static Transform RotateXTransform(float theta);
    static Transform RotateYTransform(float theta);
    static Transform RotateZTransform(float theta);
    static Transform RotateTransform(Vector &axis, float theta);

protected:
    Matrix4 mat;
};

#endif

