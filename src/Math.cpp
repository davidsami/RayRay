// David Sami 2015
#include <math.h>
#include "Math.h"

// r0 is the smaller one, r1 is the larger one
bool Math::SolveQuadratic(double a, double b, double c, double* r0, double* r1){
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // Only imaginary roots
        return false;
    }
    double disciminantRoot = sqrt(discriminant);
    (*r0) = (-b - disciminantRoot) / (2 * a);
    (*r1) = (-b + disciminantRoot) / (2 * a);
    return true;
}

std::ostream &operator<<(std::ostream &os, const Math::Vector &m) {
    os << '(' << m.d(0) << ", " << m.d(1) << ", " << m.d(2) << ')';
    return os;
}

std::ostream &operator<<(std::ostream &os, const Math::Point &m) {
    os << '(' << m.d(0) << ", " << m.d(1) << ", " << m.d(2) << ')';
    return os;
}

std::ostream &operator<<(std::ostream &os, const Math::Ray &m) {
    os << "O: " << m.o << " D: " << m.d;
    return os;
}
