// David Sami 2015

struct Material {
    Material(double aSelfEmittance, double aDiffuse, double aSpecular, double aShininess): mSelfEmittance(aSelfEmittance), mDiffuse(aDiffuse), mSpecular(aSpecular), mShininess(aShininess) {}

    double mSelfEmittance;
    double mDiffuse;
    double mSpecular;
    double mShininess;
};
