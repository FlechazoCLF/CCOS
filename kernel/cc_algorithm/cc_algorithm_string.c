
/****************************************************************************************************
* File cc_algorithm_string.c Start!
****************************************************************************************************/

/*
 *
 *  Copyright (c) 2024-2025 by flechazo. All rights reserved.
 *
 * Author : CarlChai LinFeng Chai flechazo
 * Website: flechazo.mba
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-14     cc          the first version
 *
*/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_algorithm_string.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */
#include "cc_mem.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* cc_algorithm_string */
cc_algorithm_string_struct cc_algorithm_string_t;
/* init flag */
cc_boolean cc_algorithm_string_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_algorithm_string_init()
****************************************************************************************************/
cc_result cc_algorithm_string_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init cc_algorithm_string */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_string_split()
****************************************************************************************************/
cc_result cc_algorithm_string_split(cc_int8 **dst,cc_uint16 *dstnum,cc_int8 *src,cc_int8 *delimiter)
{
    cc_result result = CC_E_OK;
    cc_uint16 num = 0;
    cc_int8 *srcstr;

    do
    {
        /* check */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,dstnum);
        CHECK_PTR(result,src);
        CHECK_PTR(result,delimiter);
        CHECK_LOGIC(result,(*dstnum > 0));
        /* impletement */
        srcstr = src;
        while((*srcstr != '\0') && (num < *dstnum))
        {
            if(cc_mem_strtok(dst[num],&srcstr,delimiter) == CC_E_OK)
            {
                num++;
            }
        }
        /* output */
        *dstnum = num;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_string_nsplit()
****************************************************************************************************/
cc_result cc_algorithm_string_nsplit(cc_int8 *dst,cc_uint16 *dstnum,cc_int8 *src,cc_int8 *delimiter,cc_uint32 maxlen)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,dstnum);
        CHECK_PTR(result,src);
        CHECK_PTR(result,delimiter);
        CHECK_LOGIC(result,(*dstnum > 0));
        CHECK_LOGIC(result,(maxlen > 0));
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_string_split_pos()
****************************************************************************************************/
cc_result cc_algorithm_string_split_pos(cc_uint8 *dstpos,cc_uint16 *dstnum,cc_int8 *src,cc_int8 *delimiter)
{
    cc_result result = CC_E_OK;
    cc_uint32 srclen;
    cc_uint32 delimiterlen;

    do
    {
        /* check */
        CHECK_PTR(result,dstpos);
        CHECK_PTR(result,dstnum);
        CHECK_PTR(result,src);
        CHECK_PTR(result,delimiter);
        CHECK_LOGIC(result,(*dstnum > 0));
        /* impletement */
        /* get len */
        cc_mem_strlen(src,&srclen);
        cc_mem_strlen(delimiter,&delimiterlen);
        /* check */
        CHECK_LOGIC(result,(srclen > delimiterlen));
        /*  */
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_string_nsplit_pos()
****************************************************************************************************/
cc_result cc_algorithm_string_nsplit_pos(cc_uint8 *dstpos,cc_uint16 *dstnum,cc_int8 *src,cc_int8 *delimiter)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,dstpos);
        CHECK_PTR(result,dstnum);
        CHECK_PTR(result,src);
        CHECK_PTR(result,delimiter);
        CHECK_LOGIC(result,(*dstnum > 0));
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_string_mainfunction()
****************************************************************************************************/
cc_result cc_algorithm_string_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_algorithm_string.c End!
****************************************************************************************************/

