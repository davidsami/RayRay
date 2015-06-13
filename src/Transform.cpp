// David Sami 2015

#include <iostream>
#include <string.h>
#include "Transform.h"

Transform::Transform(Matrix4& aMatrix){
    mat = aMatrix;
    inverse = mat.Inverse();
}

Transform Transform :: TranslationTransform(Vector &d){
    Matrix4 matrix;
    matrix.m[0][0] = d.x;
    matrix.m[1][1] = d.y;
    matrix.m[2][2] = d.z;
    return Transform(matrix);
}

Transform Transform :: ScaleTransform(Vector &d){
    Matrix4 matrix;
    matrix.m[0][3] = d.x;
    matrix.m[1][3] = d.y;
    matrix.m[2][3] = d.z;
    return Transform(matrix);
}


Transform Transform :: RotateXTransform(float theta){
    double c = cos(theta);
    double s = sin(theta);
    Matrix4 matrix;
    matrix.m[1][1] = c;
    matrix.m[2][2] = c;
    matrix.m[2][1] = s;
    matrix.m[1][2] = -s;
    return Transform(matrix);
}

Transform Transform :: RotateYTransform(float theta){
    double c = cos(theta);
    double s = sin(theta);
    Matrix4 matrix;
    matrix.m[0][0] = c;
    matrix.m[2][2] = c;
    matrix.m[2][0] = -s;
    matrix.m[0][2] = s;
    return Transform(matrix);
}

Transform Transform :: RotateZTransform(float theta){
    double c = cos(theta);
    double s = sin(theta);
    Matrix4 matrix;
    matrix.m[0][0] = c;
    matrix.m[1][1] = c;
    matrix.m[1][0] = s;
    matrix.m[0][1] = -s;
    return Transform(matrix);
}

Transform Transform :: RotateTransform(Vector &axis, float theta){
    Matrix4 matrix;
    return Transform(matrix);
}


