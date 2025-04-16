
/****************************************************************************************************
* File cc_algorithm_math.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_algorithm_math.h"
#include "cc_trace.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_algorithm_math_bignumadd()
****************************************************************************************************/
cc_result cc_algorithm_math_bignumadd(cc_uint8 *dstData,cc_uint8 *srcData,cc_uint16 dstLen,cc_uint16 srcLen,cc_uint8 *resultData,cc_uint16 *resultLen,cc_uint16 maxLen)
{
    cc_result result = CC_E_OK;
    cc_uint8 carry;
    cc_uint8 value;
    cc_uint16 i;

    do
    {
        /* check pointer */
        CHECK_PTR(result,dstData);
        CHECK_PTR(result,srcData);
        CHECK_PTR(result,resultData);
        CHECK_PTR(result,resultLen);

        /* srcData add dstData */
        carry = 0;
        for (i = 0;((i < dstLen) || (i < srcLen)); i++)
        {
            /* check len */
            if (i >= maxLen)
            {
                break;
            }
            /* get carry */
            value = carry;
            /* add src data */
            if(i < srcLen)
            {
                value += srcData[i];
            }
            /* add dst data */
            if(i < dstLen)
            {
                value += dstData[i];
            }
            /* carry */
            if(value < srcData[i])
            {
                carry = 1;
            }
            /* calc result */
            resultData[i] = value;
        }
        /* output result len */
        *resultLen = i;

    }while (0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_bignumSubtract()
****************************************************************************************************/
cc_result cc_algorithm_math_bignumSubtract(cc_uint8 *dstData,cc_uint8 *srcData,cc_uint16 dstLen,cc_uint16 srcLen,cc_uint8 *resultData,cc_uint16 *resultLen,cc_uint16 maxLen)
{
    cc_result result = CC_E_OK;
    cc_uint8 borrow;
    cc_uint8 value;
    cc_uint16 i;

    do
    {
        /* check pointer */
        CHECK_PTR(result,dstData);
        CHECK_PTR(result,srcData);
        CHECK_PTR(result,resultData);
        CHECK_PTR(result,resultLen);

        /* srcData subtract dstData */
        if(dstLen > srcLen)
        {
            continue;
        }

        borrow = 0;
        for (i = 0;i < srcLen; i++)
        {
            /* check len */
            if (i >= maxLen)
            {
                break;
            }
            /* Subtract borrow */
            value = srcData[i] - borrow;
            /* Subtract dstData */
            if(i < dstLen)
            {
                value -= dstData[i];
            }
            /* process borrow */
            borrow = 0;
            if(value > srcData[i])
            {
                borrow = 1;
                value += 0xFF;
            }
            /* result */
            resultData[i] = value;
        }
        /* result len */
        *resultLen = i;

    }while (0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_fmod()
****************************************************************************************************/
cc_result cc_algorithm_math_fmod(cc_double *value,cc_double x,cc_double y)
{
    cc_result result = CC_E_OK;
    cc_double quotient;
    cc_double integer;
    cc_double remainder;

    do
    {
        /* check parameter */
        CHECK_PTR(result,value);
        CHECK_LOGIC(result,(y != 0.0));

        /* impletement */
        /* double x % double y */
        quotient = x / y;
        integer = (quotient >= 0) ? quotient : (quotient - 1.0);
        remainder = x - (y * integer);
        /* output */
        *value = remainder;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_getradian()
****************************************************************************************************/
cc_result cc_algorithm_math_getradian(cc_double *radian,cc_double angle)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,radian);

        /* impletement */
        /* radian = angle * (2 * PI / 360) */
        *radian = angle * CC_ALGORITHM_MATH_PI / 180.0;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_getangle()
****************************************************************************************************/
cc_result cc_algorithm_math_getangle(cc_double *angle,cc_double radian)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,angle);

        /* impletement */
        /* angle = radian / (2 * PI / 360) */
        *angle = radian * 180.0 / CC_ALGORITHM_MATH_PI;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_sin()
****************************************************************************************************/
cc_result cc_algorithm_math_sin(cc_double *value,cc_double radian)
{
    cc_result result = CC_E_OK;
    cc_double sum;
    cc_double term;
    cc_double numerator;
    cc_double denominator;
    cc_int32 sign;
    cc_double x2;

    do
    {
        /* check parameter */
        CHECK_PTR(result,value);

        /* impletement */
        /* Taylor series : y = sum[0,...](((f^(n)(a)) / n!) * ((x - a)^n)) */
        /* Taylor series : sin(x) = sum[0,...]((-1)^n * (x ^ (2 * n + 1) / (2 * n + 1)!)) */
        /* Taylor series : sin(x) = x - x^3/3 + x^5/5 - x^7/7 + ... */
#if (CC_ALGORITHM_MATH_DEBUG == CC_ON)
        /* remainder: [-2pi,+2pi] */
        cc_algorithm_math_fmod(&radian,radian,2 * CC_ALGORITHM_MATH_PI);
        /* [+pi,+2pi] -> [-pi,0] */
        radian = (radian > CC_ALGORITHM_MATH_PI) ? (radian - 2 * CC_ALGORITHM_MATH_PI) : radian ;
        /* [-2pi,-pi] -> [0,+pi] */
        radian = (radian < (-CC_ALGORITHM_MATH_PI)) ? (radian + 2 * CC_ALGORITHM_MATH_PI) : radian ;
#else
        /* remainder: [-pi,+pi] */
        cc_algorithm_math_fmod(&radian,radian + CC_ALGORITHM_MATH_PI,2 * CC_ALGORITHM_MATH_PI);
        radian = radian - CC_ALGORITHM_MATH_PI;
#endif /* CC_ALGORITHM_MATH_DEBUG == CC_ON */
        /* calc */
        sum = 0.0;
        term = radian;
        numerator = radian;
        denominator = 1.0;
        x2 = radian * radian;
        sign = 1;
        for (cc_uint32 n = 1; n <= CC_ALGORITHM_MATH_TAYLOR_ACCURACY; n++)
        {
            /* sum */
            sum += term;
            /* next term */
            /* numerator : radian ^ (2 * n + 1) */
            numerator *= x2;
            /* denominator : (2 * n + 1)! */
            denominator *= (2 * n) * (2 * n + 1);
            /* sign : +1 -1 +1 -1 +1 ... */
            sign *= (-1);
            /* term : (-1)^n * (x^(2n + 1) / (2n + 1)!) */
            term = sign * numerator / denominator;
        }
        /* output */
        *value = sum;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_cos()
****************************************************************************************************/
cc_result cc_algorithm_math_cos(cc_double *value,cc_double radian)
{
    cc_result result = CC_E_OK;
    cc_double sum;
    cc_double term;
    cc_double numerator;
    cc_double denominator;
    cc_int32 sign;

    do
    {
        /* check parameter */
        CHECK_PTR(result,value);

        /* impletement */
        /* Taylor series : y = sum[0,...](((f^(n)(a)) / n!) * ((x - a)^n)) */
        /* Taylor series : cos(x) = sum[0,...]((-1)^n * (x ^ (2 * n)) / (2 * n)!) */
        /* Taylor series : cos(x) = 1 - x^2/2 + x^4/4 - x^6/6 + ... */

        /* remainder: [-pi,+pi] */
        cc_algorithm_math_fmod(&radian,radian + CC_ALGORITHM_MATH_PI,2 * CC_ALGORITHM_MATH_PI);
        radian = radian - CC_ALGORITHM_MATH_PI;
        /* calc */
        sum = 0.0;
        term = 1.0;
        numerator = 1.0;
        denominator = 1.0;
        sign = 1;
#if (CC_ALGORITHM_MATH_DEBUG == CC_ON)
        /* sum first */
        sum += term;
        for (cc_uint32 n = 1; n <= CC_ALGORITHM_MATH_TAYLOR_ACCURACY; n++)
        {
            /* next term */
            /* numerator : radian ^ (2 * n) */
            numerator *= radian * radian;
            /* denominator : (2 * n)! */
            denominator *= (2 * n - 1) * (2 * n);
            /* sign : +1 -1 +1 -1 +1 ... */
            sign *= -1;
            /* term : (-1)^n * (x^(2n) / (2n)!) */
            term = sign * numerator / denominator;
            /* sum */
            sum += term;
        }
#else
        for (cc_uint32 n = 0; n < CC_ALGORITHM_MATH_TAYLOR_ACCURACY; n++)
        {
            /* term : (-1)^n * (x^(2n) / (2n)!) */
            term = sign * numerator / denominator;
            /* sum */
            sum += term;

            /* next term */
            /* numerator : radian ^ (2 * n) */
            numerator *= radian * radian;
            /* denominator : (2 * n)! */
            denominator *= (2 * n - 1) * (2 * n);
            /* sign : +1 -1 +1 -1 +1 ... */
            sign *= -1;
        }
#endif /* CC_ALGORITHM_MATH_DEBUG == CC_ON */
        /* output */
        *value = sum;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_tan()
****************************************************************************************************/
cc_result cc_algorithm_math_tan(cc_double *value,cc_double radian)
{
    cc_result result = CC_E_OK;
    cc_double sin;
    cc_double cos;

    do
    {
        /* check parameter */
        CHECK_PTR(result,value);

        /* impletement */
        /* tan(x) = sin(x) / cos(x) */
        cc_algorithm_math_sin(&sin,radian);
        cc_algorithm_math_cos(&cos,radian);
        /* check */
        CHECK_LOGIC(result,(cos != 0.0));
        /* output */
        *value = sin / cos;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_arcsin()
****************************************************************************************************/
cc_result cc_algorithm_math_arcsin(cc_double *value,cc_double radian)
{
    cc_result result = CC_E_OK;
    cc_double sum;
    cc_double term;
    cc_double numerator;
    cc_double denominator;
    cc_double x2;

    do
    {
        /* check parameter */
        CHECK_PTR(result,value);
        /* -1.0 < radian < 1.0 */
        CHECK_LOGIC(result,((-1.0 < radian) && (radian < 1.0)));

        /* impletement */
        sum = 0.0;
        term = radian;
        numerator = radian;
        denominator = 1.0;
        x2 = radian * radian;
        sum += term;
        for (cc_uint32 n = 1; n < CC_ALGORITHM_MATH_TAYLOR_ACCURACY; n++)
        {
            /* calc term: Taylor series & Peano remainder */
            /* numerator : (2 * n - 1) * radian^(2 * n + 1) */
            numerator *= (2 * n - 1) * x2;
            /* denominator : (2 * n)(2 * n + 1) */
            denominator *= (2 * n) * (2 * n + 1);
            /* term : (x^(2n + 1) / (2n)!) */
            term = numerator / denominator;
            /* sum */
            sum += term;
        }
        /* output */
        *value = sum;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_arccos()
****************************************************************************************************/
cc_result cc_algorithm_math_arccos(cc_double *value,cc_double radian)
{
    cc_result result = CC_E_OK;
    cc_double arcsin;

    do
    {
        /* check parameter */
        CHECK_PTR(result,value);

        /* impletement */
        /* arccos(x) = PI/2 - arcsin(x) */
        cc_algorithm_math_arcsin(&arcsin,radian);
        /* output */
        *value = CC_ALGORITHM_MATH_PI / 2 - arcsin;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_arctan()
****************************************************************************************************/
cc_result cc_algorithm_math_arctan(cc_double *value,cc_double radian)
{
    cc_result result = CC_E_OK;
    cc_double sum;
    cc_double term;
    cc_double numerator;
    cc_double denominator;
    cc_double x2;
    cc_int32 sign;
    cc_double tan;

    do
    {
        /* check parameter */
        CHECK_PTR(result,value);

        /* impletement */
        if(radian > 1.0)
        {
            cc_algorithm_math_tan(&tan,1.0/radian);
            *value = CC_ALGORITHM_MATH_PI / 2 - tan;
            continue;
        }
        if(radian < -1.0)
        {
            cc_algorithm_math_tan(&tan,1.0/radian);
            *value = (-CC_ALGORITHM_MATH_PI) / 2 - tan;
            continue;
        }
        sum = 0.0;
        term = radian;
        numerator = radian;
        denominator = 1.0;
        x2 = radian * radian;
        sign = (-1);
        sum = term;
        for (cc_uint32 n = 1; n <= CC_ALGORITHM_MATH_TAYLOR_ACCURACY; n++)
        {
            /* calc term: Taylor series : sum[0,...] (-1)^n * x^(2n+1) / (2n+1) */
            /* numerator : radian^(2 * n + 1) */
            numerator *= x2;
            /* denominator : (2 * n + 1) */
            denominator = (2 * n + 1);
            /* term */
            term = sign * numerator / denominator;
            sign *= (-1);
            /* sum */
            sum += term;
        }
        /* output */
        *value = sum;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_getgcd()
****************************************************************************************************/
cc_result cc_algorithm_math_getgcd(cc_uint32 *gcd,cc_uint32 a,cc_uint32 b)
{
    cc_result result = CC_E_NOT_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,gcd);
        /* impletement */
        if(b == 0)
        {
            *gcd = a;
            result = CC_E_OK;
            continue;
        }
        else
        {
            result = cc_algorithm_math_getgcd(gcd,b,a%b);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_powercalc()
****************************************************************************************************/
cc_result cc_algorithm_math_powercalc(cc_uint32 *value,cc_uint32 x,cc_uint32 p)
{
    cc_result result = CC_E_OK;
    cc_uint32 temp;

    do
    {
        /* check parameter */
        CHECK_PTR(result,value);
        /* impletement */
        if(p == 0)
        {
            *value = 1;
            continue;
        }
        /* example: 2^5 = 2^2 * 2^2 * 2 */
        cc_algorithm_math_powercalc(&temp,x,p/2);
        if(p % 2 == 0)
        {
            /* example: 2^4 */
            *value = temp * temp;
        }
        else
        {
            /* example: 2^5 */
            *value = temp * temp * x;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_swapvalue()
****************************************************************************************************/
cc_result cc_algorithm_math_swapvalue(cc_uint8 *dst,cc_uint8 *src)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);
        /* impletement swap */
        *dst = (*dst) ^ (*src);
        *src = (*dst) ^ (*src);
        *dst = (*dst) ^ (*src);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_math_swaparray()
****************************************************************************************************/
cc_result cc_algorithm_math_swaparray(cc_uint8 *array,cc_uint16 length)
{
    cc_result result = CC_E_OK;
    cc_uint16 left;
    cc_uint16 right;

    do
    {
        /* check parameter */
        CHECK_PTR(result,array);
        CHECK_LOGIC(result,(length > 0));
        /* impletement */
        left = 0;
        right = length - 1;
        /* swap */
        while(left < right)
        {
            cc_algorithm_math_swapvalue(&array[left],&array[right]);
            left++;
            right--;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_algorithm_math.c End!
****************************************************************************************************/

