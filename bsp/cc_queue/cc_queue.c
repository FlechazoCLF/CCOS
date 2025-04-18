
/****************************************************************************************************
* File queue.c Start!
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
#include "cc_queue.h"
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

/* cc_queue */
cc_queue_struct cc_queue_t;
/* init flag */
cc_boolean cc_queue_initflag = CC_FALSE;
/* list */

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_queue_init()
****************************************************************************************************/
cc_result cc_queue_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init queue */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_create()
****************************************************************************************************/
cc_result cc_queue_create(cc_uint8 *ctrlidx,cc_int8 *name,cc_void *buffer,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* find name */

        /* init */

        /* create lock */

        /* append queue list */

        /* output ctrlidx */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_delete()
****************************************************************************************************/
cc_result cc_queue_delete(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_read()
****************************************************************************************************/
cc_result cc_queue_read(cc_int8 *name,cc_void **buffer,cc_uint32 *length)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

        /* return pointer */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_readout()
****************************************************************************************************/
cc_result cc_queue_readout(cc_int8 *name,cc_void *buffer,cc_uint32 *length)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

        /* copy buffer */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_release()
****************************************************************************************************/
cc_result cc_queue_release(cc_int8 *name,cc_void *buffer,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_write()
****************************************************************************************************/
cc_result cc_queue_write(cc_int8 *name,cc_void *buffer,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_lock()
****************************************************************************************************/
cc_result cc_queue_lock(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_unlock()
****************************************************************************************************/
cc_result cc_queue_unlock(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_queue_mainfunction()
****************************************************************************************************/
cc_result cc_queue_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File queue.c End!
****************************************************************************************************/

