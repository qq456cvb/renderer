//
//  material.hpp
//  Renderer
//
//  Created by Qearl on 2019/12/21.
//  Copyright © 2019 Qearl. All rights reserved.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include "bsdf.h"
#include <vector>
using namespace std;


// constant now, unaware of uv mapping
class Material {
    
public:
    BSDF *bsdf;
};

#endif /* material_hpp */
