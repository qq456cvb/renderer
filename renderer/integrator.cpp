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
        fvec3 Li{1.f, 1.f, 1.f};
        return beta * Li;
    } else {
        return fvec3{0., 0., 0.};
    }
}


unsigned char* Integrator::render(int width, int height) {
    unsigned char *img = new unsigned char[height * width * 4];

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            
            fvec3 color; 
            color.zeros();
            float weight = 0.f;
            for (size_t i = 0; i < 10; i++)
            {
                Ray ray = cam->gen_ray((x - width / 2) / float(width),
                    (y - height / 2) / float(width));
                color += path_trace(&ray);
                weight += 1.f;
            }
            img[(y * width + x) * 4] = static_cast<unsigned char>(color[0] * 255);
            img[(y * width + x) * 4 + 1] = static_cast<unsigned char>(color[1] * 255);
            img[(y * width + x) * 4 + 2] = static_cast<unsigned char>(color[2] * 255);
            img[(y * width + x) * 4 + 3] = 255;
        }
        
    }
    return img;
} 

Integrator::Integrator()
{
}

Integrator::~Integrator()
{
}
