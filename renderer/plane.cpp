#include "plane.h"
#include <armadillo>
#include <assert.h>

Plane::Plane(const fvec3 &n, float d) : n(n), d(d)
{
}

Plane::~Plane()
{
}

float Plane::intersect(Ray *ray, Intersection *isect) {
    float dn = dot(ray->d, n);
    if (abs(dn) < 1e-7)
    {
        return 0;
    }
    float t = (-d - dot(ray->o, n)) / dn;
    if (t < 1e-7)
    {
        return 0;
    }
    isect->n = n;
    isect->p = (*ray)(t);

    return t;
}

fvec3 Plane::sample_p(fvec3 *normal) {
    *normal = n;
    return fvec3{ 0, 0, 0 };
}

float Plane::area() {
    return std::numeric_limits<float>::infinity();
}