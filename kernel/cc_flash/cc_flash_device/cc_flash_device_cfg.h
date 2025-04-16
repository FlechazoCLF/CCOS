
/****************************************************************************************************
* File flash_device_cfg.h Start!
****************************************************************************************************/

#ifndef _FLASH_DEVICE_CFG_H
#define _FLASH_DEVICE_CFG_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
#include "cc_flash_device.h"
/* log */
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

/* cc_flash_device_cfg */
typedef struct
{
    cc_uint8 id;
    /* devices */
    cc_flash_device_struct devices[CC_FLASH_DEVICE_END];
}cc_flash_device_cfg_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_flash_device_cfg_init(cc_void);
cc_result cc_flash_device_cfg_getnum(cc_uint32 *num);
cc_result cc_flash_device_cfg_getname(cc_uint32 ctrlidx,cc_int8 *name);
cc_result cc_flash_device_cfg_getinfoaddr(cc_uint32 ctrlidx,cc_uint32 *infoaddr);
cc_result cc_flash_device_cfg_gettotlesize(cc_uint32 ctrlidx,cc_uint32 *totlesize);
cc_result cc_flash_device_cfg_getusesize(cc_uint32 ctrlidx,cc_uint32 *usesize);
cc_result cc_flash_device_cfg_getfunc(cc_uint32 ctrlidx,cc_flash_device_func_struct *func);
cc_result cc_flash_device_cfg_getattributepage(cc_uint32 ctrlidx,cc_flash_device_attribute_struct **attributepage);
cc_result cc_flash_device_cfg_getsizepage(cc_uint32 ctrlidx,cc_flash_device_info_size_struct **sizepage);
cc_result cc_flash_device_cfg_getcataloguepage(cc_uint32 ctrlidx,cc_flash_device_info_catalogue_struct **cataloguepage);
cc_result cc_flash_device_cfg_getverifypage(cc_uint32 ctrlidx,cc_flash_device_info_verify_struct **verifypage);

cc_result cc_flash_device_cfg_read(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length);
cc_result cc_flash_device_cfg_write(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length);
cc_result cc_flash_device_cfg_erase(cc_uint32 address,cc_uint32 length);

cc_result cc_flash_device_cfg_mainfunction(cc_void);

#endif /* _FLASH_DEVICE_CFG_H */
/****************************************************************************************************
* File flash_device_cfg.h End!
****************************************************************************************************/

