
/****************************************************************************************************
* File lock_spin.c Start!
****************************************************************************************************/

/*
 *
 *  Copyright (c) 2024-2025 by flechazo. All rights reserved.
 *
 * Author : CarlChai LinFeng Chai flechazo
 * Website: flechazo.mba
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-03     cc          the first version
 *
*/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_lock_spin.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */
#include "cc_lock.h"
#include "cc_mem.h"
#include "cc_heap.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* cc_lock_spin */
cc_lock_spin_struct cc_lock_spin_t;
/* init flag */
cc_boolean cc_lock_spin_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_lock_spin_object_init()
****************************************************************************************************/
cc_result cc_lock_spin_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "spinlock obj";
    cc_int8 log[CC_LOG_MAX_LEN] = "spinlock obj init";

    do
    {
        /* check */
        CHECK_PTR(result,object);
        /* impletement */
        /* parent */
        cc_lock_getobject(&object->parent);
        /* name */
        cc_mem_strncpy(object->name,name,CC_NAME_MAX_LEN);
        /* id */
        object->id = CC_SERVICE_TYPE_LOCK;
        /* state */
        object->state = CC_OBJECT_STATE_UNINIT;
        /* type */
        object->type = CC_OBJECT_TYPE(CC_SERVICE);
        /* flag */
        object->flag = CC_OBJECT_FLAG_FREE;
        /* info */
        cc_mem_strncpy(object->info.log,log,CC_LOG_MAX_LEN);
        /* authority */
        object->authority = CC_OBJECT_AUTHORITY(CC_SERVICE);
        /* list */
        cc_list_init(&object->list);
        /* state */
        object->state = CC_OBJECT_STATE_INIT;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_item_init()
****************************************************************************************************/
cc_result cc_lock_spin_item_init(cc_lock_spin_item_struct *item)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "spinlock item";

    do
    {
        /* check */
        CHECK_PTR(result,item);
        /* name */
        cc_mem_strncpy(item->name,name,CC_NAME_MAX_LEN);
        /* init */
        item->value = CC_LOCK_SPIN_STATE_UNLOCK;
        /* list */
        cc_list_init(&item->list);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_internal_init()
****************************************************************************************************/
cc_result cc_lock_spin_internal_init(cc_lock_spin_struct *spinlock)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,spinlock);
        /* init */
        cc_lock_spin_item_init(&spinlock->item);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_init()
****************************************************************************************************/
cc_result cc_lock_spin_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_lock_spin_initflag != CC_TRUE));
        /* init object */
        cc_lock_spin_object_init(&cc_lock_spin_t.object);
        /* register object */
        cc_object_register(&cc_lock_spin_t.object);

        /* init */
        cc_lock_spin_internal_init(&cc_lock_spin_t);

        /* init flag */
        cc_lock_spin_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_find()
****************************************************************************************************/
cc_result cc_lock_spin_find(cc_int8 *name,cc_lock_spin_item_struct **item)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_lock_spin_item_struct *itemhead;
    cc_lock_spin_item_struct *iterator;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_lock_spin_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,item);

        /* check timer list */
        itemhead = &cc_lock_spin_t.item;
        iterator = itemhead;
        /* iterator */
        while((iterator != CC_NULL_PTR) && (iterator->list.next != &itemhead->list))
        {
            /* check name */
            if(cc_mem_strncmp(name,iterator->name,CC_NAME_MAX_LEN) == CC_E_OK)
            {
                /* set state */
                *item = iterator;
                result = CC_E_OK;
                break;
            }
            /* next */
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_lock_spin_item_struct,list);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_item_gethead()
****************************************************************************************************/
cc_result cc_lock_spin_item_gethead(cc_lock_spin_item_struct **itemhead)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,itemhead);

        /* impletement */
        *itemhead = &cc_lock_spin_t.item;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_item_gettail()
****************************************************************************************************/
cc_result cc_lock_spin_item_gettail(cc_lock_spin_item_struct *itemhead,cc_lock_spin_item_struct **itemtail)
{
    cc_result result = CC_E_OK;
    cc_lock_spin_item_struct *iterator;

    do
    {
        /* check parameter */
        CHECK_PTR(result,itemhead);
        CHECK_PTR(result,itemtail);

        /* impletement */
        iterator = itemhead;
        while((iterator != CC_NULL_PTR) && (iterator->list.next != &itemhead->list))
        {
            /* next */
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_lock_spin_item_struct,list);
        }
        
        /* output */
        *itemtail = iterator;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_create()
****************************************************************************************************/
cc_result cc_lock_spin_create(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_lock_spin_item_struct *item;
    cc_lock_spin_item_struct *itemhead;
    cc_lock_spin_item_struct *itemtail;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_lock_spin_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        /* find */
        CHECK_LOGIC(result,cc_lock_spin_find(name,&item) == CC_E_NOT_OK_NOT_FIND);
        /* heap */
        CHECK_FUNC(result,cc_heap_allocate("heap",(cc_void **)&item,sizeof(cc_lock_spin_item_struct)));
        /* create */
        /* name */
        cc_mem_strncpy(item->name,name,CC_NAME_MAX_LEN);
        /* init */
        item->value = CC_LOCK_SPIN_STATE_UNLOCK;
        /* list */
        /* append queue list */
        CHECK_FUNC(result,cc_lock_spin_item_gethead(&itemhead));
        CHECK_FUNC(result,cc_lock_spin_item_gettail(itemhead,&itemtail));
        CHECK_FUNC(result,cc_list_insert_after(&itemtail->list,&item->list));
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_delete()
****************************************************************************************************/
cc_result cc_lock_spin_delete(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_lock_spin_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_lock_spin_initflag == CC_TRUE));
        CHECK_PTR(result,name);

        /* find messagequeue */
        CHECK_FUNC(result,cc_lock_spin_find(name,&item));
        /* remove timer list */
        cc_list_remove(&item->list);
        /* heap free */
        cc_heap_free("heap",item);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_take()
****************************************************************************************************/
cc_result cc_lock_spin_take(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_lock_spin_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_lock_spin_initflag == CC_TRUE));
        /* find messagequeue */
        CHECK_FUNC(result,cc_lock_spin_find(name,&item));
        /* check lock state */
        CHECK_LOGIC(result,(item->value == CC_LOCK_SPIN_STATE_UNLOCK));
        /* take */
        item->value = CC_LOCK_SPIN_STATE_LOCKED;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_wait()
****************************************************************************************************/
cc_result cc_lock_spin_wait(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_lock_spin_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_lock_spin_initflag == CC_TRUE));
        /* find messagequeue */
        CHECK_FUNC(result,cc_lock_spin_find(name,&item));
        /* check lock state */
        while (item->value != CC_LOCK_SPIN_STATE_UNLOCK)
        {
            /* wait */
        }
        /* take */
        item->value = CC_LOCK_SPIN_STATE_LOCKED;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_bring()
****************************************************************************************************/
cc_result cc_lock_spin_bring(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_lock_spin_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_lock_spin_initflag == CC_TRUE));
        /* find messagequeue */
        CHECK_FUNC(result,cc_lock_spin_find(name,&item));
        /* check lock state */
        switch (item->value)
        {
        case CC_LOCK_SPIN_STATE_UNLOCK:
            {
                /* do nothing */
            }
            break;
        case CC_LOCK_SPIN_STATE_LOCKED:
            {
                /* unlock */
                item->value = CC_LOCK_SPIN_STATE_UNLOCK;
            }
            break;
        default:
            break;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_lock_spin_mainfunction()
****************************************************************************************************/
cc_result cc_lock_spin_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File lock_spin.c End!
****************************************************************************************************/

