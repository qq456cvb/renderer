#include "pinhole.h"
#include "coord.hpp"

[[deprecated]]
fmat33 rot(const fvec3 &a, const fvec3 &b) {
    float cosine = dot(a, b);
    if (1 + cosine < 1e-7) {
        fvec3 ax = gen_frame_from_z(b).col(1);
        fmat33 K{ {0, -ax[2], ax[1]},
                       {ax[2], 0, -ax[0]},
                       {-ax[1], ax[0], 0} };
        fmat33 eye; eye.eye();
        return eye + 2 * K * K;
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


PinholeCam::PinholeCam(fvec3 principal_axis, fvec3 c, fvec3 up, float fov)
{
    this->c = c;
    auto z = principal_axis;
    auto x = cross(up, z);
    auto y = cross(z, x);

    this->R.col(0) = x;
    this->R.col(1) = y;
    this->R.col(2) = z;

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
