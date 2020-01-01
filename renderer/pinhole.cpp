#include "pinhole.h"


fmat33 rot(const fvec3 &a, const fvec3 &b) {
    float cosine = dot(a, b);
    if (1 + cosine < 1e-7) {
        // TODO
        return fmat33();
    }
    else {
        fvec3 cd = cross(a, b);
        fmat33 cd_skew{{0, -cd[2], cd[1]},
                       {cd[2], 0, -cd[0]},
                       {-cd[1], cd[0], 0}};
        fmat33 eye; eye.eye();
        return eye + cd_skew + cd_skew * cd_skew / (1.f + cosine);
    }
}


PinholeCam::PinholeCam(fvec3 principal_axis, fvec3 c, float fov)
{
    this->c = c;
    this->pa = principal_axis;
    this->R = rot(fvec3{ 0, 0, 1.f }, principal_axis);
    this->fov = fov;
}

PinholeCam::~PinholeCam()
{
}

Ray PinholeCam::gen_ray(float x, float y) {
    fvec3 unit{x * tanf(fov / 360.f * datum::pi), y * tanf(fov / 360.f * datum::pi), 1.f};
    Ray ray(c, R * normalise(unit));
    return ray;
}
