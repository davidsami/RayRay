// David Sami 2015

#ifndef RAYRAY_MATH_H
#define RAYRAY_MATH_H
#include "Eigen/Dense"
#include "Eigen/Geometry"

namespace Math {
    // Uses quadratic formula to solve for roots. Returns true if roots available
    bool SolveQuadratic(double a, double b, double c, double* r0, double* r1);

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
    };

    struct Point : Vector {
        Point(): Vector(){}
        Point(double x, double y, double z):Vector(x,y,z){}
        Point(Eigen::Vector3d& vin):Vector(vin){}
    };

    struct Normal : Vector {
        Normal(): Vector(){}
        Normal(double x, double y, double z):Vector(x,y,z){}
        Normal(Eigen::Vector3d& vin):Vector(vin){}
    };

    struct Ray{
        Point o;
        Vector d;
    };

    struct Transform {
        Eigen::Affine3d t;
        Eigen::Affine3d tinv;

        Transform() = delete;
        Transform(Eigen::Affine3d& tin){
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
            o.d = t * p.d;
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
            o.d = tinv * p.d;
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

#endif
