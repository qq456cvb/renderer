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
    
    Integrator(Scene *scene, PinholeCam *cam);
    ~Integrator();

    unsigned char* render(int width, int height);
    fvec3 path_trace(Ray *ray, int depth=0, fvec3 beta = fvec3("1.f 1.f 1.f"));
};


#endif
