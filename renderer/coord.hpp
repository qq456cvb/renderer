#ifndef COORD_HPP
#define COORD_HPP
#include <armadillo>
using namespace arma;


// local to world
fmat33 gen_frame_from_z(const fvec3 &z);

#endif
