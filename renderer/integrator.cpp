#include "integrator.h"


// local to world
fmat33 gen_frame_from_z(fvec3 &z) {
    int valid_digit = 0;
    for (size_t i = 0; i < 3; i++)
    {
        if (abs(z[i]) > 1e-7f) {
            valid_digit = i;
            break;
        }
    }
    fvec3 y;
    y.zeros();
    y[valid_digit] = -z[(valid_digit + 1) % 3];
    y[(valid_digit + 1) % 3] = z[valid_digit];
    y = normalise(y);
    fvec3 x = cross(y, z);

    fmat33 frame;
    frame.col(0) = x;
    frame.col(1) = y;
    frame.col(2) = z;

    return frame;
}


fvec3 Integrator::path_trace(Ray *ray, int depth, fvec3 beta) {
    Intersection isect;
    if (depth >= max_depth) return fvec3{0., 0., 0.};
    if (scene->intersect(ray, &isect) > 0) {
        Ray next;
        next.o = isect.p;
        float pdf;
        // to do, transform to local frame
        fmat33 local2world = gen_frame_from_z(isect.n);
        fmat33 world2local = arma::inv(local2world);
        fvec3 f = isect.bsdf->sample_f(world2local * ray->d, next.d, pdf);
        next.d = local2world * next.d;

        // TODO, add Le contribution
        beta *= f * dot(next.d, isect.n) / pdf;
        fvec3 Li = path_trace(&next, depth + 1, beta);
        return beta * Li;
    } else {
        return fvec3{0., 0., 0.};
    }
}


Mat<fvec3> Integrator::render(int width, int height) {
    Mat<fvec3> img(height, width);

    for (size_t x = 0; x < width; x++)
    {
        for (size_t y = 0; y < height; y++)
        {
            Ray ray = cam->gen_ray((x - width / 2) / float(width),
                (y - height / 2) / float(height));
            img.at(y, x) = path_trace(&ray);
        }
        
    }
    
} 