
/****************************************************************************************************
* File cc_thread.h Start!
****************************************************************************************************/
#ifndef _CC_THREAD_H
#define _CC_THREAD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"
#include "cc_kernel_type.h"

/****************************************************************************************************
* Define
****************************************************************************************************/
#define CC_THREAD_PRIORITY_MAX (32u)

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* thread type */
typedef enum
{
    CC_THREAD_TYPE_USER = 0,
    CC_THREAD_TYPE_IDLE,
    CC_THREAD_TYPE_KERNEL,
    CC_THREAD_TYPE_END
}cc_thread_type_enum;

/* thread state */
typedef enum
{
    CC_THREAD_STATE_UNINIT = 0,
    CC_THREAD_STATE_INIT,
    CC_THREAD_STATE_READY,
    CC_THREAD_STATE_RUNNING,
    CC_THREAD_STATE_BLOCK,
    CC_THREAD_STATE_WAIT,
    CC_THREAD_STATE_TERMINATE,
    CC_THREAD_STATE_END
}cc_thread_state_enum;

/* thread info */
typedef struct
{
    /* ctrlidx */
    cc_uint32 id;
    /* state */
    cc_thread_state_enum state;
    /* flag */
    ____________________________TO_DO__________________________
    /* error */
    ____________________________TO_DO__________________________
    /* cpu */
    cc_uint32 cpuid;
}cc_thread_info_struct;

/* thread scheduler type */
typedef enum
{
    CC_THREAD_SCHEDULER_TYPE_IDLE = 0,
    CC_THREAD_SCHEDULER_TYPE_END
}cc_thread_scheduler_type_enum;

/* thread scheduler */
typedef struct
{
    /* type */
    cc_thread_scheduler_type_enum type;
    /* block */
    cc_uint32 block;
    /* time */
    cc_uint32 time;
    /* tick */
    cc_uint32 tick;
    /* priority */
    cc_uint32 priority;
    cc_uint32 currentpriority;
}cc_thread_scheduler_struct;

/* thread signal */
typedef struct
{
    /* mutex */
    cc_uint32 mutex;
    /* event */
    cc_uint32 event;
    /* semaphore */
    cc_uint32 semaphore;
    /* signal */
    cc_uint32 signal;
}cc_thread_signal_struct;

/* thread context */
typedef struct
{
    /* stack pointer */
    void *stackptr;
    /* entry */
    void *entry;
    /* semaphore */
    void *parameter;
    /* stackaddress */
    void *stackadd;
    /* stacksize */
    cc_uint32 stacksize;
}cc_thread_context_struct;

/* thread interface */
typedef struct
{
    cc_result (*init)(void);
    /* send */
    ____________________________TO_DO__________________________
    /* recv */
    ____________________________TO_DO__________________________
}cc_thread_func_struct;

/* thread */
typedef struct
{
    /* parent */
    cc_kernel_struct *parent;
    /* thread inherit object */
    cc_object_struct object;
    /* thread name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* type */
    cc_thread_type_enum type;
    /* list */
    cc_list_struct list;
    /* info */
    cc_thread_info_struct info;
    /* scheduler */
    cc_thread_scheduler_struct scheduler;
    /* signal */
    cc_thread_signal_struct signal;
    /* context */
    cc_thread_context_struct context;
    /* func */
    cc_thread_func_struct func;
}cc_thread_struct;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/
cc_result cc_thread_init(cc_void);
cc_result cc_thread_detach(cc_int8 *name);
cc_result cc_thread_create(cc_void);
cc_result cc_thread_delete(cc_void);
cc_result cc_thread_suspend(cc_void);
cc_result cc_thread_resume(cc_void);
cc_result cc_thread_start(cc_void);
cc_result cc_thread_stop(cc_void);
cc_result cc_thread_idle_entry(cc_void *parameter);
cc_result cc_thread_exit(cc_void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_THREAD_H */
/****************************************************************************************************
* File cc_thread.h End!
****************************************************************************************************/

