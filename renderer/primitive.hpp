//
//  primitive.hpp
//  Renderer
//
//  Created by Qearl on 2019/12/21.
//  Copyright © 2019 Qearl. All rights reserved.
//

#ifndef primitive_hpp
#define primitive_hpp

#include <stdio.h>
#include <vector>
#include "shape.h"
#include "material.hpp"
#include "ray.h"
#include "intersection.h"

class Primitive {
    unsigned int id;
    
public:
    Primitive(unsigned int id, Material *mat, Shape *sh);
    ~Primitive();
    
    Material *material;
    Shape *shape;
    float intersect(Ray *ray, Intersection *isect);
};

#endif /* primitive_hpp */
