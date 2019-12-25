#include "arealight.h"


fvec3 AreaLight::sample_L(Intersection *isect, fvec3 &wi, float &pdf) {
    fvec3 n;
    fvec3 light_p = sh->sample_p(&n);
    fvec3 p2l = light_p - isect->p;
    float dist = norm(p2l);
    wi = p2l / dist;
    pdf = dot(-wi, n) * dot(wi, isect->n) / (dist * dist);
    return fvec3{1.f, 1.f, 1.f};
}