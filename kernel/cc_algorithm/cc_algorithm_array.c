
/****************************************************************************************************
* File cc_algorithm_array.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_algorithm_array.h"
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

/* cc_algorithm_array */
cc_algorithm_array_struct cc_algorithm_array_t;
/* init flag */
cc_boolean cc_algorithm_array_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_algorithm_array_init()
****************************************************************************************************/
cc_result cc_algorithm_array_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init cc_algorithm_array */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_array_moveback()
****************************************************************************************************/
cc_result cc_algorithm_array_moveback(cc_uint8 *array,cc_uint32 len,cc_uint32 movelen)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,array);
        CHECK_LOGIC(result,(len > 0));
        CHECK_LOGIC(result,(movelen > 0));
        /* impletement */
#if (CC_ALGORITHM_ARRAY_USE_MEM == CC_ON)
        cc_mem_cpy(array + movelen,array,len);
#else
        while(len--)
        {
            array[movelen + len - 1] = array[len - 1];
        }
#endif /* CC_ALGORITHM_ARRAY_USE_MEM == CC_ON */
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_array_insert()
****************************************************************************************************/
cc_result cc_algorithm_array_insert(cc_uint8 *array,cc_uint32 len,cc_uint32 index,cc_uint8 value)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,array);
        CHECK_LOGIC(result,(len > 0));
        CHECK_LOGIC(result,(index <= len));
        /* impletement */
        cc_algorithm_array_moveback(array + index,len,1);
        array[index] = value;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_array_insertarray()
****************************************************************************************************/
cc_result cc_algorithm_array_insertarray(cc_uint8 *dstarray,cc_uint32 dstlen,cc_uint32 index,cc_uint8 *array,cc_uint32 len)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,dstarray);
        CHECK_LOGIC(result,(dstlen > 0));
        CHECK_PTR(result,array);
        CHECK_LOGIC(result,(len > 0));
        CHECK_LOGIC(result,(index <= dstlen));
        /* impletement */
        cc_algorithm_array_moveback(dstarray + index,dstlen,len);
#if (CC_ALGORITHM_ARRAY_USE_MEM == CC_ON)
        cc_mem_cpy(dstarray + index,array,len);
#else
        while(len--)
        {
            dstarray[index + len - 1] = array[len - 1];
        }
#endif /* CC_ALGORITHM_ARRAY_USE_MEM == CC_ON */
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_array_mainfunction()
****************************************************************************************************/
cc_result cc_algorithm_array_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_algorithm_array.c End!
****************************************************************************************************/

