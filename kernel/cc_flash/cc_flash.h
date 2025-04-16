
/****************************************************************************************************
* File cc_flash.h Start!
****************************************************************************************************/

#ifndef _CC_FLASH_H
#define _CC_FLASH_H

/****************************************************************************************************
*                        device1 -> folder1 -> folder11 -> file1
*  (flash)              /         \          \           \
* cc_flash -> devices ->            folder2    folder12    file2
*                       \
*                        device2
* read(cc_uint8 *buffer,cc_uint32 bufferlen,cc_int8 *path);
*                        "flash/device1/folder1/folder11/file1"
* 
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
#include "cc_flash_device.h"
/* components */
#include "cc_service.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/* page header */
#define CC_FLASH_PAGE_HEADER_LEN (12u)
#define CC_FLASH_PAGE_HEADER_ID_LEN (8u)

/* version */
#define CC_FLASH_VERSION (0x00000000)

/* deep */
#define CC_FLASH_CATALOGUE_DEEP (8u)

/****************************************************************************************************
* Type
****************************************************************************************************/

/* cc_flash_storage_type_enum */
typedef enum
{
    CC_FLASH_STORAGE_TYPE_FILE = 0,
    CC_FLASH_STORAGE_TYPE_FOLDER,
    CC_FLASH_STORAGE_TYPE_END
}cc_flash_storage_type_enum;

/* cc_flash_page_type_enum */
typedef enum
{
    CC_FLASH_PAGE_TYPE_MAIN = 0,
    CC_FLASH_PAGE_TYPE_SIZE,
    CC_FLASH_PAGE_TYPE_DEVICE,
    CC_FLASH_PAGE_TYPE_VERIFY,
    CC_FLASH_PAGE_TYPE_END
}cc_flash_page_type_enum;

/* ---------------------------------------------------------------------------------------------------
*  | 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 |
*  |-------------------------------------------------------------------------------------------------|----------------
*  > page 1
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          flash header  (main page 1 )                           | <96 Byte>
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          id[1]                                                  | 8 Byte     ^
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          type[1]                                                | 4 Byte     |
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
*  |                                          information[1]                                         | 16 Byte    |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          version[1]                                             | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          verify[1]                                              | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          reserve[1]                                             | 28 Byte    |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            v
*  |-------------------------------------------------------------------------------------------------|----------------
*  > page 2
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
*  > page 3
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          devices header   (sub page 2)                          | <12 + 32*n Byte>
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          id[1]                                                  | 8 Byte     ^
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          type[1]                                                | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          devicesnum[n]                                          | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          name[n]                                                | 16 Byte    |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          device type[n]                                         | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          device info address[n]                                 | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          verify[1]                                              | 4 Byte     v
*  |-------------------------------------------------------------------------------------------------|----------------
*  > page 4
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          crc header   (sub page 3)                              | <12+ 4*n Byte>
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          id[1]                                                  | 8 Byte     ^
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          type[1]                                                | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          verify[1]                                              | 4 Byte     v
*  |-------------------------------------------------------------------------------------------------|----------------
*/

/* header */
typedef struct
{
    /* size: 8 + 4 */
    /* header */
    cc_uint8 id[CC_FLASH_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_page_type_enum type;
}cc_flash_info_header_struct;

/* main page size */
#define CC_FLASH_INFO_MAIN_PAGE_SIZE (CC_FLASH_PAGE_HEADER_ID_LEN+\
                                      sizeof(cc_flash_page_type_enum)+\
                                      CC_NAME_MAX_LEN+\
                                      CC_NAME_MAX_LEN+\
                                      CC_NAME_MAX_LEN+\
                                      sizeof(cc_uint32)+\
                                      sizeof(cc_uint32)+\
                                      28)
#define CC_FLASH_INFO_MAIN_PAGE_ITEM_SIZE (CC_FLASH_INFO_MAIN_PAGE_SIZE)
/* main page */
typedef struct
{
    /* info page size: 8 + 4 + 16 + 16 + 16 + 4 + 4 + 28 = 96 */
    /* header */
    cc_uint8 id[CC_FLASH_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_page_type_enum type;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* author */
    cc_int8 author[CC_NAME_MAX_LEN];
    /* information */
    cc_int8 information[CC_NAME_MAX_LEN];
    /* version */
    cc_uint32 version;
    /* verify */
    cc_uint32 verify;
    /* reserve */
    cc_uint8 reserve[28];
}cc_flash_info_main_struct;

/* size page size */
#define CC_FLASH_INFO_SIZE_PAGE_SIZE (CC_FLASH_PAGE_HEADER_ID_LEN+\
                                      sizeof(cc_flash_page_type_enum)+\
                                      sizeof(cc_uint32)+\
                                      sizeof(cc_uint32)+\
                                      sizeof(cc_uint32))
#define CC_FLASH_INFO_SIZE_PAGE_ITEM_SIZE (sizeof(cc_uint32)+\
                                           sizeof(cc_uint32)+\
                                           sizeof(cc_uint32))
