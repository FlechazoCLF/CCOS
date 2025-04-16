
/****************************************************************************************************
* File key.c Start!
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
#include "cc_key.h"
/* log */
#include "cc_trace.h"
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

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* cc_key */
cc_key_struct cc_key_t;
/* init flag */
cc_boolean cc_key_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_key_object_init()
****************************************************************************************************/
cc_result cc_key_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 *name = "key obj";
    cc_int8 *log = "key obj init";

    do
    {
        /* check parameter */
        CHECK_PTR(result,object);
        /* impletement */
        cc_components_getobject(object->parent);
        /* name */
        cc_mem_strncpy(object->name,name,CC_NAME_MAX_LEN);
        /* id */
        object->id = CC_SERVICE_TYPE_INPUT;
        /* state */
        object->state = CC_OBJECT_STATE_INIT;
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
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_item_init()
****************************************************************************************************/
cc_result cc_key_item_init(cc_key_item_struct *item)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "key item";

    do
    {
        /* check */
        CHECK_PTR(result,item);
        /* ctrlidx */
        item->ctrlidx = 0;
        /* name */
        cc_mem_strncpy(item->name,name,CC_NAME_MAX_LEN);
        /* init */
        item->type = CC_KEY_ITEM_TYPE_PRESS;
        item->triggermode = CC_KEY_ITEM_TRIGGERMODE_HIGH_TO_LOW;
        item->shakeofftime = 20;
        /* list */
        cc_list_init(&item->list);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_internalinit()
****************************************************************************************************/
cc_result cc_key_internal_init(cc_key_struct *key)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,key);

        /* impletement */
        cc_key_item_init(&key->item);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_service_init()
****************************************************************************************************/
cc_result cc_key_service_init(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_int8 *name = "key";
    cc_int8 *log = "key service init";

    do
    {
        /* check parameter */
        CHECK_PTR(result,service);
        /* impletement */
        /* parent */
        service->parent = CC_NULL_PTR;
        /* object */
        service->object = &cc_key_t.object;
        /* name */
        cc_mem_strncpy(service->name,name,CC_NAME_MAX_LEN);
        /* method */
        service->method = CC_SERVICE_METHOD_LOCAL;
        /* level */
        service->level = CC_SERVICE_LEVEL_COMPONENTS;
        /* type */
        service->type = CC_SERVICE_TYPE_INPUT;
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
        service->scheduler.init = cc_key_init;
        service->scheduler.mainfunction = cc_key_mainfunction;
        /* signal */
        service->signal.mutex = 0;
        service->signal.event = 0;
        service->signal.semaphore = 0;
        service->signal.signal = 0;
        /* func */
        service->func.send = cc_service_send;
        service->func.recv = cc_mem_recv;
        /* state */
        service->info.state = CC_SERVICE_STATE_INIT;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_init()
****************************************************************************************************/
cc_result cc_key_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,CC_NULL_PTR);

        /* init object */
        cc_key_object_init(&cc_key_t.object);
        /* register object */
        cc_object_register(&cc_key_t.object);

        /* init key */
        cc_key_internal_init(&cc_key_t);

        /* init service */
        cc_key_service_init(&cc_key_t.service);
        /* register service */
        cc_service_register(&cc_key_t.service);

        /* start service */
        cc_service_start("key");

        /* init flag */
        cc_key_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_item_gethead()
****************************************************************************************************/
cc_result cc_key_item_gethead(cc_key_item_struct **itemhead)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,itemhead);

        /* impletement */
        *itemhead = &cc_key_t.item;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_item_gettail()
****************************************************************************************************/
cc_result cc_key_item_gettail(cc_key_item_struct *itemhead,cc_key_item_struct **itemtail)
{
    cc_result result = CC_E_OK;
    cc_key_item_struct *iterator;

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
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_key_item_struct,list);
        }
        
        /* output */
        *itemtail = iterator;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_find()
