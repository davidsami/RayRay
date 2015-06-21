// David Sami 2015

#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(size_t aHeight, size_t aWidth):mHeight(aHeight),mWidth(aWidth){
    mData = new Colour[mHeight*mWidth]();
}

PixelBuffer::~PixelBuffer(){
    delete mData;
}

size_t PixelBuffer::GetHeight() const{
    return mHeight;
}

size_t PixelBuffer::GetWidth() const{
    return mWidth;
}

Colour PixelBuffer::GetPixel(size_t x, size_t y) const{
    return mData[x + y*mWidth];
}
