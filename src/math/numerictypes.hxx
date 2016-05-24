#ifndef NUMERICTYPES_HXX
#define NUMERICTYPES_HXX


#include "../globaldefinitions.hxx"

#ifdef QUAD_PRECISION_ENABLED
#include <boost/multiprecision/float128.hpp>
#endif // QUAD_PRECISION_ENABLED


namespace Math
{
#ifdef REAL_IS_EXTERNAL
#ifdef REAL_IS_BOOST_FLOAT128
#define REAL_C(x) (x ## Q)
  using real_t = boost::multiprecision::float128;
#else // REAL_IS_BOOST_FLOAT128
#error "No candidate was found for external `real_t':"
#error "`real_t' type alias was not defined due to absence of `REAL_T_IS_*' macro."
#error "`REAL_C(x)' macro was not defined too!"
#endif // REAL_IS_BOOST_FLOAT128
#else // REAL_IS_EXTERNAL
#ifdef REAL_IS_BUILTIN
#ifdef REAL_IS_GCC_FLOAT80
#define REAL_C(x) (x ## W)
  using real_t = __float80;
#else // REAL_IS_GCC_FLOAT80
#ifdef REAL_IS_LONG_DOUBLE
#define REAL_C(x) (x ## L)
  using real_t = long double;
#else // REAL_IS_LONG_DOUBLE
#ifdef REAL_IS_DOUBLE
#define REAL_C(x) (x)
  using real_t = double;
#else // REAL_IS_DOUBLE
#ifdef REAL_IS_FLOAT
#define REAL_C(x) (x ## F)
  using real_t = float;
#else // REAL_IS_FLOAT
#error "No candidate was found for builtin `real_t'"
#error "`real_t' type alias was not defined due to absence of `REAL_T_IS_*' macro."
#error "`REAL_C(x)' macro was not defined too!"
#endif // REAL_IS_FLOAT
#endif // REAL_IS_DOUBLE
#endif // REAL_IS_LONG_DOUBLE
#endif // REAL_IS_GCC_FLOAT80
#else
#error "`REAL_IS_EXTERNAL' or `REAL_IS_BUILTIN' macro should be defined!"
#endif // REAL_IS_BUILTIN
#endif // REAL_IS_EXTERNAL


#ifdef REAL_IS_EXTERNAL
#define REAL_EXTERNAL_C(x) (REAL_C (x))
  using real_external_t = real_t;
#else // REAL_IS_EXTERNAL
#ifdef REAL_IS_BUILTIN
#define REAL_BUILTIN_C(x) (REAL_C (x))
  using real_builtin_t = real_t;
#else // REAL_IS_BUILTIN
#error "`REAL_IS_EXTERNAL' or `REAL_IS_BUILTIN' macro should be defined!"
#endif // REAL_IS_BUILTIN
#endif // REAL_IS_EXTERNAL


#ifdef INTEGER_IS_LONG_LONG
#define INTEGER_C(x) (x ## LL)
  using integer_t = long long;
#else
#ifdef INTEGER_IS_LONG
#define INTEGER_C(x) (x ## L)
  using integer_t = long;
#else
#ifdef INTEGER_IS_INT
#define INTEGER_C(x) (x)
  using integer_t = int;
#else
#ifdef INTEGER_IS_SHORT
#define INTEGER_C(x) ((short) (x))
  using integer_t = short;
#else
#error "`integer_t' type alias was not defined due to absence of `INTEGER_IS_*' macro."
#error "`INTEGER_C(x)' macro was not defined too!"
#endif // INTEGER_IS_SHORT
#endif // INTEGER_IS_INT
#endif // INTEGER_IS_LONG
#endif // INTEGER_IS_LONG_LONG


#ifdef UINTEGER_IS_U_LONG_LONG
#define UINTEGER_C(x) (x ## ULL)
  using uinteger_t = unsigned long long;
#else
#ifdef UINTEGER_IS_U_LONG
#define UINTEGER_C(x) (x ## UL)
  using uinteger_t = unsigned long;
#else
#ifdef UINTEGER_IS_U_INT
#define UINTEGER_C(x) (x ## U)
  using uinteger_t = unsigned;
#else
#ifdef UINTEGER_IS_U_SHORT
#define UINTEGER_C(x) ((unsigned short) (x ## U))
  using uinteger_t = unsigned short;
#else
#error "`uinteger_t' type alias was not defined due to absence of `UINTEGER_IS_*' macro."
#error "`UINTEGER_C(x)' macro was not defined too!"
#endif // UINTEGER_IS_U_SHORT
#endif // UINTEGER_IS_U_INT
#endif // UINTEGER_IS_U_LONG
#endif // UINTEGER_IS_U_LONG_LONG
}


#endif // NUMERICTYPES_HXX
