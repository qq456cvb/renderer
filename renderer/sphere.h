#ifndef SPHERE_H
#define SPHERE_H
#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere(const fvec3 &o, const float &r);
    ~Sphere();

    float intersect(Ray * ray, Intersection *isect);
    fvec3 sample_p(fvec3 *normal = nullptr);
    float area();

private:
    fvec3 o;
    float r;
    
};


#endif
