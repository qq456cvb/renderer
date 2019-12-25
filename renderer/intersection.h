//
//  intersection.h
//  Renderer
//
//  Created by Qearl on 2019/12/21.
//  Copyright © 2019 Qearl. All rights reserved.
//

#ifndef intersection_h
#define intersection_h
#include <armadillo>
#include <vector>
#include "bsdf.h"
using namespace arma;


class Intersection {
    
public:
    fvec3 n, p;
    BSDF *bsdf;
};

#endif /* intersection_h */
