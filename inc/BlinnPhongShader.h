// David Sami 2015

#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H

#include "Shader.h"

class BlinnPhongShader: public Shader {
public:
    static std::unique_ptr<BlinnPhongShader> CreateBlinnPhongShader(const Settings& aSettings);
    BlinnPhongShader(double aAmbient);
    BlinnPhongShader()=delete;
protected:
    virtual Colour CalculateColour(ObjectIntersection& aObject, std::vector<LightIntersection>& aLights, Scene& aScene);
private:
    // Global settings
    double mAmbientIntensity;
};

#endif
