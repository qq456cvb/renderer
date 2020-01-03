#include "coord.hpp"

fmat33 gen_frame_from_z(const fvec3 &z) {
    int valid_digit = 0;
    for (size_t i = 0; i < 3; i++)
    {
        if (abs(z[i]) > 1e-7f) {
            valid_digit = static_cast<int>(i);
            break;
        }
    }
    fvec3 y;
    y.zeros();
    y[valid_digit] = -z[(valid_digit + 1) % 3];
    y[(valid_digit + 1) % 3] = z[valid_digit];
    y = normalise(y);
    fvec3 x = cross(y, z);

    fmat33 frame;
    frame.col(0) = x;
    frame.col(1) = y;
    frame.col(2) = z;

    return frame;
}