#ifndef RAY_H
#define RAY_H
#include <armadillo>

using namespace arma;

class Ray {
public:
    fvec3 o;
    fvec3 d;
    
    Ray() {}
    Ray(fvec3 o, fvec3 d) : o(o), d(d) {}
    
    fvec3 operator()(float t) {
        return o + t * d;
    };
};
#endif
