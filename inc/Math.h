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
        double operator()(int i) const{
            return d(i);
        }
        double& operator[](int i){
            return d(i);
        }
        Vector operator+(const Vector& rhs) const{
            Eigen::Vector3d out;
            out = d + rhs.d;
            return Vector(out);
        }
        Vector operator*(const double rhs) const{
            Eigen::Vector3d out;
            out = d * rhs;
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
        Vector Inverse(){
            Eigen::Vector3d out;
            out << 1. / d(0),
                   1. / d(1),
                   1. / d(2);

            return Vector(out);
        }
    };

    struct Point : public Vector {
        Point(): Vector(){}
        Point(const Vector& vec){
            d = vec.d;
        }
        Point(double x, double y, double z):Vector(x,y,z){}
        Point(Eigen::Vector3d& vin):Vector(vin){}
    };

    struct Normal : public Vector {
        Normal(): Vector(){}
        Normal(const Vector& vec){
            d = vec.d.normalized();
        }
        Normal(double x, double y, double z):Vector(x,y,z){}
        Normal(Eigen::Vector3d& vin):Vector(vin){}
    };

    struct Ray {
        Ray(Point aO, Vector aD):o(aO), d(aD), dinv(aD.Inverse()){}
        Ray():o(0.,0.,0.), d(0.,0.,0.), dinv(0., 0., 0.){}
        Point GetPoint(double t){
            Eigen::Vector3d p = o.d + d.d*t;
            return Point(p);
        }
        Point o;
        Vector d;
        Vector dinv;
    };


    struct Transform {
        Eigen::Projective3d t;
        Eigen::Projective3d tinv;

        Transform(){
            t = Eigen::Matrix4d::Identity();
            tinv = Eigen::Matrix4d::Identity();
        }
        Transform(Eigen::Matrix4d& min){
            t = min;
            tinv = t.inverse();
        }
        Transform(Eigen::Projective3d& tin){
            t = tin;
            tinv = tin.inverse();
        }
        // To save an inverse if have it already
        Transform(Eigen::Projective3d& tin, Eigen::Projective3d& tinvin){
            t = tin;
            tinv = tinvin;
        }
        // For explicit identity
        static Transform Identity(){
            return Transform();
        }

        static Transform Scaling(double x, double y, double z){
            Eigen::Projective3d n;
            n = Eigen::Scaling(x,y,z);
            return Transform(n);
        }
        static Transform Translation(double x, double y, double z){
            Eigen::Projective3d n;
            n = Eigen::Translation3d(x,y,z);
            return Transform(n);
        }
        static Transform Rotation(double yaw, double pitch, double roll){
            Eigen::AngleAxisd rollR(roll, Eigen::Vector3d::UnitZ());
            Eigen::AngleAxisd yawR(yaw, Eigen::Vector3d::UnitY());
            Eigen::AngleAxisd pitchR(pitch, Eigen::Vector3d::UnitX());

            Eigen::Quaterniond q = rollR * yawR * pitchR;
            Eigen::Projective3d n;
            n = q.matrix();
            return Transform(n);
        }

        Transform Inverse(){
            return Transform(tinv, t);
        }
        Transform operator*(const Transform &rhs){
            Eigen::Projective3d n;
            n = t * rhs.t;
            Eigen::Projective3d ninv;
            ninv = rhs.tinv * tinv;
            return Transform(n, ninv);
        }
        Transform& operator*=(const Transform &rhs){
            t = t * rhs.t;
            tinv = rhs.tinv * tinv;
            return *this;
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
            o.dinv = o.d.Inverse();
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
            o.dinv = o.d.Inverse();
            return o;
        }
    };
};

std::ostream &operator<<(std::ostream &os, const Math::Vector &m);
std::ostream &operator<<(std::ostream &os, const Math::Ray &m);

#endif
