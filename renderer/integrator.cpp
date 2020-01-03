#include "integrator.h"
#include <assert.h>
#include "coord.hpp"


fvec3 Integrator::path_trace(Ray ray) {
    fvec3 L;
    L.zeros();
    Intersection isect;
    fvec3 beta;
    beta.ones();
    for (size_t i = 0; i < max_depth; i++)
    {
        if (scene->intersect(&ray, &isect) > 1e-7f) {
            // direct lighting
            if (!scene->lights.empty())
            {
                int light_idx = static_cast<int>(arma::randi(arma::distr_param(0, int(scene->lights.size()) - 1)));
                auto light = scene->lights[light_idx];
                fvec3 wi, light_p;
                float pdf;
                fvec3 Ll = light->sample_L(&isect, wi, pdf, light_p);
                fvec3 f = isect.bsdf->f(isect.world2local * ray.d, isect.world2local * wi);
                if (sum(abs(f)) > 1e-7 && !scene->occluded(isect.p + wi * 1e-4f, light_p))
                {
                    L += beta % Ll % f * dot(isect.n, wi) / pdf * scene->lights.size();
                }
            }
            
            Ray next;
            next.o = isect.p;
            float pdf;
            fvec3 f = isect.bsdf->sample_f(isect.world2local * ray.d, next.d, pdf);
            if (sum(abs(f)) < 1e-7)
            {
                break;
            }
            next.d = isect.local2world * next.d;
            next.o += next.d * 1e-4f;

            // TODO, add Le contribution
            beta %= f * dot(next.d, isect.n) / pdf;
            if (arma::randu() < rs_term)
            {
                break;
            }
            beta /= 1.f - rs_term;
            ray = next;
        }
        else {
            break;
        }
    }
    return L;
}


unsigned char* Integrator::render(int width, int height, bool alpha) {
    int stride = alpha ? 4 : 3;
    unsigned char *img = new unsigned char[height * width * stride];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            
            fvec3 color; 
            color.zeros();
            float weight = 0.f;
            for (size_t i = 0; i < 20; i++)
            {
                arma::arma_rng::set_seed_random();
                Ray ray = cam->gen_ray((x - width / 2) / float(width),
                    (y - height / 2) / float(width));
                color += path_trace(ray);
                weight += 1.f;
            }
            color /= weight;
            color = arma::clamp(color, 0.f, 1.f);
            
            img[(y * width + x) * stride] = static_cast<unsigned char>(color[0] * 255);
            img[(y * width + x) * stride + 1] = static_cast<unsigned char>(color[1] * 255);
            img[(y * width + x) * stride + 2] = static_cast<unsigned char>(color[2] * 255);
            if (alpha)
            {
                img[(y * width + x) * stride + 3] = 255;
            }
        }
        
    }
    return img;
} 

Integrator::Integrator(Scene *scene, PinholeCam *cam)
    : scene(scene), cam(cam)
{
}

Integrator::~Integrator()
{
}
