
/****************************************************************************************************
* File cc_flash_catalogue.c Start!
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
 * 2025-04-12     cc          the first version
 *
*/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_flash_catalogue.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */
#include "cc_mem.h"
#include "cc_flash_catalogue_file.h"

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

/* cc_flash_catalogue */
cc_flash_catalogue_struct cc_flash_catalogue_t;
/* init flag */
cc_boolean cc_flash_catalogue_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_flash_catalogue_init()
****************************************************************************************************/
cc_result cc_flash_catalogue_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init cc_flash_catalogue */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_catalogue_get()
****************************************************************************************************/
cc_result cc_flash_catalogue_get(cc_flash_catalogue_struct **catalogue,cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_catalogue_get_child()
****************************************************************************************************/
cc_result cc_flash_catalogue_get_child(cc_flash_catalogue_struct **catalogue,cc_flash_catalogue_struct *parent,cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_catalogue_read()
****************************************************************************************************/
cc_result cc_flash_catalogue_read(cc_int8 *name,cc_int8 *path,cc_uint8 *buffer,cc_uint32 *length)
{
    cc_result result = CC_E_OK;
    cc_flash_catalogue_struct *catalogue;
    cc_int8 cataloguename[CC_NAME_MAX_LEN];
    cc_int8 *cataloguepath;
    cc_uint8 *fileaddress;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,path);
        CHECK_PTR(result,buffer);
        CHECK_PTR(result,length);
        /* impletement */
        /* get catalogue */
        cc_flash_catalogue_get(&catalogue,name);
        /* get path */
        cataloguepath = path;
        /* type */
        switch (catalogue->type)
        {
        case CC_FLASH_CATALOGUE_FILE:
            {
                /* check is file */
            }
            break;
        case CC_FLASH_CATALOGUE_FLODER:
            {
                /* get catalogue name */
                while (cc_mem_strtok(&cataloguename,&cataloguepath,"/") == CC_E_OK)
                {
                    /* into catalogue */
                    cc_flash_catalogue_get_child(&catalogue,catalogue,cataloguename);
                }
            }
            break;
        default:
            break;
        }
        /* get file name */
        cc_flash_catalogue_get_child(&catalogue,catalogue,cataloguepath);
        /* check file */
        CHECK_LOGIC(result,(catalogue->type == CC_FLASH_CATALOGUE_FILE));
        /* read */
        cc_flash_catalogue_file_read(catalogue,buffer,length);
        /* output */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_catalogue_mainfunction()
****************************************************************************************************/
cc_result cc_flash_catalogue_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_flash_catalogue.c End!
****************************************************************************************************/

