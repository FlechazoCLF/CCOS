
/****************************************************************************************************
* File cc_lock.h Start!
****************************************************************************************************/
#ifndef _CC_LOCK_H
#define _CC_LOCK_H

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
* Type Define
****************************************************************************************************/

/* lock type */
typedef enum
{
    CC_LOCK_TYPE_NULL = 0,
    CC_LOCK_TYPE_SPINLOCK,
    CC_LOCK_TYPE_MUTEX,
    CC_LOCK_TYPE_SEMAPHORE,
    CC_LOCK_TYPE_END
}cc_lock_type_enum;

/* cc_lock_struct */
typedef struct
{
    /* inherit object */
    cc_object_struct object;
    /* service */
    cc_service_struct service;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* ctrlidx */
    cc_uint8 ctrlidx;
    /* type */
    cc_lock_type_enum type;
    /* value */
    cc_uint32 value;
    /* queue list */
    cc_list_struct list;
}cc_lock_struct;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

cc_result cc_lock_init(cc_void);
cc_result cc_lock_detach(cc_int8 *name);
cc_result cc_lock_getobject(cc_object_struct **object);
cc_result cc_lock_take(cc_int8 *name);
cc_result cc_lock_bring(cc_int8 *name);
cc_result cc_lock_create(cc_int8 *name,cc_lock_type_enum type,cc_lock_struct **lock);
cc_result cc_lock_delete(cc_int8 *name);
cc_result cc_lock_mainfunction(cc_void);


#endif /* _CC_LOCK_H */
/****************************************************************************************************
* File cc_lock.h End!
****************************************************************************************************/

