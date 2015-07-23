// David Sami 2015

#include <iostream>
#include "RayRay.h"
#include "Settings.h"
#include "Screen.h"

int main(int argc, char* argv[]){
    std::unique_ptr<Settings> s(new Settings);
    s->AddSetting(Settings::kFOV, "90");
    s->AddSetting(Settings::kXPixels, "1920");
    s->AddSetting(Settings::kYPixels, "1080");
    s->AddSetting(Settings::kAmbientIntensity, "0.1");

    RayRay r(std::move(s));
    r.Run();
    return 0;
} 

