#ifndef PINHOLE_H
#define PINHOLE_H
#include "ray.h"

class PinholeCam
{
public:
    PinholeCam(const fvec3 &principal_axis = {0.f, 0.f, 1.f}, const fvec3 &c = {0.f, 0.f, 0.f}, const  float fov = 120.f);
    ~PinholeCam();

    float fov;

    void gen_ray(float px, float py, Ray *ray);

private:
    fvec3 c;  // cam center in world coordinate
    fvec3 pa;
    fmat33 R;  // c2w
};




#endif
