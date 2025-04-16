
/****************************************************************************************************
* File cc_algorithm_math.h Start!
****************************************************************************************************/
#ifndef _CC_ALGORITHM_MATH_H
#define _CC_ALGORITHM_MATH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/* debug */
#define CC_ALGORITHM_MATH_DEBUG (CC_OFF)

/* pi */
#define CC_ALGORITHM_MATH_PI (3.14159265358979323846)
/* e */
#define CC_ALGORITHM_MATH_E (2.71828182845904523536)

/* Taylor series */
#define CC_ALGORITHM_MATH_TAYLOR_ACCURACY (20u)

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

/* Math */
/* min max abs */
#define CC_ALGORITHM_MATH_GET_MIN(a,b) ((a) < (b)) ? (a) : (b)
#define CC_ALGORITHM_MATH_GET_MAX(a,b) ((a) > (b)) ? (a) : (b)
#define CC_ALGORITHM_MATH_GET_ABS(x) ((x) > 0) ? (x) : (-x)

/* add & sub */
cc_result cc_algorithm_math_bignumadd(cc_uint8 *dstData,cc_uint8 *srcData,cc_uint16 dstLen,cc_uint16 srcLen,cc_uint8 *resultData,cc_uint16 *resultLen,cc_uint16 maxLen);
cc_result cc_algorithm_math_bignumSubtract(cc_uint8 *dstData,cc_uint8 *srcData,cc_uint16 dstLen,cc_uint16 srcLen,cc_uint8 *resultData,cc_uint16 *resultLen,cc_uint16 maxLen);
/* fmod 9.2 % 3.7 = 1.8 */
cc_result cc_algorithm_math_fmod(cc_double *value,cc_double x,cc_double y);
/* triangle sin cos tan */
cc_result cc_algorithm_math_getradian(cc_double *radian,cc_double angle);
cc_result cc_algorithm_math_getangle(cc_double *angle,cc_double radian);
cc_result cc_algorithm_math_sin(cc_double *value,cc_double radian);
cc_result cc_algorithm_math_cos(cc_double *value,cc_double radian);
cc_result cc_algorithm_math_tan(cc_double *value,cc_double radian);
cc_result cc_algorithm_math_arcsin(cc_double *value,cc_double radian);
cc_result cc_algorithm_math_arccos(cc_double *value,cc_double radian);
cc_result cc_algorithm_math_arctan(cc_double *value,cc_double radian);
/* Euclidean Algorithm 48 18 = 6 */
cc_result cc_algorithm_math_getgcd(cc_uint32 *gcd,cc_uint32 a,cc_uint32 b);
/* Prime Check */
/* Exponentiation by Squaring example: 2^5 = 2^2 * 2^2 * 2 */
cc_result cc_algorithm_math_powercalc(cc_uint32 *value,cc_uint32 x,cc_uint32 p);
/* Permutations and Combinations */
/* Monte Carlo Method */
/* swap */
cc_result cc_algorithm_math_swapvalue(cc_uint8 *dst,cc_uint8 *src);
cc_result cc_algorithm_math_swaparray(cc_uint8 *array,cc_uint16 length);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_ALGORITHM_MATH_H */
/****************************************************************************************************
* File cc_algorithm_math.h End!
****************************************************************************************************/

