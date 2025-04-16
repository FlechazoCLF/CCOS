
/****************************************************************************************************
* File cc_timer.h Start!
****************************************************************************************************/
#ifndef _CC_TIMER_H
#define _CC_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"
#include "cc_service.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/* timer func ctrlidx */
typedef enum
{
    CC_TIMER_FUNCCTRLIDX_FREE = 0,
    CC_TIMER_FUNCCTRLIDX_INIT,
    CC_TIMER_FUNCCTRLIDX_DETACH,
    CC_TIMER_FUNCCTRLIDX_CREATE,
    CC_TIMER_FUNCCTRLIDX_DELETE,
    CC_TIMER_FUNCCTRLIDX_START,
    CC_TIMER_FUNCCTRLIDX_STOP,
    CC_TIMER_FUNCCTRLIDX_GETLOCALTIME,
    CC_TIMER_FUNCCTRLIDX_END
}cc_timer_funcctrlidx_enum;

/* number of func */
#define CC_TIMER_CFG_FUNCTABLE_NUM (CC_TIMER_FUNCCTRLIDX_END - 1)

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* timer type */
typedef enum
{
    CC_TIMER_ITEM_TYPE_CYCLE = 0,
    CC_TIMER_ITEM_TYPE_ONCE,
    CC_TIMER_ITEM_TYPE_END
}cc_timer_item_type_enum;

/* timer state */
typedef enum
{
    CC_TIMER_ITEM_STATE_INIT = 0,
    CC_TIMER_ITEM_STATE_START,
    CC_TIMER_ITEM_STATE_TRIGGER,
    CC_TIMER_ITEM_STATE_STOP,
    CC_TIMER_ITEM_STATE_END
}cc_timer_item_state_enum;

/* timer create type */
typedef enum
{
    CC_TIMER_CREATE_TYPE_HEAP = 0,
    CC_TIMER_CREATE_TYPE_MEM,
    CC_TIMER_CREATE_TYPE_END
}cc_timer_create_type_enum;

/* date */
typedef struct
{
    cc_uint32 year;/* 2025 */
    cc_uint32 month;/* 1~12 */
    cc_uint32 day;/* 1~31 */
    cc_uint32 hour;/* 0~24 */
    cc_uint32 minute;/* 0~60 */
    cc_uint32 second;
    cc_uint32 millisecond;
    cc_uint32 nanosecond;
    cc_uint64 tick;
}cc_timer_date_struct;

/* timeout precision */
typedef enum
{
    CC_TIMER_PRECISION_TICK = 0,
    CC_TIMER_PRECISION_NS,
    CC_TIMER_PRECISION_MS,
    CC_TIMER_PRECISION_S,
    CC_TIMER_PRECISION_MIN,
    CC_TIMER_PRECISION_HOUR,
    CC_TIMER_PRECISION_DAY,
    CC_TIMER_PRECISION_MONTH,
    CC_TIMER_PRECISION_YEAR,
    CC_TIMER_PRECISION_END
}cc_timer_precision_enum;

/* timer item */
typedef struct
{
    /* inherit object */
    cc_object_struct object;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* type */
    cc_timer_item_type_enum type;
    /* state */
    cc_timer_item_state_enum state;
    /* timeout */
    cc_uint32 time;
    cc_uint32 timeout;
    cc_timer_precision_enum precision;
    /* callback */
    cc_void (*callback)(cc_void *parameter);
    cc_void *parameter;
    /* list */
    cc_list_struct list;
}cc_timer_item_struct;

/* func */
typedef struct
{
    cc_result (*init)(cc_void);
}cc_timer_func_struct;

/* timer */
typedef struct
{
    /* inherit object */
    cc_object_struct object;
    /* service */
    cc_service_struct service;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* date */
    cc_timer_date_struct date;
    /* func */
    cc_timer_func_struct func;
    /* item */
    cc_timer_item_struct item;
}cc_timer_struct;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/
cc_result cc_timer_init(cc_void);
cc_result cc_timer_detach(cc_void);
cc_result cc_timer_create(cc_int8 *name,cc_timer_create_type_enum type,cc_timer_item_struct *item);
cc_result cc_timer_delete(cc_int8 *name);
cc_result cc_timer_start(cc_int8 *name);
cc_result cc_timer_stop(cc_int8 *name);
cc_result cc_timer_checktimeout(cc_void);
cc_result cc_timer_getlocaltime(cc_void);
cc_result cc_timer_dateupdate(cc_void);
cc_result cc_timer_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);
cc_result cc_timer_mainfunction(cc_void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_TIMER_H */
/****************************************************************************************************
* File cc_timer.h End!
****************************************************************************************************/

