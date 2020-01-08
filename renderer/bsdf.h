#ifndef BSDF_H
#define BSDF_H
#include "bxdf.h"
#include <vector>


// bsdf should accept direction in its local frame, it does not store the transformation
class BSDF
{
public:
    BSDF();
    ~BSDF();

    void add(BXDF *bxdf);

    fvec3 sample_f(const fvec3 &out, fvec3 &in, float &pdf, int &flags);
    fvec3 f(const fvec3 &out, const fvec3 &in);
private:
    std::vector<BXDF*> bxdfs;

};

#endif
