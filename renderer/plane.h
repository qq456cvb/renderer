#ifndef PLANE_H
#define PLANE_H
#include "shape.h"

class Plane : public Shape
{
public:
    Plane(const fvec3 &n, float d);
    ~Plane();
    float intersect(Ray *ray, Intersection *isect) override;
    fvec3 sample_p(fvec3 *normal = nullptr) override;
    float area() override;

private:
    fvec3 n;
    float d;
};


#endif // PLANE_H
