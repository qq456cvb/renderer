#include "sphere.h"

float Sphere::intersect(Ray *ray, Intersection *isect) {
    fvec3 oo = ray->o - o;
    float b = 2 * dot(oo, ray->d);
    float c = dot(oo, oo) - r * r;

    float delta = b * b - 4 * c;
    if (delta < 1e-7f) return 0;

    float t1 = (-b - sqrt(delta)) / 2.f;
    if (t1 > 1e-7f) {
        isect->p = (*ray)(t1);
        isect->n = normalise(isect->p - o);
        return t1;
    }

    float t2 = (-b + sqrt(delta)) / 2.f;
    if (t2 > 1e-7f) {
        isect->p = (*ray)(t2);
        isect->n = normalise(isect->p - o);
        return t2;
    }
    return 0;
}


fvec3 Sphere::sample_p(fvec3 *normal) {
    float theta = acos(1. - 2 * randu());
    float phi = randu() * datum::pi * 2;
    fvec3 n = fvec3{ sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta) };
    if (normal) *normal = n;
    return o + r * n;
}

float Sphere::area() {
    return 4 * datum::pi * r * r;
}


Sphere::Sphere(const fvec3 &o, const float &r) : o(o), r(r)
{
}

Sphere::~Sphere()
{
}
