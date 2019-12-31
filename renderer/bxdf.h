#ifndef BXDF_H
#define BXDF_H
#include <armadillo>
using namespace arma;

class BXDF
{
public:
    enum class Type
    {
        TRANSMISSION,
        DIFFUSE,
        SPECULAR
    };
    BXDF(BXDF::Type type);
    ~BXDF();

    fvec3 sample_f(const fvec3 &out, fvec3 &in, float &pdf);
    fvec3 f(const fvec3 &out, const fvec3 &in);

private:
    BXDF::Type type;
};

#endif