/* size page */
typedef struct
{
    /* info page size: 8 + 4 + (4 + 4 + 4) * n = 12 + 12*n */
    /* header */
    cc_uint8 id[CC_FLASH_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_page_type_enum type;
    /* size */
    cc_uint32 totlesize;
    cc_uint32 usesize;
    /* verify */
    cc_uint32 verify;
}cc_flash_info_size_struct;

/* devices page size */
#define CC_FLASH_INFO_DEVICES_PAGE_SIZE (CC_FLASH_PAGE_HEADER_ID_LEN+\
                                         sizeof(cc_flash_page_type_enum)+\
                                         sizeof(cc_uint32)+\
                                         (sizeof(cc_flash_info_devices_item_struct) * CC_FLASH_DEVICE_END)+\
                                         sizeof(cc_uint32))
#define CC_FLASH_INFO_DEVICES_PAGE_ITEM_SIZE (sizeof(cc_uint32)+\
                                              (sizeof(cc_flash_info_devices_item_struct) * CC_FLASH_DEVICE_END)+\
                                              sizeof(cc_uint32))
/* devices page */
typedef struct
{
    /* device name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* device type */
    cc_flash_device_enum devicetype;
    /* decive info address */
    cc_uint32 infoaddr;
}cc_flash_info_devices_item_struct;

typedef struct
{
    /* info page size: 8 + 4 + (4 + 16 + 4 + 4)* n = 12 + 28*n */
    /* header */
    cc_uint8 id[CC_FLASH_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_page_type_enum type;
    /* devices num */
    cc_uint32 num;
    /* device item */
    cc_flash_info_devices_item_struct item[CC_FLASH_DEVICE_END];
    /* verify */
    cc_uint32 verify;
}cc_flash_info_devices_struct;

/* verify page size */
#define CC_FLASH_INFO_VERIFY_PAGE_SIZE (CC_FLASH_PAGE_HEADER_ID_LEN+\
                                        sizeof(cc_flash_page_type_enum)+\
                                        sizeof(cc_uint32))
#define CC_FLASH_INFO_VERIFY_PAGE_ITEM_SIZE (sizeof(cc_uint32))
/* verify page */
typedef struct
{
    /* info page size: 8 + 4 + 4 * n = 12 + 4*n */
    /* header */
    cc_uint8 id[CC_FLASH_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_page_type_enum type;
    /* verify */
    cc_uint32 verify;
}cc_flash_info_verify_struct;

/* cc_flash_info_struct */
typedef struct
{
    /* main */
    cc_flash_info_main_struct mainpage;
    /* size */
    cc_flash_info_size_struct sizepage;
    /* devices */
    cc_flash_info_devices_struct devpage;
    /* verify */
    cc_flash_info_verify_struct verifypage;
}cc_flash_info_struct;

/* cc_flash */
typedef struct
{
    cc_result (*read)(cc_int8 *path,cc_uint8 *buffer,cc_uint32 length);
    cc_result (*write)(cc_int8 *path,cc_uint8 *buffer,cc_uint32 length);
    cc_result (*erase)(cc_flash_storage_type_enum type,cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen);
    cc_result (*erase_folder)(cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen);
    cc_result (*erase_file)(cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen);
    cc_result (*create)(cc_flash_storage_type_enum type,cc_int8 *path,cc_int8 *name);
    cc_result (*delete)(cc_flash_storage_type_enum type,cc_int8 *path);
    cc_result (*create_folder)(cc_int8 *path,cc_int8 *name);
    cc_result (*delete_folder)(cc_int8 *path);
    cc_result (*create_file)(cc_int8 *path,cc_int8 *name);
    cc_result (*delete_file)(cc_int8 *path);
}cc_flash_func_struct;

/* cc_flash */
typedef struct
{
    /* inherit object */
    cc_object_struct object;
    /* service */
    cc_service_struct service;
    /* header info */
    cc_flash_info_struct info;
    /* devices */
    cc_flash_device_struct devices;
    /* func */
    cc_flash_func_struct func;
}cc_flash_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_flash_init(cc_void);
cc_result cc_flash_get_headerid(cc_uint8 *header);
cc_result cc_flash_read(cc_int8 *path,cc_uint8 *buffer,cc_uint32 *length);
cc_result cc_flash_write(cc_int8 *path,cc_uint8 *buffer,cc_uint32 length);
cc_result cc_flash_erase(cc_flash_storage_type_enum type,cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen);
cc_result cc_flash_erase_folder(cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen);
cc_result cc_flash_erase_file(cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen);
cc_result cc_flash_create(cc_flash_storage_type_enum type,cc_int8 *path,cc_int8 *name);
cc_result cc_flash_delete(cc_flash_storage_type_enum type,cc_int8 *path);
cc_result cc_flash_create_folder(cc_int8 *path,cc_int8 *name);
cc_result cc_flash_delete_folder(cc_int8 *path);
cc_result cc_flash_create_file(cc_int8 *path,cc_int8 *name);
cc_result cc_flash_delete_file(cc_int8 *path);
cc_result cc_flash_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);
cc_result cc_flash_mainfunction(cc_void);

#endif /* _CC_FLASH_H */
/****************************************************************************************************
* File cc_flash.h End!
****************************************************************************************************/

