#ifndef MATHUTILS_HXX
#define MATHUTILS_HXX


#include "numerictypes.hxx"


namespace Math
{
  // TODO: [~-] Inline?
  real_t lerp (real_t x_1, real_t y_1, real_t x_2, real_t y_2, real_t x_0);

  real_t clamp (real_t x_min, real_t x_max, real_t x);

//  real_t clamp_2d (real_t a, real_t b, real_t x);

  bool isGreaterThan (real_t x, real_t y);
}


#endif // MATHUTILS_HXX
