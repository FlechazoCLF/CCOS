
/****************************************************************************************************
* File com_messagequeue.c Start!
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
#include "cc_com_messagequeue.h"
/* log */
#include "cc_trace.h"
/* sub module */
#include "cc_com_messagequeue_cfg.h"
/* components */
#include "cc_com.h"
#include "cc_list.h"
#include "cc_heap.h"
#include "cc_mem.h"
#include "cc_timer.h"

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

/* cc_com_messagequeue */
cc_com_messagequeue_struct cc_com_messagequeue_t;
/* init flag */
cc_boolean cc_com_messagequeue_initflag = CC_FALSE;
/* buffer */
cc_uint8 cc_com_messagequeue_buffer[CC_COM_MESSAGEQUEUE_CFG_BUFFER_SIZE];

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_com_messagequeue_object_init()
****************************************************************************************************/
cc_result cc_com_messagequeue_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "mq obj";
    cc_int8 log[CC_LOG_MAX_LEN] = "mq obj init";

    do
    {
        /* check */
        CHECK_PTR(result,object);
        /* impletement */
        /* parent */
        cc_com_getobject(&object->parent);
        /* name */
        cc_mem_strncpy(object->name,name,CC_NAME_MAX_LEN);
        /* id */
        object->id = CC_SERVICE_TYPE_COM;
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
* cc_com_messagequeue_callback()
****************************************************************************************************/
cc_result cc_com_messagequeue_callback(cc_int8 *name,cc_com_messagequeue_state_enum state)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,name);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_item_init()
****************************************************************************************************/
cc_result cc_com_messagequeue_item_init(cc_com_messagequeue_item_struct *item)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,item);
        /* item init */
        item->ctrlidx = 0u;
        item->state = CC_QUEUE_STATE_UNINIT;
        item->buffer = cc_com_messagequeue_buffer;
        item->length = CC_COM_MESSAGEQUEUE_CFG_BUFFER_SIZE;
        item->operate.readpointer = item->buffer;
        item->operate.writepointer = item->buffer;
        item->operate.length = CC_NULL;
        item->operate.uselength = CC_NULL;
        cc_lock_create("lock mq",CC_LOCK_TYPE_MUTEX,&item->lock);
        item->callback = cc_com_messagequeue_callback;
        cc_list_init(&item->list);
        item->state = CC_QUEUE_STATE_INIT;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_internal_init()
****************************************************************************************************/
cc_result cc_com_messagequeue_internal_init(cc_com_messagequeue_struct *messagequeue)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,messagequeue);
        /* item init */
        cc_com_messagequeue_item_init(&messagequeue->item);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_service_init()
****************************************************************************************************/
cc_result cc_com_messagequeue_service_init(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_int8 *name = "messagequeue";
    cc_int8 *log = "mq service init";

    do
    {
        /* check */
        CHECK_PTR(result,service);
        /* impletement */
        /* parent */
        service->parent = CC_NULL_PTR;
        /* object */
        service->object = &cc_com_messagequeue_t.object;
        /* name */
        cc_mem_strncpy(service->name,name,CC_NAME_MAX_LEN);
        /* method */
        service->method = CC_SERVICE_METHOD_LOCAL;
        /* level */
        service->level = CC_SERVICE_LEVEL_KERNEL;
        /* type */
        service->type = CC_SERVICE_TYPE_COM;
        /* list */
        cc_list_init(&service->list);
        /* info */
        service->info.id = 0;
        service->info.state = CC_SERVICE_STATE_UNINIT;
        cc_mem_strncpy(service->info.log,log,CC_LOG_MAX_LEN);
        service->info.version = 1;
        service->info.inittime = cc_timer_getlocaltime();
        service->info.starttime = 0;
        service->info.stoptime = 0;
        /* scheduler */
        service->scheduler.init = cc_com_messagequeue_init;
        service->scheduler.mainfunction = cc_com_messagequeue_mainfunction;
        /* signal */
        service->signal.mutex = 0;
        service->signal.event = 0;
        service->signal.semaphore = 0;
        service->signal.signal = 0;
        /* func */
        service->func.send = cc_service_send;
        service->func.recv = cc_com_messagequeue_recv;
        /* state */
        service->info.state = CC_SERVICE_STATE_INIT;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_init()
****************************************************************************************************/
cc_result cc_com_messagequeue_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_com_messagequeue_initflag != CC_TRUE));
        /* init object */
        cc_com_messagequeue_object_init(&cc_com_messagequeue_t.object);
        /* register object */
        cc_object_register(&cc_com_messagequeue_t.object);

        /* init com_messagequeue */
        cc_com_messagequeue_internal_init(&cc_com_messagequeue_t);

        /* init service */
        cc_com_messagequeue_service_init(&cc_com_messagequeue_t.service);
        /* register service */
        cc_service_register(&cc_com_messagequeue_t.service);

        /* start service */
        cc_service_start("messagequeue");

        /* init flag */
        cc_com_messagequeue_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_item_find()
