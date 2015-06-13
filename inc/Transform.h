// David Sami 2015

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"
#include "Matrix.h"

class Transform{
public:
    Transform(Matrix4& aMat);
    Transform() = delete;

    static Transform TranslationTransform(Vector &d);
    static Transform ScaleTransform(Vector &d);
    static Transform RotateXTransform(float theta);
    static Transform RotateYTransform(float theta);
    static Transform RotateZTransform(float theta);
    static Transform RotateTransform(Vector &axis, float theta);

protected:
    Matrix4 mat;
    Matrix4 inverse;
};

#endif

