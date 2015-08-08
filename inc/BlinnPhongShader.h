// David Sami 2015

#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H

#include "Shader.h"

class BlinnPhongShader: public Shader {
public:
    static std::shared_ptr<BlinnPhongShader> CreateBlinnPhongShader(const Settings& aSettings);
    BlinnPhongShader(double aAmbient, uint32_t aMaxBounces);
    BlinnPhongShader()=delete;
protected:
    virtual Colour CalculateColour(ObjectIntersection& aObject, std::vector<LightIntersection>& aLights, const Scene& aScene, uint32_t aNumBounce);
private:
    // Global settings
    double mAmbientIntensity;
    double mMaxBounces;
};

#endif
