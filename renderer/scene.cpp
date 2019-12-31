//
//  scene.cpp
//  Renderer
//
//  Created by Qearl on 2019/12/21.
//  Copyright © 2019 Qearl. All rights reserved.
//

#include "scene.hpp"

bool Scene::add_primitive(Primitive *prim) {
    this->prims.push_back(prim);
    return true;
}

float Scene::intersect(Ray *ray, Intersection *isect) {
    for (auto prim : prims) {
        float dist = prim->intersect(ray, isect);
        if (dist > 0) {
            return dist;
        }
    }
    return -1.f;
}
