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
    float rs_term = 0.1f;
    
    Integrator(Scene *scene, PinholeCam *cam);
    ~Integrator();

    unsigned char* render(int width, int height, bool alpha=false);
    fvec3 path_trace(Ray ray);
};


#endif
