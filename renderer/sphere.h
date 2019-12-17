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
    float intersect(Ray * ray);
};

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}


#endif
