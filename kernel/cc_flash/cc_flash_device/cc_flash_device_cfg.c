
/****************************************************************************************************
* File flash_device_cfg.c Start!
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
#include "cc_flash_device_cfg.h"
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

/* cc_flash_device_cfg */
cc_flash_device_cfg_struct cc_flash_device_cfg_t =
{
    .id = 0,
    .devices = 
    {
        [0] = 
        {
            .attribute =
            {
                .id = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC},
                .type = CC_FLASH_DEVICE_PAGE_TYPE_ATTRIBUTE,
                .devicetype = CC_FLASH_DEVICE_RAM,
                .name = "device 1",
                .author = "flechazo",
                .address = 0x800000,
                .length = 1024 * 5,
                .blocksize = 1024,
                .writeminunit = 1,
                .version = 1,
                .verify = 0,
                .reserve = {0xFF}
            },
            .info = 
            {
                .sizepage = 
                {
                    .id = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC},
                    .type = CC_FLASH_DEVICE_PAGE_TYPE_SIZE,
                    .totlesize = 1024 * 5,
                    .usesize = 0,
                    .verify = 0,
                },
                .cataloguepage = 
                {
                    .id = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC},
                    .type = CC_FLASH_DEVICE_PAGE_TYPE_CATALOGUE,
                    .num = 1,
                    .name = "folder 1",
                    .infoaddr = 0x800000 + 1024,
                },
                .verifypage = 
                {
                    .id = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC},
                    .type = CC_FLASH_DEVICE_PAGE_TYPE_VERIFY,
                    .verify = 0,
                },
            },
            .status = CC_FLASH_DEVICE_STATUS_FREE,
            .func = 
            {
                cc_flash_device_cfg_init,
                cc_flash_device_cfg_read,
                cc_flash_device_cfg_write,
                cc_flash_device_cfg_erase
            },
            .list = {0}
        },
        [1] = 
        {
            .attribute =
            {
                .id = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC},
                .type = CC_FLASH_DEVICE_PAGE_TYPE_ATTRIBUTE,
                .devicetype = CC_FLASH_DEVICE_RAM,
                .name = "device 2",
                .author = "flechazo",
                .address = 0x810000,
                .length = 1024 * 5,
                .blocksize = 1024,
                .writeminunit = 1,
                .version = 1,
                .verify = 0,
                .reserve = {0xFF}
            },
            .info = 
            {
                .sizepage = 
                {
                    .id = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC},
                    .type = CC_FLASH_DEVICE_PAGE_TYPE_SIZE,
                    .totlesize = 1024 * 5,
                    .usesize = 0,
                    .verify = 0,
                },
                .cataloguepage = 
                {
                    .id = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC},
                    .type = CC_FLASH_DEVICE_PAGE_TYPE_CATALOGUE,
                    .num = 1,
                    .name = "folder 2",
                    .infoaddr = 0x810000 + 1024,
                },
                .verifypage = 
                {
                    .id = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC},
                    .type = CC_FLASH_DEVICE_PAGE_TYPE_VERIFY,
                    .verify = 0,
                },
            },
            .status = CC_FLASH_DEVICE_STATUS_FREE,
            .func = 
            {
                cc_flash_device_cfg_init,
                cc_flash_device_cfg_read,
                cc_flash_device_cfg_write,
                cc_flash_device_cfg_erase
            },
            .list = {0}
        },
    }
};
/* init flag */
cc_boolean cc_flash_device_cfg_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_flash_device_cfg_init()
****************************************************************************************************/
cc_result cc_flash_device_cfg_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init flash_device_cfg */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getnum()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getnum(cc_uint32 *num)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,num);
        /* output */
        *num = CC_FLASH_DEVICE_END;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getname()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getname(cc_uint32 ctrlidx,cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,name);
        /* output */
        cc_mem_strncpy(name,cc_flash_device_cfg_t.devices[ctrlidx].attribute.name,CC_NAME_MAX_LEN);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getinfoaddr()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getinfoaddr(cc_uint32 ctrlidx,cc_uint32 *infoaddr)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,infoaddr);
        /* output */
        *infoaddr = cc_flash_device_cfg_t.devices[ctrlidx].attribute.address;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_gettotlesize()
****************************************************************************************************/
cc_result cc_flash_device_cfg_gettotlesize(cc_uint32 ctrlidx,cc_uint32 *totlesize)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,totlesize);
        /* output */
        *totlesize = cc_flash_device_cfg_t.devices[ctrlidx].info.sizepage.totlesize;
        ____________________________TO_DO__________________________
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getusesize()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getusesize(cc_uint32 ctrlidx,cc_uint32 *usesize)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,usesize);
        /* output */
        *usesize = cc_flash_device_cfg_t.devices[ctrlidx].info.sizepage.usesize;
        /* find usesize from size page */
        ____________________________TO_DO__________________________
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getfunc()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getfunc(cc_uint32 ctrlidx,cc_flash_device_func_struct *func)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,func);
        /* output */
        *func = cc_flash_device_cfg_t.devices[ctrlidx].func;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getattributepage()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getattributepage(cc_uint32 ctrlidx,cc_flash_device_attribute_struct **attributepage)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,attributepage);
        /* output */
        *attributepage = &cc_flash_device_cfg_t.devices[ctrlidx].attribute;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getsizepage()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getsizepage(cc_uint32 ctrlidx,cc_flash_device_info_size_struct **sizepage)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,sizepage);
        /* output */
        *sizepage = &cc_flash_device_cfg_t.devices[ctrlidx].info.sizepage;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getcataloguepage()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getcataloguepage(cc_uint32 ctrlidx,cc_flash_device_info_catalogue_struct **cataloguepage)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,cataloguepage);
        /* output */
        *cataloguepage = &cc_flash_device_cfg_t.devices[ctrlidx].info.cataloguepage;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_getverifypage()
****************************************************************************************************/
cc_result cc_flash_device_cfg_getverifypage(cc_uint32 ctrlidx,cc_flash_device_info_verify_struct **verifypage)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,verifypage);
        /* output */
        *verifypage = &cc_flash_device_cfg_t.devices[ctrlidx].info.verifypage;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_read()
****************************************************************************************************/
cc_result cc_flash_device_cfg_read(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_write()
****************************************************************************************************/
cc_result cc_flash_device_cfg_write(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_erase()
****************************************************************************************************/
cc_result cc_flash_device_cfg_erase(cc_uint32 address,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_cfg_mainfunction()
****************************************************************************************************/
cc_result cc_flash_device_cfg_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File flash_device_cfg.c End!
****************************************************************************************************/