****************************************************************************************************/
cc_result cc_key_find(cc_int8 *name,cc_key_item_struct **item)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_key_item_struct *itemhead;
    cc_key_item_struct *iterator;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_key_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,item);

        /* check timer list */
        itemhead = &cc_key_t.item;
        iterator = itemhead;
        /* iterator */
        while((iterator != CC_NULL_PTR) && (iterator->list.next != &itemhead->list))
        {
            /* check name */
            if(cc_mem_strcmp(name,iterator->name,CC_NAME_MAX_LEN) == CC_E_OK)
            {
                /* set state */
                *item = iterator;
                result = CC_E_OK;
                break;
            }
            /* next */
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_key_item_struct,list);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_create()
****************************************************************************************************/
cc_result cc_key_create(cc_int8 *name,cc_key_item_type_enum type,cc_key_item_triggermode_enum triggermode,cc_uint32 shakeofftime)
{
    cc_result result = CC_E_OK;
    cc_key_item_struct *item;
    cc_key_item_struct *itemhead;
    cc_key_item_struct *itemtail;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_key_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        /* find */
        CHECK_LOGIC(result,cc_key_find(name,&item) == CC_E_NOT_OK_NOT_FIND);
        /* heap */
        CHECK_FUNC(result,cc_heap_allocate("heap",&(cc_void *)item,sizeof(cc_key_item_struct)));
        /* create */
        /* ctrlidx */
        cc_list_getlen(&item->list,&item->ctrlidx);
        /* name */
        cc_mem_strncpy(item->name,name,CC_NAME_MAX_LEN);
        /* type */
        item->type = type;
        /* triggermode */
        item->triggermode = triggermode;
        /* shakeofftime */
        item->shakeofftime = shakeofftime;
        /* list */
        /* append queue list */
        CHECK_FUNC(result,cc_key_item_gethead(&itemhead));
        CHECK_FUNC(result,cc_key_item_gettail(itemhead,&itemtail));
        CHECK_FUNC(result,cc_list_insert_after(&itemtail->list,&item->list));
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_getctrlidx()
****************************************************************************************************/
cc_result cc_key_getctrlidx(cc_uint32 *ctrlidx,cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_key_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_key_initflag == CC_TRUE));
        CHECK_PTR(result,ctrlidx);
        CHECK_PTR(result,name);
        /* find */
        CHECK_FUNC(result,cc_key_find(name,&item));
        /* output */
        *ctrlidx = item->ctrlidx;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_delete()
****************************************************************************************************/
cc_result cc_key_delete(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_key_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_key_initflag == CC_TRUE));
        CHECK_PTR(result,name);

        /* find messagequeue */
        CHECK_FUNC(result,cc_key_find(name,&item));
        /* remove timer list */
        cc_list_remove(&item->list);
        /* heap free */
        cc_heap_free("heap",item);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_recv()
****************************************************************************************************/
cc_result cc_mem_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dstname);
        CHECK_PTR(result,srcname);
        CHECK_PTR(result,data);

        /* check dstname */
        CHECK_FUNC(result,cc_mem_strncmp(cc_key_t.service.name,dstname,CC_NAME_MAX_LEN));
        /* check srcname */
        ____________________________TO_DO__________________________
        switch(type)
        {
        case CC_SERVICE_MSGTYPE_USER:
            {
                
            }
            break;
        case CC_SERVICE_MSGTYPE_TASK:
            {
                
            }
            break;
        case CC_SERVICE_MSGTYPE_SERVICE:
            {
                /* call public service data: func + parameter */

            }
            break;
        case CC_SERVICE_MSGTYPE_SERVICE_ALIVE:
            {
                /* set flag then send to service alive */
                cc_key_t.service.func.send(srcname,dstname,data,len,CC_SERVICE_MSGTYPE_SERVICE_ALIVE);
            }
            break;
        case CC_SERVICE_MSGTYPE_THREAD:
            {
                
            }
            break;
        case CC_SERVICE_MSGTYPE_KERNEL:
            {
                
            }
            break;
        case CC_SERVICE_MSGTYPE_IPC:
            {
                
            }
            break;
        
        default:
            break;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_scanf_press()
****************************************************************************************************/
cc_result cc_key_scanf_press(cc_key_item_struct *item,cc_boolean *triggerflag)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_POINTER(result,item);
        CHECK_POINTER(result,triggerflag);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_scanf_knock()
****************************************************************************************************/
cc_result cc_key_scanf_knock(cc_key_item_struct *item,cc_boolean *triggerflag)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_POINTER(result,item);
        CHECK_POINTER(result,triggerflag);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_scanf()
****************************************************************************************************/
cc_result cc_key_scanf(cc_uint32 *ctrlidx,cc_key_item_status_enum *status)
{
    cc_result result = CC_E_OK;
    cc_key_item_struct *itemhead;
    cc_key_item_struct *iterator;
    cc_boolean triggerflag = CC_FALSE;

    do
    {
        /* check pointer */
        CHECK_POINTER(result,ctrlidx);
        CHECK_POINTER(result,status);

        /* impletement */
        cc_key_item_gethead(&itemhead);
        iterator = itemhead;
        /* iterator */
        while((iterator != CC_NULL_PTR) && (iterator->list.next != &itemhead->list))
        {
            /* type */
            switch(iterator->type)
            {
            case CC_KEY_ITEM_TYPE_PRESS:
                {
                    cc_key_scanf_press(iterator,&triggerflag);
                }
                break;
            case CC_KEY_ITEM_TYPE_KNOCK:
                {
                    cc_key_scanf_knock(iterator,&triggerflag);
                }
                break;
            default:
                break;
            }

            /* find trigger */
            if(triggerflag == CC_TRUE)
            {
                /* get status */
                *ctrlidx = iterator->ctrlidx;
                *status = iterator->status.value;
                break;
            }

            /* next */
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_key_item_struct,list);
        }

        /* check trigger */
        if(triggerflag == CC_TRUE)
        {
            /* find trigger */
            continue;
        }

        /* no key trigger */
        cc_list_getlen(&itemhead->list,&ctrlidx);
        *status = CC_KEY_ITEM_STATUS_END;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_key_mainfunction()
****************************************************************************************************/
cc_result cc_key_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File key.c End!
****************************************************************************************************/

