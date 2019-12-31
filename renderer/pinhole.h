#ifndef PINHOLE_H
#define PINHOLE_H
#include "ray.h"

class PinholeCam
{
public:
    PinholeCam(fvec3 principal_axis = fvec3{0.f, 0.f, 1.f}, fvec3 c = fvec3{0.f, 0.f, 0.f}, const float fov = 120.f);
    ~PinholeCam();

    float fov;

    Ray gen_ray(float x, float y);

private:
    fvec3 c;  // cam center in world coordinate
    fvec3 pa;
    fmat33 R;  // c2w
};




#endif
