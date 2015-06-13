// David Sami 2015
#include <math.h>
#include "Math.h"

bool Math::SolveQuadratic(double a, double b, double c, double* r0, double* r1){
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // Only imaginary roots
        return false;
    }
    double disciminantRoot = sqrt(discriminant);
    (*r0) = (-b - disciminantRoot) / (2 * c);
    (*r1) = (-b + disciminantRoot) / (2 * c);
    return true;
}
