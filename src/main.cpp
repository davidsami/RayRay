// David Sami 2015

#include <iostream>
#include "RayRay.h"
#include "Settings.h"
#include "Screen.h"

int main(int argc, char* argv[]){
    Settings s;
    s.AddSetting(Settings::kFOV, "90");
    s.AddSetting(Settings::kXPixels, "1920");
    s.AddSetting(Settings::kYPixels, "1080");

    RayRay r(&s);
    r.Run();
    return 0;
} 

