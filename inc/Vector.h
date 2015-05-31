// David Sami 2015

#include <math.h>
#include <string.h>

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    Vector() { x=0; y=0; z=0; }
    Vector(double aX, double aY, double aZ) { x=aX; y=aY; z=aZ; }
    Vector(const Vector& aVector) { x=aVector.x; y=aVector.y; z=aVector.z; }

    Vector& operator=(const Vector& aVector) { x=aVector.x; y=aVector.y; z=aVector.z; return *this; }

    Vector operator-() { return Vector(-x, -y, -z); }

    Vector operator+(const Vector& aVector) const { return Vector(x+aVector.x, y+aVector.y, z+aVector.z); }
    Vector operator-(const Vector& aVector) const { return Vector(x-aVector.x, y-aVector.y, z-aVector.z); }
    Vector operator*(const Vector& aVector) const { return Vector(x*aVector.x, y*aVector.y, z*aVector.z); }
    Vector operator/(const Vector& aVector) const { return Vector(x/aVector.x, y/aVector.y, z/aVector.z); }

    Vector& operator+=(const Vector& aVector) { x+=aVector.x; y+=aVector.y; z+=aVector.z; return *this; }
    Vector& operator-=(const Vector& aVector) { x-=aVector.x; y-=aVector.y; z-=aVector.z; return *this; }
    Vector& operator*=(const Vector& aVector) { x*=aVector.x; y*=aVector.y; z*=aVector.z; return *this; }
    Vector& operator/=(const Vector& aVector) { x/=aVector.x; y/=aVector.y; z/=aVector.z; return *this; }

    Vector operator*(const double aF) { return Vector(x*aF, y*aF, z*aF); }
    Vector operator/(const double aF) { return Vector(x/aF, y/aF, z/aF); }
    Vector& operator*=(const double aF) { x*=aF; y*=aF; z*=aF; return *this; }
    Vector& operator/=(const double aF) { x/=aF; y/=aF; z/=aF; return *this; }

    bool operator==(const Vector& aVector) { return (x==aVector.x && y==aVector.y && z==aVector.z); }
    bool operator!=(const Vector& aVector) { return !(*this==aVector); }

    double LengthSquared() { return x*x + y*y + z*z; }
    double Length() { return sqrtf(LengthSquared()); }

    Vector Normal() { return *this / Length(); }

    static double DistanceSquared(const Vector& a, const Vector& b) { return (a-b).LengthSquared(); }
    static double Distance(const Vector& a, const Vector& b) { return (a-b).Length(); }

    static double Dot(const Vector& a, const Vector& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
    static Vector Cross(const Vector& a, const Vector& b) { 
        return Vector(a.y*b.z - a.z*b.y,
                      a.z*b.x - a.x*b.z,
                      a.x*b.y - a.y*b.x);
    }

    double x, y, z;
};

class Ray{
public:
    Vector o, d;
};

#endif
