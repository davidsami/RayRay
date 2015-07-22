// David Sami 2015

#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
    Material(double aSelfEmittance, double aDiffuse, double aSpecular, double aShininess): mSelfEmittance(aSelfEmittance), mDiffuse(aDiffuse), mSpecular(aSpecular), mShininess(aShininess) {}

    double mSelfEmittance;
    double mDiffuse;
    double mSpecular;
    double mShininess;
};

#endif
