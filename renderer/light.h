#ifndef LIGHT_H
#define LIGHT_H
#include <armadillo>
#include "intersection.h"
using namespace arma;

class Light
{
public:
    virtual fvec3 sample_L(Intersection *isect, fvec3 &wi, float &pdf, fvec3 &light_p) = 0;
    virtual fvec3 Le(Intersection *isect, const fvec3 &wi) = 0;

};


#endif