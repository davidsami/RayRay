// David Sami 2015

#include "BlinnPhongShader.h"

Colour BlinnPhongShader::CalculateColour(ObjectIntersection& aObject, std::vector<LightIntersection>& aLights, Scene& aScene){
    Colour ret;

    Math::Ray ray = aObject.mRay;
    size_t materialId = aObject.mMaterialId;

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
        double diffuseConstant = aScene.mMaterials[materialId]->mDiffuse;
        double diffuseDot = l.Normal().Dot(n);
        diffuse += lightIntensity / attenuation * diffuseConstant * ((diffuseDot > 0)?diffuseDot:0);

        // Calculate specular component
        double shininess = aScene.mMaterials[materialId]->mShininess;
        double specularConstant = aScene.mMaterials[materialId]->mSpecular;
        double specularDot = n.Dot(halfAngle);
        double specular = 255 * (lightIntensity / attenuation) * specularConstant * ((specularDot > 0)?pow(specularDot, shininess):0);
        specularColour = specularColour + Math::Vector(specular, specular, specular);
    }

    ret = aObject.mColour * diffuse + Colour(specularColour);
    return ret;
}
