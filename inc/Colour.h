// David Sami 2015

#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>

struct Colour{
    Colour(){
        r = g = b = 0;
    }
    uint8_t r,g,b;
};

#endif
