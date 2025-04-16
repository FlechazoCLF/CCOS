
/****************************************************************************************************
* File components.c Start!
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
 * 2025-04-03     cc          the first version
 *
*/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_components.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */

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

/* cc_components */
cc_components_struct cc_components_t;
/* init flag */
cc_boolean cc_components_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_components_init()
****************************************************************************************************/
cc_result cc_components_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init components */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_components_getobject()
****************************************************************************************************/
cc_result cc_components_getobject(cc_object_struct **object)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,object);
        CHECK_LOGIC(result,(cc_components_initflag == CC_TRUE));
        /* output */
        *object = &cc_components_t.object;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_components_mainfunction()
****************************************************************************************************/
cc_result cc_components_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File components.c End!
****************************************************************************************************/

