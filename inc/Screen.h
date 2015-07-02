// David Sami 2015

#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include "Settings.h"

class Screen {
public:
    Screen(unsigned aX, unsigned aY): mX(aX), mY(aY) {}
    static Screen* CreateScreen(Settings* aSettings);
    uint32_t GetX(){
        return mX;
    }
    uint32_t GetY(){
        return mY;
    }
private:
    uint32_t mX;
    uint32_t mY;
};

#endif
