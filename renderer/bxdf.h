#ifndef BXDF_H
#define BXDF_H
#include <armadillo>
using namespace arma;

class BXDF
{
public:
    BXDF();
    ~BXDF();

    virtual fvec3 sample_f(const fvec3 *out, fvec3 *in) = 0;
    virtual fvec3 f(const fvec3 *out, const fvec3 *in) = 0;

private:

};

BXDF::BXDF()
{
}

BXDF::~BXDF()
{
}
#endif
