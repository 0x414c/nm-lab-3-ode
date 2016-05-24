﻿#ifndef GLOBALDEFINITIONS_HXX
#define GLOBALDEFINITIONS_HXX


#ifdef QUAD_PRECISION_ENABLED
#define REAL_IS_EXTERNAL
#define REAL_IS_BOOST_FLOAT128
#else
#define REAL_IS_BUILTIN
//#define REAL_IS_GCC_FLOAT80
//#define REAL_IS_LONG_DOUBLE
#define REAL_IS_DOUBLE
//#define REAL_IS_FLOAT
#endif // QUAD_PRECISION_ENABLED


#define INTEGER_IS_BUILTIN
#define INTEGER_IS_LONG_LONG
//#define INTEGER_IS_LONG
//#define INTEGER_IS_INT
//#define INTEGER_IS_SHORT


#define UINTEGER_IS_BUILTIN
#define UINTEGER_IS_U_LONG_LONG
//#define UINTEGER_IS_U_LONG
//#define UINTEGER_IS_U_INT
//#define UINTEGER_IS_U_SHORT


#endif // GLOBALDEFINITIONS_HXX
