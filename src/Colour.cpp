// David Sami 2015

#include "Colour.h"

std::ostream &operator<<(std::ostream &os, const Colour &c) { 
    os << '(' << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ')';
    return os;
}
