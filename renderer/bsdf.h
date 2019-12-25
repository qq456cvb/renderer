#ifndef BSDF_H
#define BSDF_H
#include "bxdf.h"


// bsdf should accept direction in its local frame, it does not store the transformation
class BSDF : public BXDF
{
public:
    enum class Type
    {
        TRANSMISSION,
        DIFFUSE,
        SPECULAR
    };

    BSDF(BSDF::Type type);
    ~BSDF();

    fvec3 sample_f(const fvec3 *out, fvec3 *in, float &pdf);
    fvec3 f(const fvec3 *out, const fvec3 *in);
private:
    BSDF::Type type;

};

BSDF::BSDF(BSDF::Type type)
{
    this->type = type;
}

BSDF::~BSDF()
{
}
#endif
