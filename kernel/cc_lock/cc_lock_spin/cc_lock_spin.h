
/****************************************************************************************************
* File lock_spin.h Start!
****************************************************************************************************/

#ifndef _LOCK_SPIN_H
#define _LOCK_SPIN_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
/* components */
#include "cc_list.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type
****************************************************************************************************/

/* lock state */
typedef enum
{
    CC_LOCK_SPIN_STATE_UNLOCK = 0,
    CC_LOCK_SPIN_STATE_LOCKED,
    CC_LOCK_SPIN_STATE_END
}cc_lock_spin_state_enum;

/* cc_lock_spin_item */
typedef struct
{
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* value */
    volatile cc_uint32 value;
    /* lock list */
    cc_list_struct list;
}cc_lock_spin_item_struct;

/* cc_lock_spin */
typedef struct
{
    /* inherit object */
    cc_object_struct object;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* value */
    volatile cc_uint32 value;
    /* lock */
    cc_lock_spin_item_struct item;
}cc_lock_spin_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_lock_spin_init(cc_void);
cc_result cc_lock_spin_create(cc_int8 *name);
cc_result cc_lock_spin_delete(cc_int8 *name);
cc_result cc_lock_spin_take(cc_int8 *name);
cc_result cc_lock_spin_wait(cc_int8 *name);
cc_result cc_lock_spin_bring(cc_int8 *name);
cc_result cc_lock_spin_mainfunction(cc_void);

#endif /* _LOCK_SPIN_H */
/****************************************************************************************************
* File lock_spin.h End!
****************************************************************************************************/

