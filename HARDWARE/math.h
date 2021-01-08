/* math.h standard header */

/* Copyright 2003-2010 IAR Systems AB. */

#ifndef _MATH

#define _MATH



#ifndef _SYSTEM_BUILD

  #pragma system_include

#endif



//#include <ycheck.h>

#include <ymath.h>

#include <xtgmath.h>



_C_STD_BEGIN



#if __AEABI_PORTABILITY_INTERNAL_LEVEL

  #ifndef __AEABI_PORTABLE

    #define __AEABI_PORTABLE

  #endif



  #define HUGE_VAL        _CSTD __aeabi_HUGE_VAL



  #if _DLIB_ADD_C99_SYMBOLS

    #define HUGE_VALF     _CSTD __aeabi_HUGE_VALF

    #define HUGE_VALL     _CSTD __aeabi_HUGE_VALL



    #define INFINITY      _CSTD __aeabi_INFINITY

    #define NAN           _CSTD __aeabi_NAN

  #endif /* _DLIB_ADD_C99_SYMBOLS */

#else /* __AEABI_PORTABILITY_INTERNAL_LEVEL */

  #define HUGE_VAL        (0.Infinity)



  #if _DLIB_ADD_C99_SYMBOLS

    #define HUGE_VALF     ((float) 0.Infinity)

    #define HUGE_VALL     ((long double) 0.Infinity)



    #define INFINITY      ((float) 0.Infinity)

    #define NAN           ((float) 0.NaN)

  #endif /* _DLIB_ADD_C99_SYMBOLS */

#endif /* __AEABI_PORTABILITY_INTERNAL_LEVEL */



#if _DLIB_ADD_C99_SYMBOLS

  typedef float float_t;

  typedef double double_t;

#endif /* _DLIB_ADD_C99_SYMBOLS */





_C_LIB_DECL

                /* double declarations */

__EFF_NS    __ATTRIBUTES double acos(double);

__EFF_NS    __ATTRIBUTES double asin(double);

__EFF_NS    __ATTRIBUTES double atan(double);

__EFF_NS    __ATTRIBUTES double atan2(double, double);

__EFF_NE    __ATTRIBUTES double ceil(double);

__EFF_NS    __ATTRIBUTES double exp(double);

__EFF_NE    __ATTRIBUTES double fabs(double);

__EFF_NE    __ATTRIBUTES double floor(double);

__EFF_NS    __ATTRIBUTES double fmod(double, double);

__EFF_NENR2 __ATTRIBUTES double frexp(double, int *);

__EFF_NS    __ATTRIBUTES double ldexp(double, int);

__EFF_NENR2 __ATTRIBUTES double modf(double, double *);

__EFF_NS    __ATTRIBUTES double pow(double, double);

__EFF_NS    __ATTRIBUTES double sqrt(double);

__EFF_NS    __ATTRIBUTES double tan(double);

__EFF_NS    __ATTRIBUTES double tanh(double);



__EFF_NS    __ATTRIBUTES double cos(double);

__EFF_NS    __ATTRIBUTES double cosh(double);

__EFF_NS    __ATTRIBUTES double log(double);

__EFF_NS    __ATTRIBUTES double log10(double);

__EFF_NS    __ATTRIBUTES double sin(double);

__EFF_NS    __ATTRIBUTES double sinh(double);



