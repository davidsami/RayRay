// David Sami 2015

#include "Screen.h"

std::unique_ptr<Screen> Screen::CreateScreen(const Settings& aSettings){
    std::unique_ptr<Screen> out;
    bool xResult, yResult;
    uint32_t xPixels, yPixels;

    xResult = aSettings.GetUnsigned(Settings::kXPixels, &xPixels);
    yResult = aSettings.GetUnsigned(Settings::kYPixels, &yPixels);

    if(xResult && yResult){
        out = std::make_unique<Screen>(xPixels,yPixels);
    }

    return out;
}
