
/****************************************************************************************************
* File key.h Start!
****************************************************************************************************/

#ifndef _KEY_H
#define _KEY_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
/* components */
#include "cc_service.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type
****************************************************************************************************/

/* cc_key_item_type_enum */
typedef enum{
    CC_KEY_ITEM_TYPE_PRESS,
    CC_KEY_ITEM_TYPE_KNOCK,
    CC_KEY_ITEM_TYPE_END
}cc_key_item_type_enum;

/* cc_key_item_triggermode_enum */
typedef enum{
    CC_KEY_ITEM_TRIGGERMODE_HIGH_TO_LOW,
    CC_KEY_ITEM_TRIGGERMODE_LOW_TO_HIGH,
    CC_KEY_ITEM_TRIGGERMODE_END
}cc_key_item_triggermode_enum;

/* cc_key_item_status_enum */
typedef enum
{
    CC_KEY_ITEM_STATUS_FREE = 0,
    CC_KEY_ITEM_STATUS_TRIGGER,
    CC_KEY_ITEM_STATUS_CHECKVALID,
    CC_KEY_ITEM_STATUS_DOUBLECLICK,
    CC_KEY_ITEM_STATUS_CLICK,
    CC_KEY_ITEM_STATUS_LONGPRESS,
    CC_KEY_ITEM_STATUS_END
}cc_key_item_status_enum;

/* cc_key_item_status_struct */
typedef struct
{
    /* status */
    cc_key_item_status_enum value;
    /* time */
    cc_uint32 time;
}cc_key_item_status_struct;

/* cc_key_item_struct */
typedef struct
{
    /* ctrlidx */
    cc_uint32 ctrlidx;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* type */
    cc_key_item_type_enum type;
    /* trigger mode */
    cc_key_item_triggermode_enum triggermode;
    /* shake off time */
    cc_uint32 shakeofftime;
    /* status */
    cc_key_item_status_struct status;
    /* key list */
    cc_list_struct list;
}cc_key_item_struct;

/* cc_key_func_struct */
typedef struct
{
    cc_result (*init)(cc_void);
}cc_key_func_struct;

/* cc_key */
typedef struct
{
    /* inherit object */
    cc_object_struct object;
    /* service */
    cc_service_struct service;
    /* func */
    cc_key_func_struct func;
    /* item */
    cc_key_item_struct item;
}cc_key_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_key_init(cc_void);
cc_result cc_mem_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);
cc_result cc_key_mainfunction(cc_void);

#endif /* _KEY_H */
/****************************************************************************************************
* File key.h End!
****************************************************************************************************/

