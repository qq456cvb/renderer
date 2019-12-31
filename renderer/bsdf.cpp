#include "bsdf.h"

fvec3 BSDF::sample_f(const fvec3 &out, fvec3 &in, float &pdf) {
    int num_bxdfs = static_cast<int>(bxdfs.size());
    int bxdf_idx = arma::randi(arma::distr_param(0, num_bxdfs - 1));
    fvec3 res = bxdfs[bxdf_idx]->sample_f(out, in, pdf);
    pdf /= num_bxdfs;
    return res;
}

fvec3 BSDF::f(const fvec3 &out, const fvec3 &in) {
    fvec3 res; res.zeros();
    for (const auto &bxdf : bxdfs) {
        res += bxdf->f(out, in);
    }
    return res;
}

BSDF::BSDF()
{
}

BSDF::~BSDF()
{
}

void BSDF::add(BXDF *bxdf) {
    bxdfs.push_back(bxdf);
}
