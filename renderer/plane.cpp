#include "plane.h"

Plane::Plane(const fvec3 &n, float d) : n(n), d(d)
{
}

Plane::~Plane()
{
}

float Plane::intersect(Ray *ray, Intersection *isect) {

}