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
    isect->bsdf = this->material->bsdf;
    return this->shape->intersect(ray, isect);
}


