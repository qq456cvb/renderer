#include "bxdf.h"

#include "montecarlo.hpp"

fvec3 BXDF::sample_f(const fvec3 &out, fvec3 &in, float &pdf) {
    if (type == Type::DIFFUSE) {
        in = sample_hsphere_cos();
        pdf = dot(in, fvec3{ 0.f, 0.f, 1.f });
    } else if (type == Type::SPECULAR) {
        in = out;
        in[2] = -out[2];
        pdf = std::numeric_limits<float>::infinity();
    }
    else {
        printf("BSDF NOT SUPPORTED\n");
    }
    return f(out, in);
}

fvec3 BXDF::f(const fvec3 &out, const fvec3 &in) {
    if (type == Type::DIFFUSE) {
        return fvec3({ 1.f, 1.f, 1.f });
    }
    else if (type == Type::SPECULAR) {
        return fvec3({ 1.f, 1.f, 1.f });
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