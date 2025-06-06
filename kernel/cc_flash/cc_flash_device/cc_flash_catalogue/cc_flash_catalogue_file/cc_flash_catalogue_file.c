
/****************************************************************************************************
* File cc_flash_catalogue_file.c Start!
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
#include "cc_flash_catalogue_file.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */
#include "cc_flash_catalogue.h"
#include "cc_flash_device_cfg.h"

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

/* cc_flash_catalogue_file */
cc_flash_catalogue_file_struct cc_flash_catalogue_file_t;
/* init flag */
cc_boolean cc_flash_catalogue_file_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_flash_catalogue_file_init()
****************************************************************************************************/
cc_result cc_flash_catalogue_file_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init object */

        /* register object */


        /* init cc_flash_catalogue_file */


        /* init service */

        /* register service */


        /* start service */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_catalogue_file_read()
****************************************************************************************************/
cc_result cc_flash_catalogue_file_read(cc_flash_catalogue_struct *catalogue,cc_uint8 *buffer,cc_uint32 *length)
{
    cc_result result = CC_E_OK;
    cc_flash_device_func_struct func;
    cc_flash_catalogue_struct iterator;
    cc_uint32 bufferlen;
    cc_uint32 address;
    cc_uint32 len;

    do
    {
        /* check parameter */
        CHECK_PTR(result,catalogue);
        CHECK_PTR(result,buffer);
        CHECK_PTR(result,length);
        /* impletement */
        /* get func */
        cc_flash_device_cfg_getfunc(catalogue->devicectrlidx,&func);
        /* check func */
        CHECK_PTR(result,func.read);
        /* check file */
        ____________________________TO_DO__________________________
        /* read */
        bufferlen = *length;
        *length = 0;
        address = catalogue->info.curaddr;
        func.read(&iterator,address,CC_FLASH_CATALOGUE_SIZE);
        /* iterator */
        while (bufferlen > CC_NULL)
        {
            /* check */

            /* read */
            len = iterator.info.item.file.length;
            address = iterator.info.curaddr;
            func.read((buffer + (*length)),address,len);
            *length += len;

            /* next */
            if(iterator.info.nextaddr == CC_NULL)
            {
                break;
            }

            /* next */
            address = iterator.info.nextaddr;
            /* read catalogue */
            func.read(&iterator,address,CC_FLASH_CATALOGUE_SIZE);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_catalogue_file_mainfunction()
****************************************************************************************************/
cc_result cc_flash_catalogue_file_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_flash_catalogue_file.c End!
****************************************************************************************************/

