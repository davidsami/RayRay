// David Sami 2015

#include "BlinnPhongShader.h"

BlinnPhongShader::BlinnPhongShader(Colour aBackgroundColour, double aAmbient, uint32_t aMaxBounces):
    Shader(aBackgroundColour),
    mAmbientIntensity(aAmbient),
    mMaxBounces(aMaxBounces)
{
}

std::shared_ptr<BlinnPhongShader> BlinnPhongShader::CreateBlinnPhongShader(const Settings& aSettings){
    std::shared_ptr<BlinnPhongShader> out;

    Colour backgroundColour;
    bool colourResult = aSettings.GetColour(Settings::kBackgroundColour, &backgroundColour);

    double ambient;
    bool ambientResult = aSettings.GetDouble(Settings::kAmbientIntensity, &ambient);

    uint32_t maxReflectBounces;
    bool bounceResult = aSettings.GetUnsigned(Settings::kMaxReflectBounces, &maxReflectBounces);

    if(colourResult && ambientResult && bounceResult)
        out = std::make_shared<BlinnPhongShader>(backgroundColour, ambient, maxReflectBounces);

    return out;
}

Colour BlinnPhongShader::CalculateColour(ObjectIntersection& aObject, std::vector<LightIntersection>& aLights, const Scene& aScene, uint32_t aNumBounce){
    Colour ret;

    Math::Ray ray = aObject.mRay;
    Material material = aObject.mMaterial;

    // Diffuse intensity, and specular colour
    double diffuse = 0;
    Math::Vector specularColour(0,0,0);

    Math::Normal n = aObject.mNormal;

    for(auto it = aLights.begin(); it != aLights.end(); it++){
        // Values needed for next parts
        Math::Vector l = (*it).mLightRay.d;

        double lightIntensity = (*it).mIntensity;
        double attenuation = (*it).mAttenuation;
        double intensityConstant = lightIntensity / attenuation;

        // Calculate diffuse multiplier
        double diffuseConstant = material.mDiffuse;
        double diffuseDot = l.Normal().Dot(n);
        diffuse += intensityConstant * diffuseConstant * ((diffuseDot > 0)?diffuseDot:0);

        // Calculate specular component
        double specularConstant = material.mSpecular;
        if(specularConstant > 0){
            Math::Vector lPlusV = l + ray.d;
            Math::Vector halfAngle = lPlusV.Normal();

            double shininess = material.mShininess;
            double specularDot = n.Dot(halfAngle);
            double specular = 255 * intensityConstant * specularConstant * ((specularDot > 0) ? pow(specularDot, shininess):0);
            specularColour = specularColour + Math::Vector(specular, specular, specular);
        }
    }

    // Calculate reflective component
    Colour reflectiveColour(0,0,0);
    double reflectivity = material.mReflectivity;

    if(reflectivity > 0 && aNumBounce < mMaxBounces){
        Math::Vector reflectionVector = ray.d - n * 2 * (ray.d.Dot(n));
        Math::Ray reflectionRay(aObject.mPoint, reflectionVector);
        reflectiveColour = CastRay(reflectionRay, aScene) * reflectivity;
    }

    ret = aObject.mColour * (diffuse + mAmbientIntensity) + Colour(specularColour) + Colour(reflectiveColour);
    return ret;
}
