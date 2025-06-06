
/****************************************************************************************************
* File cc_flash_catalogue.h Start!
****************************************************************************************************/

#ifndef _CC_FLASH_CATALOGUE_H
#define _CC_FLASH_CATALOGUE_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
/* components */
#include "cc_flash_catalogue_file.h"
#include "cc_flash_catalogue_folder.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/* default size of file / folder */
#define CC_FLASH_CATALOGUE_SIZE (256u)
/* page header */
#define CC_FLASH_CATALOGUE_PAGE_HEADER_LEN (12u)
#define CC_FLASH_CATALOGUE_PAGE_HEADER_ID_LEN (8u)

/****************************************************************************************************
* Type
****************************************************************************************************/

/* ---------------------------------------------------------------------------------------------------
*  | 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 |
*  |-------------------------------------------------------------------------------------------------|----------------
*  > page
*  |-------------------------------------------------------------------------------------------------|----------------
*  |                                          catalogue header  (attribute page)                     | <256 Byte>          
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
*  |                                          parent ctrlidx[1]                                      | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          info[1] folder / file                                  | 188 Byte   |
*  |                                          ...                                                    |            |
*  |                                          ...                                                    |            |
*  |                                                                                                 |            |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          prev address[1]                                        | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          current address[1]                                     | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          next address[1]                                        | 4 Byte     |
*  |-------------------------------------------------------------------------------------------------|-------     |
*  |                                          reserve[1]                                             | 32 Byte    |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            |
*  |                                                                                                 |            v
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

/* cc_flash_catalogue */
typedef enum
{
    CC_FLASH_CATALOGUE_NULL = 0,
    CC_FLASH_CATALOGUE_FILE,
    CC_FLASH_CATALOGUE_FLODER,
    CC_FLASH_CATALOGUE_END
}cc_flash_catalogue_enum;

/* cc_flash_catalogue_info_content_union */
typedef union
{
    /* size */
    cc_uint8 content[CC_FLASH_CATALOGUE_SIZE - CC_FLASH_CATALOGUE_PAGE_HEADER_ID_LEN - 4 - CC_NAME_MAX_LEN - 8 - 8];
    /* file info */
    cc_flash_catalogue_file_struct file;
    /* folder info */
    cc_flash_catalogue_folder_struct folder;
}cc_flash_catalogue_info_content_union;

/* cc_flash_catalogue_info_struct */
typedef struct
{
    /* file info */
    cc_flash_catalogue_info_content_union item;
    /* list */
    cc_uint32 prevaddr;
    cc_uint32 curaddr;
    cc_uint32 nextaddr;
    /* reserve */
    cc_uint8 reserve[32];
}cc_flash_catalogue_info_struct;

/* cc_flash_catalogue */
typedef struct
{
    /* header */
    cc_uint8 id[CC_FLASH_CATALOGUE_PAGE_HEADER_ID_LEN];
    /* type */
    cc_flash_catalogue_enum type;
    /* catalogue name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* parent */
    cc_uint32 devicectrlidx;
    /* info */
    cc_flash_catalogue_info_struct info;
    /* list */
    cc_list_struct list;
}cc_flash_catalogue_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_flash_catalogue_init(cc_void);
cc_result cc_flash_catalogue_read(cc_int8 *name,cc_int8 *path,cc_uint8 *buffer,cc_uint32 *length);
cc_result cc_flash_catalogue_mainfunction(cc_void);

#endif /* _CC_FLASH_CATALOGUE_H */
/****************************************************************************************************
* File cc_flash_catalogue.h End!
****************************************************************************************************/

