#include "arealight.h"


fvec3 AreaLight::sample_L(Intersection *isect, fvec3 &wi, float &pdf, fvec3 &light_p) {
    fvec3 n;
    light_p = sh->sample_p(&n);
    fvec3 p2l = light_p - isect->p;
    float dist = norm(p2l);
    wi = p2l / dist;
    pdf = dist * dist / (abs(dot(-wi, n)) * sh->area());
    return fvec3{1.f, 1.f, 1.f} * intensity;
}

AreaLight::AreaLight(Shape *sh) : sh(sh)
{
}

AreaLight::~AreaLight()
{
}