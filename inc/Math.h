// David Sami 2015

#ifndef RAYRAY_MATH_H
#define RAYRAY_MATH_H

#include <memory>
#include <ostream>
#include "Eigen/Dense"
#include "Eigen/Geometry"

namespace Math {
    // Uses quadratic formula to solve for roots. Returns true if roots available
    bool SolveQuadratic(double a, double b, double c, double* r0, double* r1);

    // Wrapper classes for Vector, Point and Normal
    // Mostly exist to correctly handle homogenous coordinates for transformation
    struct Vector {
        Eigen::Vector3d d;
        Vector (){
            d << 0,0,0;
        }
        Vector (double x, double y, double z){
            d << x,y,z;
        }
        Vector (Eigen::Vector3d& vin){
            d = vin;
        }
        double operator()(int i){
            return d(i);
        }
        Vector operator+(const Vector& rhs) const{
            Eigen::Vector3d out;
            out = d + rhs.d;
            return Vector(out);
        }
        Vector operator-(const Vector& rhs) const{
            Eigen::Vector3d out;
            out = d - rhs.d;
            return Vector(out);
        }
        double Dot(const Vector& rhs) const{
            return d.dot(rhs.d);
        }
        Vector Cross(const Vector& rhs) const{
            Eigen::Vector3d out;
            out = d.cross(rhs.d);
            return Vector(out);
        }
        Vector Normal(){
            Eigen::Vector3d out;
            out = d.normalized();
            return Vector(out);
        }
    };

    struct Point : public Vector {
        Point(): Vector(){}
        Point(double x, double y, double z):Vector(x,y,z){}
        Point(Eigen::Vector3d& vin):Vector(vin){}
    };

    struct Normal : public Vector {
        Normal(): Vector(){}
        Normal(double x, double y, double z):Vector(x,y,z){}
        Normal(Eigen::Vector3d& vin):Vector(vin){}
    };

    struct Ray{
        Ray(Point aO, Vector aD):o(aO), d(aD){}
        Ray():o(Point(0,0,0)), d(Vector(0,0,0)){}
        Point GetPoint(double t){
            Eigen::Vector3d p = o.d + d.d*t;
            return Point(p);
        }
        Point o;
        Vector d;
    };


    struct Transform {
        Eigen::Projective3d t;
        Eigen::Projective3d tinv;

        Transform() = delete;
        Transform(Eigen::Projective3d& tin){
            t = tin;
            tinv = tin.inverse();
        }

        // Transform operations
        Vector operator()(const Vector &v) const{
            Vector o;
            o.d = t.linear() * v.d;
            return o;
        }

        Point operator()(const Point &p) const{
            Point o;
            o.d = (t * p.d.colwise().homogeneous()).colwise().hnormalized();
            return o;
        }

        Normal operator()(const Normal &n) const{
            Normal o;
            o.d = tinv.linear().transpose() * n.d;
            return o;
        }

        Ray operator()(const Ray &r) const{
            Ray o;
            o.o = (*this)(r.o);
            o.d = (*this)(r.d);
            return o;
        }

        // Inverse transform
        Vector reverse(const Vector &v) const{
            Vector o;
            o.d = tinv.linear() * v.d;
            return o;
        }

        Point reverse(const Point &p) const{
            Point o;
            o.d = (tinv * p.d.colwise().homogeneous()).colwise().hnormalized();
            return o;
        }

        Normal reverse(const Normal &n) const{
            Normal o;
            o.d = t.linear().transpose() * n.d;
            return o;
        }

        Ray reverse(const Ray &r) const{
            Ray o;
            o.o = this->reverse(r.o);
            o.d = this->reverse(r.d);
            return o;
        }
    };
};

std::ostream &operator<<(std::ostream &os, const Math::Vector &m);
std::ostream &operator<<(std::ostream &os, const Math::Ray &m);

#endif
