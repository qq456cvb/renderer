#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "scene.hpp"
#include "pinhole.h"

class Integrator
{
public:
    Scene *scene;
    PinholeCam *cam;
    int max_depth = 5;
    
    Integrator();
    ~Integrator();

    Mat<fvec3> render(int width, int height);
    fvec3 path_trace(Ray *ray, int depth=0, fvec3 beta=fvec3{0.f, 0.f, 0.f});
};

Integrator::Integrator()
{
}

Integrator::~Integrator()
{
}


#endif