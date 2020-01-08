//
//  primitive.cpp
//  Renderer
//
//  Created by Qearl on 2019/12/21.
//  Copyright © 2019 Qearl. All rights reserved.
//

#include "primitive.hpp"


Primitive::Primitive(unsigned int id, Material *mat, Shape *sh) {
    this->material = mat;
    this->shape = sh;
    this->id = id;
}

float Primitive::intersect(Ray *ray, Intersection *isect) {
    float res = this->shape->intersect(ray, isect);
    if (res > 0) {
        isect->bsdf = this->material->bsdf;
        isect->prim = this;
    }
    return res;
}

Primitive::~Primitive() {

}


