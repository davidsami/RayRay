// David Sami 2015

#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
    Material(double aSelfEmittance, double aDiffuse, double aSpecular, double aShininess, double aReflectivity): mSelfEmittance(aSelfEmittance), mDiffuse(aDiffuse), mSpecular(aSpecular), mShininess(aShininess), mReflectivity(aReflectivity) {}
    Material():mSelfEmittance(0), mDiffuse(0), mSpecular(0), mShininess(0), mReflectivity(0) {}

    double mSelfEmittance;
    double mDiffuse;
    double mSpecular;
    double mShininess;
    double mReflectivity;
};

#endif
