// David Sami 2015

struct Material {
    Material(double aSelfEmittance, double aDiffuse, double aSpecular): mSelfEmittance(aSelfEmittance), mDiffuse(aDiffuse), mSpecular(aSpecular) {}

    double mSelfEmittance;
    double mDiffuse;
    double mSpecular;
};
