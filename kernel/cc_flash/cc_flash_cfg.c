
/****************************************************************************************************
* File cc_flash_cfg.c Start!
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
 * 2025-04-11     cc          the first version
 *
*/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_flash_cfg.h"
#include "cc_flash.h"
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

/* cc_flash_cfg */
cc_flash_cfg_struct cc_flash_cfg_t;
/* init flag */
cc_boolean cc_flash_cfg_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_flash_cfg_init()
****************************************************************************************************/
cc_result cc_flash_cfg_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init cc_flash_cfg */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_read()
****************************************************************************************************/
cc_result cc_flash_cfg_read(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_write()
****************************************************************************************************/
cc_result cc_flash_cfg_write(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_erase()
****************************************************************************************************/
cc_result cc_flash_cfg_erase(cc_uint32 address,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_mainfunction()
****************************************************************************************************/
cc_result cc_flash_cfg_servicecall(cc_uint8 *data,cc_uint16 len)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_getstartaddr()
****************************************************************************************************/
cc_result cc_flash_cfg_getstartaddr(cc_uint32 *address)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,address);
        /* output */
        *address = CC_FLASH_CFG_START_ADDRESS;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_getpagesize()
****************************************************************************************************/
cc_result cc_flash_cfg_getpagesize(cc_uint32 *pagesize)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,pagesize);
        /* output */
        *pagesize = CC_FLASH_CFG_PAGE_SIZE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_getpageitemsize()
****************************************************************************************************/
cc_result cc_flash_cfg_getpageitemsize(cc_flash_page_type_enum page,cc_uint32 *itemsize)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,itemsize);
        /* impletement */
        switch (page)
        {
        case CC_FLASH_PAGE_TYPE_MAIN:
            *itemsize = CC_FLASH_INFO_MAIN_PAGE_SIZE;
            break;
        case CC_FLASH_PAGE_TYPE_SIZE:
            *itemsize = CC_FLASH_INFO_SIZE_PAGE_SIZE;
            break;
        case CC_FLASH_PAGE_TYPE_DEVICE:
            *itemsize = CC_FLASH_INFO_DEVICES_PAGE_SIZE;
            break;
        case CC_FLASH_PAGE_TYPE_VERIFY:
            *itemsize = CC_FLASH_INFO_VERIFY_PAGE_SIZE;
            break;
        default:
            break;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_getpagecontent()
****************************************************************************************************/
cc_result cc_flash_cfg_getpagecontent(cc_uint32 **address)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,address);
        /* output */
        *address = cc_flash_cfg_t.pagecontent;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_cfg_mainfunction()
****************************************************************************************************/
cc_result cc_flash_cfg_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_flash_cfg.c End!
****************************************************************************************************/

