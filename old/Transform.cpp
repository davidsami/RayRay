// David Sami 2015

#include <iostream>
#include <string.h>
#include "Transform.h"

Transform::Transform(Matrix4& aMatrix){
    mat = aMatrix;
    inverse = mat.Inverse();
}

Transform::Transform(){
    mat = Matrix4::Identity;
    inverse = Matrix4::Identity;
}

Point Transform::operator()(const Point &aP){
    double x = mat.m[0][0]*aP.x + mat.m[0][1]*aP.y + mat.m[0][2]*aP.z + mat.m[0][3];
    double y = mat.m[1][0]*aP.x + mat.m[1][1]*aP.y + mat.m[1][2]*aP.z + mat.m[1][3];
    double z = mat.m[2][0]*aP.x + mat.m[2][1]*aP.y + mat.m[2][2]*aP.z + mat.m[2][3];
    double w = mat.m[3][0]*aP.x + mat.m[3][1]*aP.y + mat.m[3][2]*aP.z + mat.m[3][3];

    return Point(x/w, y/w, z/w);
}

Vector Transform::operator()(const Vector &aV){
    double x = mat.m[0][0]*aV.x + mat.m[0][1]*aV.y + mat.m[0][2]*aV.z;
    double y = mat.m[1][0]*aV.x + mat.m[1][1]*aV.y + mat.m[1][2]*aV.z;
    double z = mat.m[2][0]*aV.x + mat.m[2][1]*aV.y + mat.m[2][2]*aV.z;

    return Vector(x, y, z);
}

Transform Transform :: TranslationTransform(const Vector &d){
    Matrix4 matrix = Matrix4::Identity;
    matrix.m[0][3] = d.x;
    matrix.m[1][3] = d.y;
    matrix.m[2][3] = d.z;
    return Transform(matrix);
}

Transform Transform :: ScaleTransform(const Vector &d){
    Matrix4 matrix = Matrix4::Identity;
    matrix.m[0][0] = d.x;
    matrix.m[1][1] = d.y;
    matrix.m[2][2] = d.z;
    return Transform(matrix);
}


Transform Transform :: RotateXTransform(const double theta){
    double c = cos(theta);
    double s = sin(theta);
    Matrix4 matrix;
    matrix.m[1][1] = c;
    matrix.m[2][2] = c;
    matrix.m[2][1] = s;
    matrix.m[1][2] = -s;
    return Transform(matrix);
}

Transform Transform :: RotateYTransform(const double theta){
    double c = cos(theta);
    double s = sin(theta);
    Matrix4 matrix;
    matrix.m[0][0] = c;
    matrix.m[2][2] = c;
    matrix.m[2][0] = -s;
    matrix.m[0][2] = s;
    return Transform(matrix);
}

Transform Transform :: RotateZTransform(const double theta){
    double c = cos(theta);
    double s = sin(theta);
    Matrix4 matrix;
    matrix.m[0][0] = c;
    matrix.m[1][1] = c;
    matrix.m[1][0] = s;
    matrix.m[0][1] = -s;
    return Transform(matrix);
}

Transform Transform :: RotateTransform(const Vector &axis, const double theta){
    Matrix4 matrix;
    return Transform(matrix);
}


