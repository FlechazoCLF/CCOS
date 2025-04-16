
/****************************************************************************************************
* File cc_scheduler.h Start!
****************************************************************************************************/
#ifndef _CC_SCHEDULER_H
#define _CC_SCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"
#include "cc_kernel_type.h"
#include "cc_thread.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* scheduler */
typedef struct
{
    /* parent */
    cc_kernel_struct *parent;
    /* scheduler inherit object */
    cc_object_struct object;
    /* scheduler name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* thread list */
    cc_list_struct thread_prioritylist[CC_THREAD_PRIORITY_MAX];
    /* priority mask */
    cc_uint32 thread_prioritymask;
}cc_scheduler_struct;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/
cc_result cc_scheduler_init(cc_void);
cc_result cc_scheduler_detach(cc_void);
cc_result cc_scheduler_start(cc_void);
cc_result cc_scheduler_stop(cc_void);
cc_result cc_scheduler_next(cc_void);
cc_result cc_scheduler_insert(cc_void);
cc_result cc_scheduler_remove(cc_void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_SCHEDULER_H */
/****************************************************************************************************
* File cc_scheduler.h End!
****************************************************************************************************/

