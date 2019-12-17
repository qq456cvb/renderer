#include "bsdf.h"
#include <limits>
#include "montecarlo.hpp"

fvec3 BSDF::sample_f(const fvec3 *out, fvec3 *in) {
    if (type == Type::DIFFUSE) {
        *in = sample_hsphere_cos();
    } else if (type == Type::SPECULAR) {
        *in = *out;
        (*in)[2] = -(*out)[2];
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
#define INF std::numeric_limits<float>::infinity()
        return fvec3({ INF, INF, INF });
#undef INF
    }
    else {
        printf("BSDF NOT SUPPORTED\n");
    }
}