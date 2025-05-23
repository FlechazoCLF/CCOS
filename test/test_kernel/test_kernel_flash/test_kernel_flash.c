
/****************************************************************************************************
* File test_kernel_flash.c Start!
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
 * 2025-04-21     cc          the first version
 *
*/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
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

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* test_kernel_flash_init()
****************************************************************************************************/
cc_result test_kernel_flash_init(cc_void)
{
    cc_result result = CC_E_OK;
    cc_uint8 buffer[256] = {0};
    cc_uint32 length = 0;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);
        /* init flash */
        cc_flash_init();
        /* read */
        cc_flash_read("flash/test/file",buffer,&length);
    }while(0u);

    return result;
}


/****************************************************************************************************
* File test_kernel_flash.c End!
****************************************************************************************************/
