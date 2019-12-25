#include "bsdf.h"
#include <limits>
#include "montecarlo.hpp"

fvec3 BSDF::sample_f(const fvec3 *out, fvec3 *in, float &pdf) {
    if (type == Type::DIFFUSE) {
        *in = sample_hsphere_cos();
        pdf = dot(*in, fvec3{ (0, 0, 1.f) });
    } else if (type == Type::SPECULAR) {
        *in = *out;
        (*in)[2] = -(*out)[2];
        pdf = std::numeric_limits<float>::infinity();
    }
    else {
        printf("BSDF NOT SUPPORTED\n");
    }
    return f(out, in);
}

fvec3 BSDF::f(const fvec3 *out, const fvec3 *in) {
    if (type == Type::DIFFUSE) {
        return fvec3({ 1.f, 1.f, 1.f });
    }
    else if (type == Type::SPECULAR) {
        return fvec3({ 1.f, 1.f, 1.f });
    }
    else {
        printf("BSDF NOT SUPPORTED\n");
    }
}