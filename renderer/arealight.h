#ifndef AREALIGHT_H
#define AREALIGHT_H
#include "light.h"
#include "shape.h"


class AreaLight : public Light
{
private:
    Shape *sh;    
public:
    float intensity = 3.f;
    fvec3 sample_L(Intersection *isect, fvec3 &wi, float &pdf, fvec3 &light_p);
    
    AreaLight(Shape *);
    ~AreaLight();
};


#endif
