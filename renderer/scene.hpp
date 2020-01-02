//
//  scene.hpp
//  Renderer
//
//  Created by Qearl on 2019/12/21.
//  Copyright © 2019 Qearl. All rights reserved.
//

#ifndef scene_hpp
#define scene_hpp

#include <stdio.h>
#include "primitive.hpp"
#include "intersection.h"
#include <vector>


class Scene {
    std::vector<Primitive*> prims;
    
public:
    bool add_primitive(Primitive *prim);
    float intersect(Ray *ray, Intersection *isect);
    bool occluded(const fvec3 &s, const fvec3 &e);

    std::vector<Light*> lights;
};

#endif /* scene_hpp */
