#include "lambertian.h"


Lambertian::Lambertian(const fvec3 &refl) 
    : refl(refl), BXDF(BXDF::Type::DIFFUSE)
{
}

Lambertian::~Lambertian()
{
}

fvec3 Lambertian::sample_f(const fvec3 &out, fvec3 &in, float &pdf) {
    return refl % BXDF::sample_f(out, in, pdf);
}

fvec3 Lambertian::f(const fvec3 &out, const fvec3 &in)
{
    return refl % BXDF::f(out, in);
}
