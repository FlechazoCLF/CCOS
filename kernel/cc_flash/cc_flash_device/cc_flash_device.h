
/****************************************************************************************************
* File flash_device.h Start!
****************************************************************************************************/

#ifndef _FLASH_DEVICE_H
#define _FLASH_DEVICE_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
/* components */
#include "cc_flash_catalogue.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/* page header */
#define CC_FLASH_DEVICE_PAGE_HEADER_LEN (12u)
#define CC_FLASH_DEVICE_PAGE_HEADER_ID_LEN (8u)

/****************************************************************************************************
* Type
****************************************************************************************************/

/* cc_flash_device_enum */
typedef enum
{
    CC_FLASH_DEVICE_RAM = 0,
    CC_FLASH_DEVICE_FLASH,
    CC_FLASH_DEVICE_GD25Q64,
    CC_FLASH_DEVICE_END,
}cc_flash_device_enum;

/* cc_flash_device_status_enum */
typedef enum
{
    CC_FLASH_DEVICE_STATUS_FREE = 0,
    CC_FLASH_DEVICE_STATUS_READ,
    CC_FLASH_DEVICE_STATUS_WRITE,
    CC_FLASH_DEVICE_STATUS_END,
}cc_flash_device_status_enum;

/* cc_flash_device_func_struct */
typedef struct
{
    cc_result (*init)(cc_void);
    cc_result (*read)(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length);
    cc_result (*write)(cc_uint8 *buffer,cc_uint32 address,cc_uint32 length);
    cc_result (*erase)(cc_uint32 address,cc_uint32 length);
}cc_flash_device_func_struct;


/* ---------------------------------------------------------------------------------------------------
*  | 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 |
*  |-------------------------------------------------------------------------------------------------|----------------
*  > page 1
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          device attribute header  (attribute page)              | <96 Byte>          
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          id[1]                                                  | 8 Byte     ^
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          type[1]                                                | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          device type[1]                                         | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          name[1]                                                | 16 Byte    |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          author[1]                                              | 16 Byte    |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          address[1]                                             | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          length[1]                                              | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          blocksize[1]                                           | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          writeminunit[1]                                        | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          version[1]                                             | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          verify[1]                                              | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          reserve[1]                                             | 24 Byte    |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            v
*  |-------------------------------------------------------------------------------------------------|----------------
*  > size
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          size header   (sub page 1)                             | <12 + 12*n Byte>
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          id[1]                                                  | 8 Byte     ^
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          type[1]                                                | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          totlesize[n]                                           | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          usesize[n]                                             | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          verify[1]                                              | 4 Byte     v
*  |-------------------------------------------------------------------------------------------------|----------------
*  > catalogue
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          catalogue header   (sub page 2)                        | <12 + 28*n Byte>          
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          id[1]                                                  | 8 Byte     ^
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          type[1]                                                | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          num[n]                                                 | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          name[n]                                                | 16 Byte    |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          catalogue info address[n]                              | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          verify[1]                                              | 4 Byte     v
*  |-------------------------------------------------------------------------------------------------|----------------
*  > verify
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          crc header   (sub page 3)                              | <12+ 4*n Byte>          
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          id[1]                                                  | 8 Byte     ^
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          type[1]                                                | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          devicesnum[n]                                          | 4 Byte     v
*  |-------------------------------------------------------------------------------------------------|----------------
*/

/* cc_flash_device_page_type_enum */
typedef enum
{
    CC_FLASH_DEVICE_PAGE_TYPE_ATTRIBUTE = 0,
    CC_FLASH_DEVICE_PAGE_TYPE_SIZE,
    CC_FLASH_DEVICE_PAGE_TYPE_CATALOGUE,
    CC_FLASH_DEVICE_PAGE_TYPE_VERIFY,
    CC_FLASH_DEVICE_PAGE_TYPE_END
}cc_flash_device_page_type_enum;

/* header */
typedef struct
{
    /* size: 8 + 4 */
    /* header */
    cc_uint8 id[CC_FLASH_DEVICE_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_device_page_type_enum type;
}cc_flash_device_header_struct;

/* cc_flash_device_attribute_struct */
typedef struct
{
    /* header id */
    cc_uint8 id[CC_FLASH_DEVICE_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_device_page_type_enum type;
    /* device type */
    cc_flash_device_enum devicetype;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* author */
    cc_int8 author[CC_NAME_MAX_LEN];
    /* address */
    cc_uint32 address;
    /* length */
    cc_uint32 length;
    /* block */
    cc_uint32 blocksize;
    /* write min unit */
    cc_uint32 writeminunit;
    /* version */
    cc_uint32 version;
    /* verify */
    cc_uint32 verify;
    /* reserve */
    cc_uint8 reserve[24];
}cc_flash_device_attribute_struct;

/* cc_flash_device_info_size_struct */
typedef struct
{
    /* header id */
    cc_uint8 id[CC_FLASH_DEVICE_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_device_page_type_enum type;
    /* size */
    cc_uint32 totlesize;
    cc_uint32 usesize;
    /* verify */
    cc_uint32 verify;
}cc_flash_device_info_size_struct;

/* cc_flash_device_info_catalogue_struct */
typedef struct
{
    /* header id */
    cc_uint8 id[CC_FLASH_DEVICE_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_device_page_type_enum type;
    /* catalogue num */
    cc_uint32 num;
    /* catalogue name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* catalogue info address */
    cc_uint32 infoaddr;
    /* verify */
    cc_uint32 verify;
}cc_flash_device_info_catalogue_struct;

/* verify page */
typedef struct
{
    /* info page size: 8 + 4 + 4 * n = 12 + 4*n */
    /* header */
    cc_uint8 id[CC_FLASH_DEVICE_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_device_page_type_enum type;
    /* verify */
    cc_uint32 verify;
}cc_flash_device_info_verify_struct;

/* cc_flash_cfg_info_struct */
typedef struct
{
    /* size */
    cc_flash_device_info_size_struct sizepage;
    /* file / folder */
    cc_flash_device_info_catalogue_struct cataloguepage;
    /* verify */
    cc_flash_device_info_verify_struct verifypage;
}cc_flash_device_info_struct;

/* cc_flash_cfg */
typedef struct
{
    /* attribute */
    cc_flash_device_attribute_struct attribute;
    /* info */
    cc_flash_device_info_struct info;
    /* status */
    cc_flash_device_status_enum status;
    /* func */
    cc_flash_device_func_struct func;
    /* catalogue */
    cc_flash_catalogue_struct catalogue;
    /* list */
    cc_list_struct list;
}cc_flash_device_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_flash_device_init(cc_flash_device_struct *device);
cc_result cc_flash_device_page_init(cc_uint32 ctrlidx);
cc_result cc_flash_device_discover(cc_flash_device_struct *device,cc_int8 *name,cc_flash_device_enum devicetype,cc_uint32 address);
cc_result cc_flash_device_get(cc_flash_device_struct **device,cc_int8 *name);
cc_result cc_flash_device_read(cc_int8 *name,cc_int8 *path,cc_uint8 *buffer,cc_uint32 *length);
cc_result cc_flash_device_mainfunction(cc_void);

#endif /* _FLASH_DEVICE_H */
/****************************************************************************************************
* File flash_device.h End!
****************************************************************************************************/

