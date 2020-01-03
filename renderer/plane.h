#ifndef PLANE_H
#define PLANE_H
#include "shape.h"

class Plane : public Shape
{
public:
    Plane(const fvec3 &n, float d);
    ~Plane();
    float intersect(Ray *ray, Intersection *isect);

private:
    fvec3 n;
    float d;
};


#endif // PLANE_H
