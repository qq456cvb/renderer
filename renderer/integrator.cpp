#include "integrator.h"


fvec3 Integrator::path_trace(Ray *ray, int depth) {
    Intersection isect;
    if (depth >= max_depth) return fvec3{0., 0., 0.};
    if (scene->intersect(ray, &isect) > 0) {
        Ray next;
        float pdf;
        // to do, transform to local frame
        isect.bsdf->sample_f(ray->d, next.d, pdf);
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