// David Sami 2015

#include <iostream>
#include "Colour.h"

std::ostream &operator<<(std::ostream &os, const Colour &c) { 
    os << '(' << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ')';
    return os;
}

static uint8_t clamp(const double in){
    if(in < 0.)
        return 0;
    else if(in > 255.)
        return 255;
    else
        return (uint8_t) in;
}

static uint8_t clamp(const int16_t in){
    if(in < 0)
        return 0;
    else if(in > 255)
        return 255;
    else
        return (uint8_t) in;
}

static uint8_t clampAdd(const uint8_t a, const uint8_t b){
    int16_t sum = a + b;
    return clamp(sum);
}

Colour::Colour(Math::Vector aV){
    r = clamp(aV(0));
    g = clamp(aV(1));
    b = clamp(aV(2));
}

Colour operator*(const double lhs, const Colour &c){
    uint8_t r, g, b;
    r = clamp(lhs * (double)c.r);
    g = clamp(lhs * (double)c.g);
    b = clamp(lhs * (double)c.b);

    return Colour(r,g,b);
}

Colour operator*(const Colour &c, const double rhs){
    return rhs * c;
}

Colour operator+(const Colour &lhs, const Colour &rhs){
    uint8_t r, g, b;
    r = clampAdd(lhs.r, rhs.r);
    g = clampAdd(lhs.g, rhs.g);
    b = clampAdd(lhs.b, rhs.b);

    return Colour(r,g,b);
}
