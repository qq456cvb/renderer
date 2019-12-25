#ifndef SPHERE_H
#define SPHERE_H
#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere();
    ~Sphere();

private:
    fvec3 o;
    float r;
    float intersect(Ray * ray, Intersection *isect);
    fvec3 sample_p(fvec3 *normal = nullptr);
    float area();
};

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}


#endif
