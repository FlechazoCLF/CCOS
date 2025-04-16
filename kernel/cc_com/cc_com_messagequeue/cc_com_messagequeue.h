
/****************************************************************************************************
* File com_messagequeue.h Start!
****************************************************************************************************/

#ifndef _COM_MESSAGEQUEUE_H
#define _COM_MESSAGEQUEUE_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
/* components */
#include "cc_service.h"
#include "cc_lock.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type
****************************************************************************************************/

/* cc_com_messagequeue_state */
typedef enum
{
    CC_QUEUE_STATE_UNINIT = 0,
    CC_QUEUE_STATE_INIT,
    CC_QUEUE_STATE_WAIT,
    CC_QUEUE_STATE_READ,
    CC_QUEUE_STATE_READEND,
    CC_QUEUE_STATE_WRITE,
    CC_QUEUE_STATE_WRITEEND,
    CC_QUEUE_STATE_SET,
    CC_QUEUE_STATE_FREE,
    CC_QUEUE_STATE_END
}cc_com_messagequeue_state_enum;

/* cc_queue_operate */
typedef struct
{
    cc_void *readpointer;
    cc_void *writepointer;
    cc_uint32 length;
    cc_uint32 uselength;
}cc_com_messagequeue_operate_struct;

/* cc_com_messagequeue_item_struct */
typedef struct
{
    /* ctrlidx */
    cc_uint8 ctrlidx;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* status */
    cc_com_messagequeue_state_enum state;
    /* buffer pointer */
    cc_void *buffer;
    cc_uint32 length;
    /* operate */
    cc_com_messagequeue_operate_struct operate;
    /* mutex lock */
    cc_lock_struct *lock;
    /* callback */
    cc_result (*callback)(cc_int8 *name,cc_com_messagequeue_state_enum state);
    /* queue list */
    cc_list_struct list;
}cc_com_messagequeue_item_struct;

/* cc_com_messagequeue */
typedef struct cc_com_messagequeue_struct_T
{
    /* inherit object */
    cc_object_struct object;
    /* service */
    cc_service_struct service;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* func */
    ____________________________TO_DO__________________________
    /* item */
    cc_com_messagequeue_item_struct item;
}cc_com_messagequeue_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_com_messagequeue_init(cc_void);
cc_result cc_com_messagequeue_mainfunction(cc_void);
cc_result cc_com_messagequeue_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);

#endif /* _COM_MESSAGEQUEUE_H */
/****************************************************************************************************
* File com_messagequeue.h End!
****************************************************************************************************/

