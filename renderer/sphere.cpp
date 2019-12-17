#include "sphere.h"

float Sphere::intersect(Ray *ray) {
    fvec3 oo = ray->o - o;
    float b = 2 * dot(oo, ray->d);
    float c = dot(oo, oo) - r * r;

    float delta = b * b - 4 * c;
    if (delta < 0) return 0;

    float t1 = (-b - sqrt(delta)) / 2.f;
    if (t1 > 0) return t1;
   
    float t2 = (-b + sqrt(delta)) / 2.f;
    if (t2 > 0) return t2;
    return 0;
}