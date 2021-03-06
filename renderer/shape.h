#ifndef SHAPE_H
#define SHAPE_H
#include "ray.h"
#include "intersection.h"
#include "light.h"

class Shape
{
public:

    virtual float intersect(Ray *ray, Intersection *isect) = 0;
    virtual fvec3 sample_p(fvec3 *normal = nullptr) = 0;
    virtual float area() = 0;
};

#endif
