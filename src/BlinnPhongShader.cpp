// David Sami 2015

#include "BlinnPhongShader.h"

BlinnPhongShader::BlinnPhongShader(double aAmbient):mAmbientIntensity(aAmbient){
}

std::shared_ptr<BlinnPhongShader> BlinnPhongShader::CreateBlinnPhongShader(const Settings& aSettings){
    std::shared_ptr<BlinnPhongShader> out;
    double ambient;
    bool result = aSettings.GetDouble(Settings::kAmbientIntensity, &ambient);
    if(result)
        out = std::make_shared<BlinnPhongShader>(ambient);

    return out;
}

Colour BlinnPhongShader::CalculateColour(ObjectIntersection& aObject, std::vector<LightIntersection>& aLights, const Scene& aScene){
    Colour ret;

    Math::Ray ray = aObject.mRay;
    Material material = aObject.mMaterial;

    // Diffuse intensity, and specular colour
    double diffuse = 0;
    Math::Vector specularColour(0,0,0);

    for(auto it = aLights.begin(); it != aLights.end(); it++){
        // Values needed for next parts
        Math::Vector l = (*it).mLightRay.d;
        Math::Normal n = aObject.mNormal;
        Math::Vector lPlusV = l + ray.d;
        Math::Vector halfAngle = lPlusV.Normal();

        double lightIntensity = (*it).mIntensity;
        double attenuation = (*it).mAttenuation;

        // Calculate diffuse multiplier
        double diffuseConstant = material.mDiffuse;
        double diffuseDot = l.Normal().Dot(n);
        diffuse += lightIntensity / attenuation * diffuseConstant * ((diffuseDot > 0)?diffuseDot:0);

        // Calculate specular component
        double shininess = material.mShininess;
        double specularConstant = material.mSpecular;
        double specularDot = n.Dot(halfAngle);
        double specular = 255 * (lightIntensity / attenuation) * specularConstant * ((specularDot > 0)?pow(specularDot, shininess):0);
        specularColour = specularColour + Math::Vector(specular, specular, specular);
    }

    ret = aObject.mColour * (diffuse + mAmbientIntensity) + Colour(specularColour);
    return ret;
}
