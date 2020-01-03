//
//  scene.cpp
//  Renderer
//
//  Created by Qearl on 2019/12/21.
//  Copyright © 2019 Qearl. All rights reserved.
//

#include "scene.hpp"
#include "coord.hpp"

bool Scene::add_primitive(Primitive *prim) {
    this->prims.push_back(prim);
    if (prim->light)
    {
        this->lights.push_back(prim->light);
    }
    return true;
}

float Scene::intersect(Ray *ray, Intersection *isect) {
    for (auto prim : prims) {
        float dist = prim->intersect(ray, isect);
        if (dist > 0) {
            isect->local2world = gen_frame_from_z(isect->n);
            isect->world2local = arma::inv(isect->local2world);
            return dist;
        }
    }
    return 0;
}

bool Scene::occluded(const fvec3 &s, const fvec3 &e) {
    Ray ray(s, normalise(e - s));
    Intersection isect;
    if (!intersect(&ray, &isect))
    {
        return false;
    }
    else {
        return norm(isect.p - s) + 1e-4f < norm(e - s);
    }
}
