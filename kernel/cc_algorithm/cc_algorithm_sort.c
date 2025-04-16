
/****************************************************************************************************
* File cc_algorithm_sort.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_algorithm_sort.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */
#include "cc_algorithm_math.h"

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

/* cc_algorithm_sort */
cc_algorithm_sort_struct cc_algorithm_sort_t;
/* init flag */
cc_boolean cc_algorithm_sort_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_algorithm_sort_init()
****************************************************************************************************/
cc_result cc_algorithm_sort_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init cc_algorithm_sort */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_sort_bubble()
****************************************************************************************************/
cc_result cc_algorithm_sort_bubble(cc_uint8 *array,cc_uint32 len)
{
    cc_result result = CC_E_OK;
    cc_uint32 i;
    cc_uint32 j;

    do
    {
        /* check pointer */
        CHECK_PTR(result,array);
        CHECK_LOGIC(result,(len > 0));
        /* impletement */
        for (i = 0; i < (len - 1); i++)
        {
            for (j = 0; j < (len - 1 - i); j++)
            {
                if(array[j] > array[j + 1])
                {
                    cc_algorithm_math_swapvalue(&array[j],&array[j + 1]);
                }
            }
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_sort_select()
****************************************************************************************************/
cc_result cc_algorithm_sort_select(cc_uint8 *array,cc_uint32 len)
{
    cc_result result = CC_E_OK;
    cc_uint32 i;
    cc_uint32 j;
    cc_uint32 min;

    do
    {
        /* check pointer */
        CHECK_PTR(result,array);
        CHECK_LOGIC(result,(len > 0));
        /* impletement */
        for (i = 0; i < (len - 1); i++)
        {
            min = i;
            /* find min */
            for (j = i + 1; j < len; j++)
            {
                if(array[j] < array[min])
                {
                    min = j;
                }
            }
            /* swap */
            if(min != i)
            {
                cc_algorithm_math_swapvalue(&array[i],&array[min]);
            }
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_sort_insert()
****************************************************************************************************/
cc_result cc_algorithm_sort_insert(cc_uint8 *array,cc_uint32 len)
{
    cc_result result = CC_E_OK;
    cc_uint32 i;

    do
    {
        /* check pointer */
        CHECK_PTR(result,array);
        CHECK_LOGIC(result,(len > 0));
        /* impletement */
        for (i = 1; i < len; i++)
        {

        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_sort_quick()
****************************************************************************************************/
cc_result cc_algorithm_sort_quick(cc_uint8 *array,cc_uint32 len)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,array);
        CHECK_LOGIC(result,(len > 0));
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_sort_mainfunction()
****************************************************************************************************/
cc_result cc_algorithm_sort_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_algorithm_sort.c End!
****************************************************************************************************/

