#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include <armadillo>
#include "bxdf.h"
using namespace arma;

class Lambertian : public BXDF
{
public:
    Lambertian(const fvec3 &refl);
    ~Lambertian();

    fvec3 f(const fvec3 &out, const fvec3 &in) override;
    fvec3 sample_f(const fvec3 &out, fvec3 &in, float &pdf) override;
private:
    fvec3 refl;
};

#endif // LAMBERTIAN_H
