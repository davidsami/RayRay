// David Sami 2015

#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H

#include <cstdlib>
#include "Colour.h"

class PixelBuffer{
public:
    PixelBuffer() = delete;
    PixelBuffer(size_t aHeight, size_t aWidth);
    ~PixelBuffer();

    size_t GetHeight() const;
    size_t GetWidth() const;
    Colour GetPixel(size_t x, size_t y) const;
private:
    Colour *mData;
    const size_t mHeight, mWidth;
};

#endif
