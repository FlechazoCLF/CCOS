
/****************************************************************************************************
* File queue.h Start!
****************************************************************************************************/

#ifndef _QUEUE_H
#define _QUEUE_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* kernel */
#include "cc_lock.h"
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

/* cc_queue_state */
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
}cc_queue_state_enum;

/* cc_queue_operate */
typedef struct
{
    cc_void *readpointer;
    cc_void *writepointer;
    cc_uint32 length;
    cc_uint32 uselength;
}cc_queue_operate_struct;

/* cc_queue */
typedef struct cc_queue_struct_T
{
    /* ctrlidx */
    cc_uint8 ctrlidx;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* status */
    cc_queue_state_enum state;
    /* buffer pointer */
    cc_void *buffer;
    cc_uint32 length;
    /* operate */
    cc_queue_operate_struct operate;
    /* mutex lock */
    cc_lock_struct *lock;
    /* callback */
    cc_result (*callback)(cc_int8 *name,cc_queue_state_enum state);
    /* queue list */
    cc_list_struct list;
}cc_queue_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_queue_init(cc_void);
cc_result cc_queue_mainfunction(cc_void);

#endif /* _QUEUE_H */
/****************************************************************************************************
* File queue.h End!
****************************************************************************************************/

