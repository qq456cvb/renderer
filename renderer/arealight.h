#ifndef AREALIGHT_H
#define AREALIGHT_H
#include "light.h"
#include "shape.h"


class AreaLight
{
private:
    Shape *sh;    
public:
    fvec3 sample_L(Intersection *isect, fvec3 &wi, float &pdf);
    
    AreaLight();
    ~AreaLight();
};

AreaLight::AreaLight()
{
}

AreaLight::~AreaLight()
{
}


#endif
