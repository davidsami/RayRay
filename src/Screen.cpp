// David Sami 2015

#include "Screen.h"

Screen* Screen::CreateScreen(Settings* aSettings){
    Screen* out = NULL;
    bool xResult, yResult;
    uint32_t xPixels, yPixels;

    xResult = aSettings->GetUnsigned(Settings::kXPixels, &xPixels);
    yResult = aSettings->GetUnsigned(Settings::kYPixels, &yPixels);

    if(xResult && yResult){
        out = new Screen(xPixels,yPixels);
    }

    return out;
}
