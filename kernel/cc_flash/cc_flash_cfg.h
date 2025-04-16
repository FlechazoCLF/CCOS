
/****************************************************************************************************
* File cc_flash_cfg.h Start!
****************************************************************************************************/

#ifndef _CC_FLASH_CFG_H
#define _CC_FLASH_CFG_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
/* components */

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/* page size */
#define CC_FLASH_CFG_PAGE_SIZE (1024u)
/* start address */
#define CC_FLASH_CFG_START_ADDRESS (0x800000)
/* need 4 * page */

/****************************************************************************************************
* Type
****************************************************************************************************/

/* cc_flash_cfg */
typedef struct
{
    /* func */
    cc_result (*init)(cc_void);
    cc_result (*read)(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length);
    cc_result (*write)(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length);
    cc_result (*erase)(cc_uint32 address,cc_uint32 length);
    /* page content */
    cc_uint8 pagecontent[CC_FLASH_CFG_PAGE_SIZE];
}cc_flash_cfg_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_flash_cfg_init(cc_void);
cc_result cc_flash_cfg_getstartaddr(cc_uint32 *address);
cc_result cc_flash_cfg_getpagesize(cc_uint32 *pagesize);
cc_result cc_flash_cfg_getpageitemsize(cc_flash_page_type_enum page,cc_uint32 *itemsize);
cc_result cc_flash_cfg_getpagecontent(cc_uint32 **address);
cc_result cc_flash_cfg_servicecall(cc_uint8 *data,cc_uint16 len);
cc_result cc_flash_cfg_read(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length);
cc_result cc_flash_cfg_write(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length);
cc_result cc_flash_cfg_erase(cc_uint32 address,cc_uint32 length);
cc_result cc_flash_cfg_mainfunction(cc_void);

#endif /* _CC_FLASH_CFG_H */
/****************************************************************************************************
* File cc_flash_cfg.h End!
****************************************************************************************************/

