// David Sami 2015

#ifndef SCREEN_H
#define SCREEN_H

#include <memory>
#include <stdint.h>
#include "Settings.h"

class Screen {
public:
    Screen(unsigned aX, unsigned aY): mX(aX), mY(aY) {}
    static std::unique_ptr<Screen> CreateScreen(const Settings& aSettings);
    uint32_t GetX() const{
        return mX;
    }
    uint32_t GetY() const{
        return mY;
    }
private:
    uint32_t mX;
    uint32_t mY;
};

#endif
