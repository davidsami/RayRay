// David Sami 2015

#ifndef RAYRAY_H
#define RAYRAY_H

#include "Settings.h"

class RayRay {
public:
    RayRay(Settings& aSettings);
    void Run();
private:
    Settings mSettings;
};

#endif
