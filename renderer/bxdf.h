#ifndef BXDF_H
#define BXDF_H
#include <armadillo>
using namespace arma;

class BXDF
{
public:
    enum Type
    {
        TRANSMISSION = 1 << 0,
        DIFFUSE = 1 << 1,
        SPECULAR = 1 << 2
    };
    BXDF(BXDF::Type type);
    ~BXDF();

    virtual fvec3 sample_f(const fvec3 &out, fvec3 &in, float &pdf);
    virtual fvec3 f(const fvec3 &out, const fvec3 &in);
    BXDF::Type type;
private:
  
};

#endif
