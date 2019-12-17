#ifndef RAY_H
#define RAY_H
#include <armadillo>

using namespace arma;

class Ray {
public:
    fvec3 o;
    fvec3 d;
};
#endif