****************************************************************************************************/
cc_result cc_com_messagequeue_item_find(cc_int8 *name,cc_com_messagequeue_item_struct **item)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_com_messagequeue_item_struct *itemhead;
    cc_com_messagequeue_item_struct *iterator;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_com_messagequeue_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,item);

        /* check timer list */
        itemhead = &cc_com_messagequeue_t.item;
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
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_com_messagequeue_item_struct,list);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_item_gethead()
****************************************************************************************************/
cc_result cc_com_messagequeue_item_gethead(cc_com_messagequeue_item_struct **itemhead)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,itemhead);

        /* impletement */
        *itemhead = &cc_com_messagequeue_t.item;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_item_gettail()
****************************************************************************************************/
cc_result cc_com_messagequeue_item_gettail(cc_com_messagequeue_item_struct *itemhead,cc_com_messagequeue_item_struct **itemtail)
{
    cc_result result = CC_E_OK;
    cc_com_messagequeue_item_struct *iterator;

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
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_com_messagequeue_item_struct,list);
        }
        
        /* output */
        *itemtail = iterator;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_create()
****************************************************************************************************/
cc_result cc_com_messagequeue_create(cc_uint8 *ctrlidx,cc_int8 *name,cc_void *buffer,cc_uint32 length)
{
    cc_result result = CC_E_OK;
    cc_com_messagequeue_item_struct *item;
    cc_com_messagequeue_item_struct *itemhead = CC_NULL_PTR;
    cc_com_messagequeue_item_struct *itemtail = CC_NULL_PTR;

    do
    {
        /* check */
        CHECK_PTR(result,ctrlidx);
        CHECK_PTR(result,name);
        CHECK_PTR(result,buffer);
        CHECK_LOGIC(result,(length > 0));

        /* find name */
        CHECK_LOGIC(result,(cc_com_messagequeue_item_find(name,&item) == CC_E_NOT_OK_NOT_FIND));
        /* heap */
        CHECK_FUNC(result,cc_heap_allocate("heap",(cc_void **)&item,sizeof(cc_com_messagequeue_item_struct)));
        /* init */
        item->ctrlidx = 0;
        /* name */
        cc_mem_strncpy(item->name,name,CC_NAME_MAX_LEN);
        item->state = CC_QUEUE_STATE_UNINIT;
        item->buffer = buffer;
        item->length = length;
        item->operate.readpointer = item->buffer;
        item->operate.writepointer = item->buffer;
        item->operate.length = CC_NULL;
        item->operate.uselength = CC_NULL;
        /* create lock */
        cc_lock_create(name,CC_LOCK_TYPE_MUTEX,&item->lock);
        item->callback = cc_com_messagequeue_callback;
        /* append queue list */
        CHECK_FUNC(result,cc_com_messagequeue_item_gethead(&itemhead));
        CHECK_FUNC(result,cc_com_messagequeue_item_gettail(itemhead,&itemtail));
        CHECK_FUNC(result,cc_list_insert_after(&itemtail->list,&item->list));
        item->state = CC_QUEUE_STATE_INIT;
        /* output ctrlidx */
        *ctrlidx = item->ctrlidx;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_delete()
****************************************************************************************************/
cc_result cc_com_messagequeue_delete(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_com_messagequeue_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_com_messagequeue_initflag == CC_TRUE));
        CHECK_PTR(result,name);

        /* find messagequeue */
        CHECK_FUNC(result,cc_com_messagequeue_item_find(name,&item));
        /* remove timer list */
        cc_list_remove(&item->list);
        /* heap free */
        cc_heap_free("heap",item);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_read()
****************************************************************************************************/
cc_result cc_com_messagequeue_read(cc_int8 *name,cc_void **buffer,cc_uint32 *length)
{
    cc_result result = CC_E_OK;
    cc_com_messagequeue_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_com_messagequeue_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,buffer);
        CHECK_PTR(result,length);

        /* find messagequeue */
        CHECK_FUNC(result,cc_com_messagequeue_item_find(name,&item));

        /* return pointer */
        *buffer = item->operate.readpointer;
        *length = item->operate.length;
        item->operate.uselength = item->operate.length;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_readout()
****************************************************************************************************/
cc_result cc_com_messagequeue_readout(cc_int8 *name,cc_void *buffer,cc_uint32 *length)
{
    cc_result result = CC_E_OK;
    cc_com_messagequeue_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_com_messagequeue_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,buffer);
        CHECK_PTR(result,length);

        /* find messagequeue */
        CHECK_FUNC(result,cc_com_messagequeue_item_find(name,&item));
        CHECK_LOGIC(result,(item->operate.length > 0));

        /* copy buffer */
        CHECK_FUNC(result,cc_mem_cpy(buffer,item->operate.readpointer,item->operate.length));
        item->operate.readpointer += item->operate.length;
        item->operate.length = 0;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_release()
****************************************************************************************************/
cc_result cc_com_messagequeue_release(cc_int8 *name,cc_void *buffer,cc_uint32 length)
{
    cc_result result = CC_E_OK;
    cc_com_messagequeue_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_com_messagequeue_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,buffer);
        CHECK_LOGIC(result,(length > 0));

        /* find messagequeue */
        CHECK_FUNC(result,cc_com_messagequeue_item_find(name,&item));
        CHECK_LOGIC(result,(item->operate.length > 0));
        CHECK_LOGIC(result,(length <= item->operate.length));

        /* release */
        CHECK_LOGIC(result,(buffer >= item->operate.readpointer));
        item->operate.readpointer = (cc_uint8 *)buffer + length;
        item->operate.length -= length;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_write()
****************************************************************************************************/
cc_result cc_com_messagequeue_write(cc_int8 *name,cc_void *buffer,cc_uint32 length)
{
    cc_result result = CC_E_OK;
    cc_com_messagequeue_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_com_messagequeue_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,buffer);
        CHECK_LOGIC(result,(length > 0));

        /* find messagequeue */
        CHECK_FUNC(result,cc_com_messagequeue_item_find(name,&item));
        CHECK_LOGIC(result,(length > 0));
        CHECK_LOGIC(result,(length <= item->length));

        /* write */
        ____________________________TO_DO__________________________
        CHECK_FUNC(result,cc_mem_cpy(item->operate.writepointer,buffer,length));
        item->operate.writepointer += length;
        item->operate.length += length;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_lock()
****************************************************************************************************/
cc_result cc_com_messagequeue_lock(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_unlock()
****************************************************************************************************/
cc_result cc_com_messagequeue_unlock(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */

        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_recv()
****************************************************************************************************/
cc_result cc_com_messagequeue_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dstname);
        CHECK_PTR(result,srcname);
        CHECK_PTR(result,data);

        /* check dstname */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_com_messagequeue_mainfunction()
****************************************************************************************************/
cc_result cc_com_messagequeue_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File com_messagequeue.c End!
****************************************************************************************************/

