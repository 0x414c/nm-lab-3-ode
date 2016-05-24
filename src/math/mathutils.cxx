#ifdef REAL_IS_BUILTIN
#include <cmath>
#endif // REAL_IS_BUILTIN

#include <algorithm>

#include "mathutils.hxx"
#include "numerictypes.hxx"
#include "../config.hxx"


namespace Math
{
  real_t
  lerp (real_t x_1, real_t y_1, real_t x_2, real_t y_2, real_t x_0)
  {
    return (y_1 + (y_2 - y_1) * ((x_0 - x_1) / (x_2 - x_1)));
  }


  real_t
  clamp (real_t x_min, real_t x_max, real_t x)
  {
    return std::max (x_min, std::min (x_max, x));
  }


//  real_t
//  clamp_2d (
//    real_t x_min, real_t x_max, real_t y_min, real_t y_max,
//    real_t x_1, real_t y_1, real_t x_2, real_t y_2
//  )
//  { }


  bool
  isGreaterThan (real_t x, real_t y)
  {
    return (
      (x - y) >
      Config::MathConstants::Epsilon * std::max<real_t> ({
#ifdef REAL_IS_EXTERNAL
#ifdef REAL_IS_BOOST_FLOAT128
        REAL_EXTERNAL_C (1.),
        boost::multiprecision::abs (x), boost::multiprecision::abs (y)
#endif // REAL_IS_BOOST_FLOAT128
#else
#ifdef REAL_IS_BUILTIN
        REAL_BUILTIN_C (1.), std::abs (x), std::abs (y)
#endif // REAL_IS_BUILTIN
#endif // REAL_IS_EXTERNAL
      })
    );
  }
}
