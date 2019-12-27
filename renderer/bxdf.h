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

    virtual fvec3 sample_f(const fvec3 &out, fvec3 &in, float &pdf) = 0;
    virtual fvec3 f(const fvec3 &out, const fvec3 &in) = 0;

private:
    BXDF::Type type;
};

BXDF::BXDF(BXDF::Type type)
{
    this->type = type;
}

BXDF::~BXDF()
{
}
#endif
