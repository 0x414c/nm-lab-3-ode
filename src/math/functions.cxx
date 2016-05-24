#include "../globaldefinitions.hxx"

#ifdef REAL_IS_BUILTIN
#include <cmath>
#endif // REAL_IS_BUILTIN

#include "functions.hxx"
#include "numerictypes.hxx"


namespace Math
{
  real_t
  f_1 (
    real_t x, real_t y,
    real_t alpha, real_t beta, real_t gamma
  )
  {
#ifdef REAL_IS_EXTERNAL
#ifdef REAL_IS_BOOST_FLOAT128
    return (
      alpha * x + beta *
      boost::multiprecision::pow (y, REAL_EXTERNAL_C (2.)) + gamma
    );
#endif // REAL_IS_BOOST_FLOAT128
#else
#ifdef REAL_IS_BUILTIN
    return (alpha * x + beta * std::pow (y, REAL_BUILTIN_C (2.)) + gamma);
//    return std::sin (x);
//    return (-y - std::pow (x, REAL_BUILTIN_C (2.)));
#endif // REAL_IS_BUILTIN
#endif // REAL_IS_EXTERNAL
  }


  real_t
  f_2 (
    real_t x, real_t y,
    real_t delta, real_t phi, real_t epsilon
  )
  {
#ifdef REAL_IS_EXTERNAL
#ifdef REAL_IS_BOOST_FLOAT128
    return (
      delta * x + phi *
      boost::multiprecision::pow (y, REAL_EXTERNAL_C (2.)) + epsilon
    );
#endif // REAL_IS_BOOST_FLOAT128
#else
#ifdef REAL_IS_BUILTIN
    return (delta * x + phi * std::pow (y, REAL_BUILTIN_C (2.)) + epsilon);
//    return std::cos (x);
//    return (REAL_BUILTIN_C (2.) * x - std::pow (y, REAL_BUILTIN_C (3.)));
#endif // REAL_IS_BUILTIN
#endif // REAL_IS_EXTERNAL
  }
}
