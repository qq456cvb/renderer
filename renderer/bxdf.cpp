#include "bxdf.h"

#include "montecarlo.hpp"

fvec3 BXDF::sample_f(const fvec3 &out, fvec3 &in, float &pdf) {
    if (out[2] > 0.f)  // from the other side
    {
        return fvec3{ 0, 0, 0 };
    }
    if (type == Type::DIFFUSE) {
        in = sample_hsphere_cos();
        pdf = in[2];
        return fvec3({ 1.f, 1.f, 1.f });
    } else if (type == Type::SPECULAR) {
        in = out;
        in[2] = -out[2];
        pdf = 1.f;
        return fvec3({ 1.f, 1.f, 1.f }) / in[2];
    }
    else {
        printf("BSDF NOT SUPPORTED\n");
    }
    return fvec3{ 0, 0, 0 };
}

fvec3 BXDF::f(const fvec3 &out, const fvec3 &in) {
    if (out[2] > 0.f || in[2] < 0.f)  // from the other side
    {
        return fvec3{ 0, 0, 0 };
    }
    if (type == Type::DIFFUSE) {
        return fvec3({ 1.f, 1.f, 1.f });
    }
    else if (type == Type::SPECULAR) {
        return fvec3{ 0, 0, 0 };
    }
    else {
        printf("BSDF NOT SUPPORTED\n");
        return fvec3();
    }
}


BXDF::BXDF(BXDF::Type type)
{
    this->type = type;
}

BXDF::~BXDF()
{
}