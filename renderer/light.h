#ifndef LIGHT_H
#define LIGHT_H
#include <armadillo>
#include "intersection.h"
using namespace arma;

class Light
{
public:
    virtual fvec3 sample_L(Intersection *isect, fvec3 &wi, float &pdf) = 0;

    Light();
    ~Light();
};

Light::Light()
{
}

Light::~Light()
{
}


#endif