#if _DLIB_ADD_C99_SYMBOLS



                /* double declarations */

  __EFF_NS    __ATTRIBUTES double acosh(double);

  __EFF_NS    __ATTRIBUTES double asinh(double);

  __EFF_NS    __ATTRIBUTES double atanh(double);

  __EFF_NE    __ATTRIBUTES double cbrt(double);

  __EFF_NE    __ATTRIBUTES double copysign(double, double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES double erf(double);

    __EFF_NS    __ATTRIBUTES double erfc(double);

    __EFF_NS    __ATTRIBUTES double expm1(double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NS    __ATTRIBUTES double exp2(double);

  __EFF_NE    __ATTRIBUTES double fdim(double, double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES double fma(double, double, double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES double fmax(double, double);

  __EFF_NE    __ATTRIBUTES double fmin(double, double);

  __EFF_NS    __ATTRIBUTES double hypot(double, double);

  __EFF_NE    __ATTRIBUTES int    ilogb(double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES double lgamma(double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  #ifdef _LONGLONG

    #pragma language=save

    #pragma language=extended

    __EFF_NS __ATTRIBUTES _Longlong llrint(double);

    __EFF_NS __ATTRIBUTES _Longlong llround(double);

    #pragma language=restore

  #endif /* _LONGLONG */

  __EFF_NS    __ATTRIBUTES double log1p(double);

  __EFF_NS    __ATTRIBUTES double log2(double);

  __EFF_NS    __ATTRIBUTES double logb(double);

  __EFF_NS    __ATTRIBUTES long   lrint(double);

  __EFF_NS    __ATTRIBUTES long   lround(double);

  __EFF_NE    __ATTRIBUTES double nan(const char *);

  __EFF_NS    __ATTRIBUTES double nearbyint(double);

  __EFF_NS    __ATTRIBUTES double nextafter(double, double);

  __EFF_NS    __ATTRIBUTES double nexttoward(double, long double);

  __EFF_NS    __ATTRIBUTES double remainder(double, double);

  __EFF_NS    __ATTRIBUTES double remquo(double, double, int *);

  __EFF_NS    __ATTRIBUTES double rint(double);

  __EFF_NE    __ATTRIBUTES double round(double);

  __EFF_NS    __ATTRIBUTES double scalbn(double, int);

  __EFF_NS    __ATTRIBUTES double scalbln(double, long);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES double tgamma(double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES double trunc(double);



                /* float declarations */

  __EFF_NS    __ATTRIBUTES float acosf(float);

  __EFF_NS    __ATTRIBUTES float asinf(float);

  __EFF_NS    __ATTRIBUTES float atanf(float);

  __EFF_NS    __ATTRIBUTES float atan2f(float, float);

  __EFF_NE    __ATTRIBUTES float ceilf(float);

  __EFF_NS    __ATTRIBUTES float expf(float);

  __EFF_NE    __ATTRIBUTES float fabsf(float);

  __EFF_NE    __ATTRIBUTES float floorf(float);

  __EFF_NS    __ATTRIBUTES float fmodf(float, float);

  __EFF_NENR2 __ATTRIBUTES float frexpf(float, int *);

  __EFF_NS    __ATTRIBUTES float ldexpf(float, int);

  __EFF_NENR2 __ATTRIBUTES float modff(float, float *);

  __EFF_NS    __ATTRIBUTES float powf(float, float);

  __EFF_NS    __ATTRIBUTES float sqrtf(float);

  __EFF_NS    __ATTRIBUTES float tanf(float);

  __EFF_NS    __ATTRIBUTES float tanhf(float);



  __EFF_NS    __ATTRIBUTES float acoshf(float);

  __EFF_NS    __ATTRIBUTES float asinhf(float);

  __EFF_NS    __ATTRIBUTES float atanhf(float);

  __EFF_NE    __ATTRIBUTES float cbrtf(float);

  __EFF_NE    __ATTRIBUTES float copysignf(float, float);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES float erff(float);

    __EFF_NS    __ATTRIBUTES float erfcf(float);

    __EFF_NS    __ATTRIBUTES float expm1f(float);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NS    __ATTRIBUTES float exp2f(float);

  __EFF_NE    __ATTRIBUTES float fdimf(float, float);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES float fmaf(float, float, float);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES float fmaxf(float, float);

  __EFF_NE    __ATTRIBUTES float fminf(float, float);

  __EFF_NS    __ATTRIBUTES float hypotf(float, float);

  __EFF_NE    __ATTRIBUTES int   ilogbf(float);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES float lgammaf(float);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  #ifdef _LONGLONG

    #pragma language=save

    #pragma language=extended

    __EFF_NS    __ATTRIBUTES _Longlong llrintf(float);

    __EFF_NS    __ATTRIBUTES _Longlong llroundf(float);

    #pragma language=restore

  #endif /* _LONGLONG */

  __EFF_NS    __ATTRIBUTES float log1pf(float);

  __EFF_NS    __ATTRIBUTES float log2f(float);

  __EFF_NS    __ATTRIBUTES float logbf(float);

  __EFF_NS    __ATTRIBUTES long  lrintf(float);

  __EFF_NS    __ATTRIBUTES long  lroundf(float);

  __EFF_NE    __ATTRIBUTES float nanf(const char *);

  __EFF_NS    __ATTRIBUTES float nearbyintf(float);

  __EFF_NS    __ATTRIBUTES float nextafterf(float, float);

  __EFF_NS    __ATTRIBUTES float nexttowardf(float, long double);

  __EFF_NS    __ATTRIBUTES float remainderf(float, float);

  __EFF_NS    __ATTRIBUTES float remquof(float, float, int *);

  __EFF_NS    __ATTRIBUTES float rintf(float);

  __EFF_NE    __ATTRIBUTES float roundf(float);

  __EFF_NS    __ATTRIBUTES float scalbnf(float, int);

  __EFF_NS    __ATTRIBUTES float scalblnf(float, long);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES float tgammaf(float);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES float truncf(float);



  __EFF_NS    __ATTRIBUTES float cosf(float);

  __EFF_NS    __ATTRIBUTES float coshf(float);

  __EFF_NS    __ATTRIBUTES float logf(float);

  __EFF_NS    __ATTRIBUTES float log10f(float);

  __EFF_NS    __ATTRIBUTES float sinf(float);

  __EFF_NS    __ATTRIBUTES float sinhf(float);



                /* long double declarations */

  __EFF_NS    __ATTRIBUTES long double acosl(long double);

  __EFF_NS    __ATTRIBUTES long double asinl(long double);

  __EFF_NS    __ATTRIBUTES long double atanl(long double);

  __EFF_NS    __ATTRIBUTES long double atan2l(long double, long double);

  __EFF_NE    __ATTRIBUTES long double ceill(long double);

  __EFF_NS    __ATTRIBUTES long double expl(long double);

  __EFF_NE    __ATTRIBUTES long double fabsl(long double);

  __EFF_NE    __ATTRIBUTES long double floorl(long double);

  __EFF_NS    __ATTRIBUTES long double fmodl(long double, long double);

  __EFF_NENR2 __ATTRIBUTES long double frexpl(long double, int *);

  __EFF_NS    __ATTRIBUTES long double ldexpl(long double, int);

  __EFF_NENR2 __ATTRIBUTES long double modfl(long double, long double *);

  __EFF_NS    __ATTRIBUTES long double powl(long double, long double);

  __EFF_NS    __ATTRIBUTES long double sqrtl(long double);

  __EFF_NS    __ATTRIBUTES long double tanl(long double);

  __EFF_NS    __ATTRIBUTES long double tanhl(long double);



  __EFF_NS    __ATTRIBUTES long double acoshl(long double);

  __EFF_NS    __ATTRIBUTES long double asinhl(long double);

  __EFF_NS    __ATTRIBUTES long double atanhl(long double);

  __EFF_NE    __ATTRIBUTES long double cbrtl(long double);

  __EFF_NE    __ATTRIBUTES long double copysignl(long double, long double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES long double erfl(long double);

    __EFF_NS    __ATTRIBUTES long double erfcl(long double);

    __EFF_NS    __ATTRIBUTES long double expm1l(long double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NS    __ATTRIBUTES long double exp2l(long double);

  __EFF_NE    __ATTRIBUTES long double fdiml(long double, long double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES long double fmal(long double, long double,

                                              long double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES long double fmaxl(long double, long double);

  __EFF_NE    __ATTRIBUTES long double fminl(long double, long double);

  __EFF_NS    __ATTRIBUTES long double hypotl(long double, long double);

  __EFF_NE    __ATTRIBUTES int         ilogbl(long double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES long double lgammal(long double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  #ifdef _LONGLONG

    #pragma language=save

    #pragma language=extended

    __EFF_NS    __ATTRIBUTES _Longlong llrintl(long double);

    __EFF_NS    __ATTRIBUTES _Longlong llroundl(long double);

    #pragma language=restore

  #endif /* _LONGLONG */

  __EFF_NS    __ATTRIBUTES long double log1pl(long double);

  __EFF_NS    __ATTRIBUTES long double log2l(long double);

  __EFF_NS    __ATTRIBUTES long double logbl(long double);

  __EFF_NS    __ATTRIBUTES long        lrintl(long double);

  __EFF_NS    __ATTRIBUTES long lroundl(long double);

  __EFF_NE    __ATTRIBUTES long double nanl(const char *);

  __EFF_NS    __ATTRIBUTES long double nearbyintl(long double);

  __EFF_NS    __ATTRIBUTES long double nextafterl(long double, long double);

  __EFF_NS    __ATTRIBUTES long double nexttowardl(long double, long double);

  __EFF_NS    __ATTRIBUTES long double remainderl(long double, long double);

  __EFF_NS    __ATTRIBUTES long double remquol(long double, long double, int *);

  __EFF_NS    __ATTRIBUTES long double rintl(long double);

  __EFF_NE    __ATTRIBUTES long double roundl(long double);

  __EFF_NS    __ATTRIBUTES long double scalbnl(long double, int);

  __EFF_NS    __ATTRIBUTES long double scalblnl(long double, long);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES long double tgammal(long double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES long double truncl(long double);



  __EFF_NS    __ATTRIBUTES long double cosl(long double);

  __EFF_NS    __ATTRIBUTES long double coshl(long double);

  __EFF_NS    __ATTRIBUTES long double logl(long double);

  __EFF_NS    __ATTRIBUTES long double log10l(long double);

  __EFF_NS    __ATTRIBUTES long double sinl(long double);

  __EFF_NS    __ATTRIBUTES long double sinhl(long double);

#endif /* _DLIB_ADD_C99_SYMBOLS */



#if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH && \

    !defined(_DLIB_DO_NOT_ADD_ACCURATE_FUNCTIONS)

                /* Accurate versions of certain float functions. */

__EFF_NS __ATTRIBUTES double __iar_tan_accurate(double);

__EFF_NS __ATTRIBUTES double __iar_cos_accurate(double);

__EFF_NS __ATTRIBUTES double __iar_sin_accurate(double);

__EFF_NS __ATTRIBUTES double __iar_pow_accurate(double, double);



__EFF_NS __ATTRIBUTES double __iar_Sin_accurate(double, unsigned int);

__EFF_NS __ATTRIBUTES double __iar_Pow_accurate(double, double, short *pex);

#if _DLIB_ADD_C99_SYMBOLS

  __EFF_NS __ATTRIBUTES float __iar_tan_accuratef(float);

  __EFF_NS __ATTRIBUTES float __iar_cos_accuratef(float);

  __EFF_NS __ATTRIBUTES float __iar_sin_accuratef(float);

  __EFF_NS __ATTRIBUTES float __iar_pow_accuratef(float, float);



  __EFF_NS __ATTRIBUTES float __iar_Sin_accuratef(float, unsigned int);

  __EFF_NS __ATTRIBUTES float __iar_Pow_accuratef(float, float, short *pex);



  __EFF_NS __ATTRIBUTES long double __iar_tan_accuratel(long double);

  __EFF_NS __ATTRIBUTES long double __iar_cos_accuratel(long double);

  __EFF_NS __ATTRIBUTES long double __iar_sin_accuratel(long double);

  __EFF_NS __ATTRIBUTES long double __iar_pow_accuratel(long double,

                                                        long double);



  __EFF_NS __ATTRIBUTES long double __iar_Sin_accuratel(long double,

                                                        unsigned int);

  __EFF_NS __ATTRIBUTES long double __iar_Pow_accuratel(long double,

                                                        long double,

                                                        short *pex);

#endif /* _DLIB_ADD_C99_SYMBOLS */

#endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH &&

          !defined(_DLIB_DO_NOT_ADD_ACCURATE_FUNCTIONS) */



#ifndef _DLIB_DO_NOT_ADD_SMALL_FUNCTIONS

                /* Small versions of certain float functions. */

__EFF_NS __ATTRIBUTES double __iar_cos_small(double);

__EFF_NS __ATTRIBUTES double __iar_exp_small(double);

__EFF_NS __ATTRIBUTES double __iar_log_small(double);

__EFF_NS __ATTRIBUTES double __iar_log10_small(double);

__EFF_NS __ATTRIBUTES double __iar_pow_small(double, double);

__EFF_NS __ATTRIBUTES double __iar_sin_small(double);

__EFF_NS __ATTRIBUTES double __iar_tan_small(double);

#if _DLIB_ADD_C99_SYMBOLS

__EFF_NS __ATTRIBUTES float __iar_cos_smallf(float);

__EFF_NS __ATTRIBUTES float __iar_exp_smallf(float);

__EFF_NS __ATTRIBUTES float __iar_log_smallf(float);

__EFF_NS __ATTRIBUTES float __iar_log10_smallf(float);

__EFF_NS __ATTRIBUTES float __iar_pow_smallf(float, float);

__EFF_NS __ATTRIBUTES float __iar_sin_smallf(float);

__EFF_NS __ATTRIBUTES float __iar_tan_smallf(float);



__EFF_NS __ATTRIBUTES long double __iar_cos_smalll(long double);

__EFF_NS __ATTRIBUTES long double __iar_exp_smalll(long double);

__EFF_NS __ATTRIBUTES long double __iar_log_smalll(long double);

__EFF_NS __ATTRIBUTES long double __iar_log10_smalll(long double);

__EFF_NS __ATTRIBUTES long double __iar_pow_smalll(long double, long double);

__EFF_NS __ATTRIBUTES long double __iar_sin_smalll(long double);

__EFF_NS __ATTRIBUTES long double __iar_tan_smalll(long double);

#endif /* _DLIB_ADD_C99_SYMBOLS */

#endif /* _DLIB_DO_NOT_ADD_SMALL_FUNCTIONS */



_END_C_LIB_DECL



#ifdef __cplusplus

  _EXTERN_CPP

  __EFF_NE    __ATTRIBUTES double abs(double);

  __EFF_NS    __ATTRIBUTES double pow(double, int);



  __EFF_NE    __ATTRIBUTES float abs(float);

  __EFF_NS    __ATTRIBUTES float acos(float);

  __EFF_NS    __ATTRIBUTES float asin(float);

  __EFF_NS    __ATTRIBUTES float atan(float);

  __EFF_NS    __ATTRIBUTES float atan2(float, float);

  __EFF_NE    __ATTRIBUTES float ceil(float);

  __EFF_NS    __ATTRIBUTES float cos(float);

  __EFF_NS    __ATTRIBUTES float cosh(float);

  __EFF_NS    __ATTRIBUTES float exp(float);

  __EFF_NE    __ATTRIBUTES float fabs(float);

  __EFF_NE    __ATTRIBUTES float floor(float);

  __EFF_NS    __ATTRIBUTES float fmod(float, float);

  __EFF_NENR2 __ATTRIBUTES float frexp(float, int *);

  __EFF_NS    __ATTRIBUTES float ldexp(float, int);

  __EFF_NS    __ATTRIBUTES float log(float);

  __EFF_NS    __ATTRIBUTES float log10(float);

  __EFF_NENR2 __ATTRIBUTES float modf(float, float *);

  __EFF_NS    __ATTRIBUTES float pow(float, float);

  __EFF_NS    __ATTRIBUTES float pow(float, int);

  __EFF_NS    __ATTRIBUTES float sin(float);

  __EFF_NS    __ATTRIBUTES float sinh(float);

  __EFF_NS    __ATTRIBUTES float sqrt(float);

  __EFF_NS    __ATTRIBUTES float tan(float);

  __EFF_NS    __ATTRIBUTES float tanh(float);

  __EFF_NS    __ATTRIBUTES float acosh(float);

  __EFF_NS    __ATTRIBUTES float asinh(float);

  __EFF_NS    __ATTRIBUTES float atanh(float);

  __EFF_NE    __ATTRIBUTES float cbrt(float);

  __EFF_NE    __ATTRIBUTES float copysign(float, float);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES float erf(float);

    __EFF_NS    __ATTRIBUTES float erfc(float);

    __EFF_NS    __ATTRIBUTES float expm1(float);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NS    __ATTRIBUTES float exp2(float);

  __EFF_NE    __ATTRIBUTES float fdim(float, float);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES float fma(float, float, float);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES float fmax(float, float);

  __EFF_NE    __ATTRIBUTES float fmin(float, float);

  __EFF_NS    __ATTRIBUTES float hypot(float, float);

  __EFF_NE    __ATTRIBUTES int   ilogb(float);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES float lgamma(float);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */



  #ifdef _LONGLONG

    #pragma language=save

    #pragma language=extended

    __EFF_NS    __ATTRIBUTES _Longlong llrint(float);

    __EFF_NS    __ATTRIBUTES _Longlong llround(float);

    #pragma language=restore

  #endif /* _LONGLONG */



  __EFF_NS    __ATTRIBUTES float log1p(float);

  __EFF_NS    __ATTRIBUTES float log2(float);

  __EFF_NS    __ATTRIBUTES float logb(float);

  __EFF_NS    __ATTRIBUTES long  lrint(float);

  __EFF_NS    __ATTRIBUTES long  lround(float);

  __EFF_NS    __ATTRIBUTES float nearbyint(float);

  __EFF_NS    __ATTRIBUTES float nextafter(float, float);

  __EFF_NS    __ATTRIBUTES float nexttoward(float, long double);

  __EFF_NS    __ATTRIBUTES float remainder(float, float);

  __EFF_NS    __ATTRIBUTES float remquo(float, float, int *);

  __EFF_NS    __ATTRIBUTES float rint(float);

  __EFF_NE    __ATTRIBUTES float round(float);

  __EFF_NS    __ATTRIBUTES float scalbn(float, int);

  __EFF_NS    __ATTRIBUTES float scalbln(float, long);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES float tgamma(float);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES float trunc(float);



  __EFF_NE    __ATTRIBUTES long double abs(long double);

  __EFF_NS    __ATTRIBUTES long double acos(long double);

  __EFF_NS    __ATTRIBUTES long double asin(long double);

  __EFF_NS    __ATTRIBUTES long double atan(long double);

  __EFF_NS    __ATTRIBUTES long double atan2(long double, long double);

  __EFF_NE    __ATTRIBUTES long double ceil(long double);

  __EFF_NS    __ATTRIBUTES long double cos(long double);

  __EFF_NS    __ATTRIBUTES long double cosh(long double);

  __EFF_NS    __ATTRIBUTES long double exp(long double);

  __EFF_NE    __ATTRIBUTES long double fabs(long double);

  __EFF_NE    __ATTRIBUTES long double floor(long double);

  __EFF_NS    __ATTRIBUTES long double fmod(long double, long double);

  __EFF_NENR2 __ATTRIBUTES long double frexp(long double, int *);

  __EFF_NS    __ATTRIBUTES long double ldexp(long double, int);

  __EFF_NS    __ATTRIBUTES long double log(long double);

  __EFF_NS    __ATTRIBUTES long double log10(long double);

  __EFF_NENR2 __ATTRIBUTES long double modf(long double, long double *);

  __EFF_NS    __ATTRIBUTES long double pow(long double, long double);

  __EFF_NS    __ATTRIBUTES long double pow(long double, int);

  __EFF_NS    __ATTRIBUTES long double sin(long double);

  __EFF_NS    __ATTRIBUTES long double sinh(long double);

  __EFF_NS    __ATTRIBUTES long double sqrt(long double);

  __EFF_NS    __ATTRIBUTES long double tan(long double);

  __EFF_NS    __ATTRIBUTES long double tanh(long double);

  __EFF_NS    __ATTRIBUTES long double acosh(long double);

  __EFF_NS    __ATTRIBUTES long double asinh(long double);

  __EFF_NS    __ATTRIBUTES long double atanh(long double);

  __EFF_NE    __ATTRIBUTES long double cbrt(long double);

  __EFF_NE    __ATTRIBUTES long double copysign(long double, long double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES long double erf(long double);

    __EFF_NS    __ATTRIBUTES long double erfc(long double);

    __EFF_NS    __ATTRIBUTES long double expm1(long double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NS    __ATTRIBUTES long double exp2(long double);

  __EFF_NE    __ATTRIBUTES long double fdim(long double, long double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES long double fma(long double, long double,

                                             long double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES long double fmax(long double, long double);

  __EFF_NE    __ATTRIBUTES long double fmin(long double, long double);

  __EFF_NS    __ATTRIBUTES long double hypot(long double, long double);

  __EFF_NE    __ATTRIBUTES int         ilogb(long double);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES long double lgamma(long double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */



  #ifdef _LONGLONG

    #pragma language=save

    #pragma language=extended

    __EFF_NS    __ATTRIBUTES _Longlong llrint(long double);

    __EFF_NS    __ATTRIBUTES _Longlong llround(long double);

    #pragma language=restore

  #endif /* _LONGLONG */



  __EFF_NS    __ATTRIBUTES long double log1p(long double);

  __EFF_NS    __ATTRIBUTES long double log2(long double);

  __EFF_NS    __ATTRIBUTES long double logb(long double);

  __EFF_NS    __ATTRIBUTES long lrint(long double);

  __EFF_NS    __ATTRIBUTES long lround(long double);

  __EFF_NS    __ATTRIBUTES long double nearbyint(long double);

  __EFF_NS    __ATTRIBUTES long double nextafter(long double, long double);

  __EFF_NS    __ATTRIBUTES long double nexttoward(long double, long double);

  __EFF_NS    __ATTRIBUTES long double remainder(long double, long double);

  __EFF_NS    __ATTRIBUTES long double remquo(long double, long double, int *);

  __EFF_NS    __ATTRIBUTES long double rint(long double);

  __EFF_NE    __ATTRIBUTES long double round(long double);

  __EFF_NS    __ATTRIBUTES long double scalbn(long double, int);

  __EFF_NS    __ATTRIBUTES long double scalbln(long double, long);

  #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

    __EFF_NS    __ATTRIBUTES long double tgamma(long double);

  #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */

  __EFF_NE    __ATTRIBUTES long double trunc(long double);



  _END_EXTERN_CPP

#endif /* __cplusplus */





#if defined(__cplusplus) && !defined(_NO_DEFINITIONS_IN_HEADER_FILES)

  _EXTERN_CPP

  /* C++ definitions */



    #pragma inline=forced

    inline double abs(double _X)    /* OVERLOADS */

    {       /* return absolute value */

      return (fabs(_X));

    }



    #pragma inline=forced

    inline double pow(double _X, int _Y)

    {       /* raise to integer power */

      unsigned int _N = _Y;

      if (_Y < 0)

        _N = 0 - _N;

     

      for (double _Z = 1; ; _X *= _X)

      {

        if ((_N & 1) != 0)

          _Z *= _X;

        if ((_N >>= 1) == 0)

          return (_Y < 0 ? (_Z == 0.0 ? HUGE_VAL : (double)(1) / _Z) : _Z);

      }

    }



    #pragma inline=forced

    inline float abs(float _X)      /* OVERLOADS */

    {       /* return absolute value */

      return (_F_FUN(fabs)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float acos(float _X)

    {       /* return arccosine */

      return (_F_FUN(acos)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float asin(float _X)

    {       /* return arcsine */

      return (_F_FUN(asin)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float atan(float _X)

    {       /* return arctangent */

      return (_F_FUN(atan)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float atan2(float _Y, float _X)

    {       /* return arctangent */

      return (_F_FUN(atan2)(_F_CAST _Y,_F_CAST  _X));

    }



    #pragma inline=forced

    inline float ceil(float _X)

    {       /* return ceiling */

      return (_F_FUN(ceil)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float cos(float _X)

    {       /* return cosine */

      return (_F_FUN(cos)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float cosh(float _X)

    {       /* return hyperbolic cosine */

      return (_F_FUN(cosh)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float exp(float _X)

    {       /* return exponential */

      return (_F_FUN(exp)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float fabs(float _X)

    {       /* return absolute value */

      return (_F_FUN(fabs)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float floor(float _X)

    {       /* return floor */

      return (_F_FUN(floor)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float fmod(float _X, float _Y)

    {       /* return modulus */

      return (_F_FUN(fmod)(_F_CAST _X,_F_CAST  _Y));

    }



    #pragma inline=forced

    inline float frexp(float _X, int *_Y)

    {       /* unpack exponent */

      return (_F_FUN(frexp)(_F_CAST _X, _Y));

    }



    #pragma inline=forced

    inline float ldexp(float _X, int _Y)

    {       /* pack exponent */

      return (_F_FUN(ldexp)(_F_CAST _X, _Y));

    }



    #pragma inline=forced

    inline float log(float _X)

    {       /* return natural logarithm */

      return (_F_FUN(log)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float log10(float _X)

    {       /* return base-10 logarithm */

      return (_F_FUN(log10)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float modf(float _X, float *_Y)

    {       /* unpack fraction */

      return (_F_FUN(modf)(_F_CAST _X,_F_PTRCAST  _Y));

    }



    #pragma inline=forced

    inline float pow(float _X, float _Y)

    {       /* raise to power */

      return (_F_FUN(pow)(_F_CAST _X,_F_CAST  _Y));

    }



    #pragma inline=forced

    inline float pow(float _X, int _Y)

    {       /* raise to integer power */

    #ifdef _FLOAT_IS_DOUBLE

      return (float) pow((double) _X, _Y);

    #else

      unsigned int _N = _Y;

      if (_Y < 0)

        _N = 0 - _N;



      for (float _Z = 1; ; _X *= _X)

      {

        if ((_N & 1) != 0)

          _Z *= _X;

        if ((_N >>= 1) == 0)

          return _Y < 0 ? (_Z == 0.0F ? (float)HUGE_VAL : (float)(1) / _Z) : _Z;

      }

    #endif /* _FLOAT_IS_DOUBLE */

    }



    #pragma inline=forced

    inline float sin(float _X)

    {       /* return sine */

      return (_F_FUN(sin)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float sinh(float _X)

    {       /* return hyperbolic sine */

      return (_F_FUN(sinh)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float sqrt(float _X)

    {       /* return square root */

      return (_F_FUN(sqrt)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float tan(float _X)

    {       /* return tangent */

      return (_F_FUN(tan)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float tanh(float _X)

    {       /* return hyperbolic tangent */

      return (_F_FUN(tanh)(_F_CAST _X));

    }



    #pragma inline=forced

    inline float acosh(float _Left)

    {       // return hyperbolic arccosine

      return (_F_FUN(acosh)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float asinh(float _Left)

    {       // return hyperbolic arcsine

      return (_F_FUN(asinh)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float atanh(float _Left)

    {       // return hyperbolic arctangent

      return (_F_FUN(atanh)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float cbrt(float _Left)

    {       // return cube root

      return (_F_FUN(cbrt)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float copysign(float _Left, float _Right)

    {       // return copysign

      return (_F_FUN(copysign)(_F_CAST _Left, _F_CAST _Right));

    }



    #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

      #pragma inline=forced

      inline float erf(float _Left)

      {       // return erf

        return (_F_FUN(erf)(_F_CAST _Left));

      }



      #pragma inline=forced

      inline float erfc(float _Left)

      {       // return erfc

        return (_F_FUN(erfc)(_F_CAST _Left));

      }



      #pragma inline=forced

      inline float expm1(float _Left)

      {       // return expml

        return (_F_FUN(expm1)(_F_CAST _Left));

      }

    #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */



    #pragma inline=forced

    inline float exp2(float _Left)

    {       // return exp2

      return (_F_FUN(exp2)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float fdim(float _Left, float _Right)

    {       // return fdim

      return (_F_FUN(fdim)(_F_CAST _Left, _F_CAST _Right));

    }



    #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

      #pragma inline=forced

      inline float fma(float _Left, float _Right, float _Addend)

      {       // return fma

        return (_F_FUN(fma)(_F_CAST _Left, _F_CAST _Right, _F_CAST _Addend));

      }

    #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */



    #pragma inline=forced

    inline float fmax(float _Left, float _Right)

    {       // return fmax

      return (_F_FUN(fmax)(_F_CAST _Left, _F_CAST _Right));

    }



    #pragma inline=forced

    inline float fmin(float _Left, float _Right)

    {       // return fmin

      return (_F_FUN(fmin)(_F_CAST _Left, _F_CAST _Right));

    }



    #pragma inline=forced

    inline float hypot(float _Left, float _Right)

    {       // return hypot

      return (_F_FUN(hypot)(_F_CAST _Left, _F_CAST _Right));

    }



    #pragma inline=forced

    inline int ilogb(float _Left)

    {       // return ilogb

      return (_F_FUN(ilogb)(_F_CAST _Left));

    }



    #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

      #pragma inline=forced

      inline float lgamma(float _Left)

      {       // return lgamma

        return (_F_FUN(lgamma)(_F_CAST _Left));

      }

    #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */



    #ifdef _LONGLONG

      #pragma language=save

      #pragma language=extended

      #pragma inline=forced

      inline _Longlong llrint(float _Left)

      {       // return llrint

        return (_F_FUN(llrint)(_F_CAST _Left));

      }



      #pragma inline=forced

      inline _Longlong llround(float _Left)

      {       // return llround

        return (_F_FUN(llround)(_F_CAST _Left));

      }

      #pragma language=restore

    #endif /* _LONGLONG */



    #pragma inline=forced

    inline float log1p(float _Left)

    {       // return loglp

      return (_F_FUN(log1p)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float log2(float _Left)

    {       // return log2

      return (_F_FUN(log2)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float logb(float _Left)

    {       // return logb

      return (_F_FUN(logb)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline long lrint(float _Left)

    {       // return lrint

      return (_F_FUN(lrint)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline long lround(float _Left)

    {       // return lround

      return (_F_FUN(lround)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float nearbyint(float _Left)

    {       // return nearbyint

      return (_F_FUN(nearbyint)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float nextafter(float _Left, float _Right)

    {       // return nextafter

      return (_F_FUN(nextafter)(_F_CAST _Left, _F_CAST _Right));

    }



    #pragma inline=forced

    inline float nexttoward(float _Left, long double _Right)

    {       // return nexttoward

      return (_F_FUN(nexttoward)(_F_CAST _Left, _F_CAST _Right));

    }



    #pragma inline=forced

    inline float remainder(float _Left, float _Right)

    {       // return remainder

      return (_F_FUN(remainder)(_F_CAST _Left, _F_CAST _Right));

    }



    #pragma inline=forced

    inline float remquo(float _Left, float _Right, int *_Pval)

    {       // return remquo

      return (_F_FUN(remquo)(_F_CAST _Left, _F_CAST _Right, _Pval));

    }



    #pragma inline=forced

    inline float rint(float _Left)

    {       // return rint

      return (_F_FUN(rint)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float round(float _Left)

    {       // return round

      return (_F_FUN(round)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline float scalbn(float _Left, int _Right)

    {       // return scalbn

      return (_F_FUN(scalbn)(_F_CAST _Left, _Right));

    }



    #pragma inline=forced

    inline float scalbln(float _Left, long _Right)

    {       // return scalbln

      return (_F_FUN(scalbln)(_F_CAST _Left, _Right));

    }



    #if _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH

      #pragma inline=forced

      inline float tgamma(float _Left)

      {       // return tgamma

        return (_F_FUN(tgamma)(_F_CAST _Left));

      }

    #endif /* _DLIB_ALLOW_LARGE_CONSTANT_TABLES_FOR_MATH */



    #pragma inline=forced

    inline float trunc(float _Left)

    {       // return trunc

      return (_F_FUN(trunc)(_F_CAST _Left));

    }



    #pragma inline=forced

    inline long double abs(long double _X)  /* OVERLOADS */

    {       /* return absolute value */

      return (_L_FUN(fabs)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double acos(long double _X)

    {       /* return arccosine */

      return (_L_FUN(acos)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double asin(long double _X)

    {       /* return arcsine */

      return (_L_FUN(asin)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double atan(long double _X)

    {       /* return arctangent */

      return (_L_FUN(atan)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double atan2(long double _Y, long double _X)

    {       /* return arctangent */

      return (_L_FUN(atan2)(_L_CAST _Y, _L_CAST _X));

    }



    #pragma inline=forced

    inline long double ceil(long double _X)

    {       /* return ceiling */

      return (_L_FUN(ceil)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double cos(long double _X)

    {       /* return cosine */

      return (_L_FUN(cos)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double cosh(long double _X)

    {       /* return hyperbolic cosine */

      return (_L_FUN(cosh)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double exp(long double _X)

    {       /* return exponential */

      return (_L_FUN(exp)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double fabs(long double _X)

    {       /* return absolute value */

      return (_L_FUN(fabs)(_L_CAST _X));

    }



    #pragma inline=forced

    inline long double floor(long double _X)

    {       /* return floor */

      return (_L_FUN(floor)(_L_CAST _X));

    }