// David Sami 2015

#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H

#include "Shader.h"

class BlinnPhongShader: public Shader {
protected:
    virtual Colour CalculateColour(ObjectIntersection aObject, LightIntersection aLight);
};

#endif