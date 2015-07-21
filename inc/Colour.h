// David Sami 2015

#ifndef COLOUR_H
#define COLOUR_H

#include <ostream>
#include <stdint.h>

struct Colour{
    Colour():r(0), g(0), b(0) {}
    Colour(uint8_t aR, uint8_t aG, uint8_t aB):r(aR), g(aG), b(aB) {}
    uint8_t r,g,b;
};

std::ostream &operator<<(std::ostream &os, const Colour &c);
Colour operator*(const double lhs, const Colour &c);
Colour operator*(const Colour &c, const double rhs);
Colour operator+(const Colour &lhs, const Colour &rhs);

#endif
