#ifndef MONTECARLO_H
#define MONTECARLO_H
#include <armadillo>
using namespace arma;

void sample_disk_uniform(float *x, float *y) {
    float u1, u2;
    srand(NULL);
    u1 = ((float)rand()) / RAND_MAX;
    u2 = ((float)rand()) / RAND_MAX;

    float r = sqrtf(u1), theta = 2.0f * math::pi() * u2;
    *x = r * cosf(theta);
    *y = r * sinf(theta);
}

fvec3 sample_hsphere_cos() {
    fvec3 res;
    sample_disk_uniform(&res[0], &res[1]);
    res[2] = sqrtf(fmaxf(0.f, 1.f - res[0] * res[0] - res[1] * res[1]));
    return res;
}

#endif
