
/****************************************************************************************************
* File cc_timer.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_timer.h"
#include "cc_timer_cfg.h"
#include "cc_kernel.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */
#include "cc_clock.h"
#include "cc_trace.h"
#include "cc_list.h"
#include "cc_heap.h"
#include "cc_mem.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/* kernel time 1ms task */
#define CC_TIMER_ITEM_NAME_1MS "timer 1ms"

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* timer */
cc_timer_struct cc_timer_t;
/* init flag */
cc_boolean cc_timer_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_timer_item_callback_1ms()
****************************************************************************************************/
cc_void cc_timer_item_callback_1ms(cc_void *parameter)
{

}

/****************************************************************************************************
* cc_timer_item_init()
****************************************************************************************************/
cc_result cc_timer_item_init(cc_timer_item_struct *item)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = CC_TIMER_ITEM_NAME_1MS;

    do
    {
        /* name */
        cc_mem_cpy(item->name,name,CC_NAME_MAX_LEN);
        item->type = CC_TIMER_ITEM_TYPE_CYCLE;
        item->state = CC_TIMER_ITEM_STATE_INIT;
        item->time = 0;
        item->timeout = 1;
        item->precision = CC_TIMER_PRECISION_MS;
        item->callback = cc_timer_item_callback_1ms;
        item->parameter = CC_NULL_PTR;
        /* init list */
        cc_list_init(&item->list);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_object_init()
****************************************************************************************************/
cc_result cc_timer_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "timer obj";
    cc_int8 log[CC_LOG_MAX_LEN] = "timer obj init";

    do
    {
        /* check parameter */
        CHECK_PTR(result,object);
        /* impletement */
        /* parent */
        object->parent = CC_KERNEL_OBJECT_GET();
        /* name */
        cc_mem_strncpy(object->name,name,CC_NAME_MAX_LEN);
        /* id */
        object->id = CC_SERVICE_TYPE_TIMER;
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
* cc_timer_internal_init()
****************************************************************************************************/
cc_result cc_timer_internal_init(cc_timer_struct *timer)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,timer);

        /* clock init */
        cc_clock_init();
        cc_clock_tick_callback_init(cc_timer_mainfunction);
        /* init list */
        cc_timer_item_init(&timer->item);
        /* start timer */
        cc_timer_start(CC_TIMER_ITEM_NAME_1MS);

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_service_init()
****************************************************************************************************/
cc_result cc_timer_service_init(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_int8 *name = "timer";
    cc_int8 *log = "timer service init";

    do
    {
        /* check parameter */
        CHECK_PTR(result,service);
        /* impletement */
        /* parent */
        service->parent = CC_NULL_PTR;
        /* object */
        service->object = &cc_timer_t.object;
        /* name */
        cc_mem_strncpy(service->name,name,CC_NAME_MAX_LEN);
        /* method */
        service->method = CC_SERVICE_METHOD_LOCAL;
        /* level */
        service->level = CC_SERVICE_LEVEL_KERNEL;
        /* type */
        service->type = CC_SERVICE_TYPE_TIMER;
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
        service->scheduler.init = cc_timer_init;
        service->scheduler.mainfunction = cc_timer_mainfunction;
        /* signal */
        service->signal.mutex = 0;
        service->signal.event = 0;
        service->signal.semaphore = 0;
        service->signal.signal = 0;
        /* func */
        service->func.send = cc_service_send;
        service->func.recv = cc_timer_recv;
        /* state */
        service->info.state = CC_SERVICE_STATE_INIT;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_init()
****************************************************************************************************/
cc_result cc_timer_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag != CC_TRUE));

        /* init timer object */
        cc_timer_object_init(&cc_timer_t.object);
        /* register object */
        cc_object_register(&cc_timer_t.object);

        /* init timer */
        cc_timer_internal_init(&cc_timer_t);

        /* init service */
        cc_timer_service_init(&cc_timer_t.service);
        /* register service */
        cc_service_register(&cc_timer_t.service);

        /* start service */
        cc_service_start("timer");

        /* init flag */
        cc_timer_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_detach()
****************************************************************************************************/
cc_result cc_timer_detach(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));
        /* init flag */
        cc_timer_initflag = CC_FALSE;
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_timer_item_object_init()
****************************************************************************************************/
cc_result cc_timer_item_object_init(cc_int8 *name,cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 *log = "user timer create";

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,object);

        /* parent */
        object->parent = &cc_timer_t.object;
        /* name */
        cc_mem_strncpy(object->name,name,CC_NAME_MAX_LEN);
        /* id */
        object->id = CC_SERVICE_TYPE_TIMER;
        /* state */
        object->state = CC_OBJECT_STATE_UNINIT;
        /* type */
        object->type = CC_OBJECT_TYPE(CC_USER);
        /* flag */
        object->flag = CC_OBJECT_FLAG_FREE;
        /* info */
        cc_mem_strncpy(object->info.log,log,CC_LOG_MAX_LEN);
        /* authority */
        object->authority = CC_OBJECT_AUTHORITY(CC_USER);
        /* list */
        cc_list_init(&object->list);
        /* state */
        object->state = CC_OBJECT_STATE_INIT;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_create()
****************************************************************************************************/
cc_result cc_timer_create(cc_int8 *name,cc_timer_create_type_enum type,cc_timer_item_struct *item)
{
    cc_result result = CC_E_OK;
    cc_timer_item_struct *newitem = CC_NULL_PTR;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,item);
        CHECK_PTR(result,item->callback);
        CHECK_LOGIC(result,(item->timeout > 0));

        /* create timer */
        switch (type)
        {
        case CC_TIMER_CREATE_TYPE_HEAP:
            {
                /* heap allocate */
                CHECK_FUNC(result,cc_heap_allocate("heap",(cc_void **)&newitem,sizeof(cc_timer_item_struct)));
                /* get input config */
                cc_mem_cpy(newitem,item,sizeof(cc_timer_item_struct));                
            }
            break;
        case CC_TIMER_CREATE_TYPE_MEM:
            {
                /* mem create */
                newitem = item;
            }
            break;
        default:
            break;
        }
        /* check */
        CHECK_PTR(result,newitem);
        /* object init */
        cc_timer_item_object_init(name,&newitem->object);
        /* init list */
        cc_list_insert_after(&cc_timer_t.item.list,&newitem->list);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_item_find()
****************************************************************************************************/
cc_result cc_timer_item_find(cc_int8 *name,cc_timer_item_struct **item)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_timer_item_struct *itemhead;
    cc_timer_item_struct *iterator;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));
        CHECK_PTR(result,name);
        CHECK_PTR(result,item);

        /* check timer list */
        itemhead = &cc_timer_t.item;
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
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_timer_item_struct,list);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_delete()
****************************************************************************************************/
cc_result cc_timer_delete(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_timer_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));

        /* find timer item */
        CHECK_FUNC(result,cc_timer_item_find(name,&item));
        /* remove timer list */
        cc_list_remove(&item->list);
        /* heap free */
        cc_heap_free("heap",item);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_start()
****************************************************************************************************/
cc_result cc_timer_start(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_timer_item_struct *itemhead;
    cc_timer_item_struct *iterator;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));

        /* check timer list */
        itemhead = &cc_timer_t.item;
        iterator = itemhead;
        /* iterator */
        while((iterator != CC_NULL_PTR) && (iterator->list.next != &itemhead->list))
        {
            /* check name */
            if(cc_mem_strncmp(name,iterator->name,CC_NAME_MAX_LEN) == CC_E_OK)
            {
                /* set state */
                ____________________________TO_DO__________________________/* create state change map */
                iterator->state = CC_TIMER_ITEM_STATE_START;
            }
            /* next */
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_timer_item_struct,list);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_stop()
****************************************************************************************************/
cc_result cc_timer_stop(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_timer_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));

        /* find timer item */
        CHECK_FUNC(result,cc_timer_item_find(name,&item));

        /* remove ready list */
        item->state = CC_TIMER_ITEM_STATE_STOP;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_gettimebyprecision()
****************************************************************************************************/
cc_result cc_timer_gettimebyprecision(cc_uint32 *time,cc_timer_precision_enum precision)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));
        CHECK_PTR(result,time);
        /* get time */
        switch (precision)
        {
        case CC_TIMER_PRECISION_TICK:
            {
                *time = cc_timer_t.date.tick;
            }
            break;
        case CC_TIMER_PRECISION_NS:
            {
                *time = cc_timer_t.date.nanosecond;
            }
            break;
        case CC_TIMER_PRECISION_MS:
            {
                *time = cc_timer_t.date.millisecond;
            }
            break;
        case CC_TIMER_PRECISION_S:
            {
                *time = cc_timer_t.date.second;
            }
            break;
        case CC_TIMER_PRECISION_MIN:
            {
                *time = cc_timer_t.date.minute;
            }
            break;
        case CC_TIMER_PRECISION_HOUR:
            {
                *time = cc_timer_t.date.hour;
            }
            break;
        case CC_TIMER_PRECISION_DAY:
            {
                *time = cc_timer_t.date.day;
            }
            break;
        case CC_TIMER_PRECISION_MONTH:
            {
                *time = cc_timer_t.date.month;
            }
            break;
        case CC_TIMER_PRECISION_YEAR:
            {
                *time = cc_timer_t.date.year;
            }
            break;
        default:
            *time = cc_timer_t.date.millisecond;
            break;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_item_checktimeout()
****************************************************************************************************/
cc_result cc_timer_item_checktimeout(cc_timer_item_struct *item)
{
    cc_result result = CC_E_OK;
    cc_uint32 time = 0;
    cc_uint32 timeout = 0;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));

        /* get time */
        cc_timer_gettimebyprecision(&time,item->precision);
        /* (case 1):
         *  0 1 2 3 4 5 6 7 8 9  
         *      |<   5   >|
         *      V         v
         *  item->time   time
         * (case 2):
         *  0 1 2 3 4 5 6 7 8 9  
         *   3 >|         |< 2
         *      V         v
         *    time    item->time
         */
        /* get timeout */
        timeout = (item->time <= time) ? (time - item->time) : (timeout - 1 - item->time + time);
        /* check timeout */
        if(timeout >= item->timeout)
        {
            /* timeout */
            item->time = time;
            result = CC_E_OK;
        }
        else
        {
            /* delay */
            result = CC_E_NOT_OK;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_checktimeout()
****************************************************************************************************/
cc_result cc_timer_checktimeout(cc_void)
{
    cc_result result = CC_E_OK;
    cc_timer_item_struct *itemhead;
    cc_timer_item_struct *iterator;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));

        /* check timer list */
        itemhead = &cc_timer_t.item;
        iterator = itemhead;
        /* iterator */
        while((iterator != CC_NULL_PTR) && (iterator->list.next != &itemhead->list))
        {
            /* check state & timeout */
            if((iterator->state == CC_TIMER_ITEM_STATE_START)&&\
               (cc_timer_item_checktimeout(iterator) == CC_E_OK))
            {
                /* user callback */
                iterator->callback(iterator->parameter);
            }
            /* next */
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_timer_item_struct,list);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_getlocaltime()
****************************************************************************************************/
cc_result cc_timer_getlocaltime(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));

        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_recv()
****************************************************************************************************/
cc_result cc_timer_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dstname);
        CHECK_PTR(result,srcname);
        CHECK_PTR(result,data);

        /* check dstname */
        CHECK_FUNC(result,cc_mem_strncmp(cc_timer_t.service.name,dstname,CC_NAME_MAX_LEN));
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
                CHECK_FUNC(result,cc_timer_cfg_servicecall(data,len));
            }
            break;
        case CC_SERVICE_MSGTYPE_SERVICE_ALIVE:
            {
                /* set flag then send to service alive */
                cc_timer_t.service.func.send(srcname,dstname,data,len,CC_SERVICE_MSGTYPE_SERVICE_ALIVE);
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
* cc_timer_dateupdateCarryBit()
****************************************************************************************************/
cc_result cc_timer_dateupdateCarryBit(cc_uint32 *dst,cc_uint32 *src,cc_uint32 span)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);
        /* impletement */
        if(((*src) % span) == 0)
        {
            *src = 0;
            *dst = *dst + 1;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_dateupdate()
****************************************************************************************************/
cc_result cc_timer_dateupdate(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* update date */
        CHECK_LOGIC(result,(cc_timer_initflag == CC_TRUE));
        /* get tick */
        cc_timer_t.date.tick = cc_clock_tickgetdirect();
        /* calc date */
        if(cc_timer_t.date.tick%(TIMER_CLOCK_FREQUENCY/1000000) == 0)
        {
            cc_timer_t.date.nanosecond++;
            /* 1000 ns = 1 ms */
            cc_timer_dateupdateCarryBit(&cc_timer_t.date.millisecond,\
                                        &cc_timer_t.date.nanosecond,\
                                        1000);
            /* 1000 ms = 1 s */
            cc_timer_dateupdateCarryBit(&cc_timer_t.date.second,\
                                        &cc_timer_t.date.millisecond,\
                                        1000);
            /* 60 s = 1 m */
            cc_timer_dateupdateCarryBit(&cc_timer_t.date.minute,\
                                        &cc_timer_t.date.second,\
                                        60);
            /* 60 m = 1 h */
            cc_timer_dateupdateCarryBit(&cc_timer_t.date.hour,\
                                        &cc_timer_t.date.minute,\
                                        60);
            /* 24 h = 1 d */
            cc_timer_dateupdateCarryBit(&cc_timer_t.date.day,\
                                        &cc_timer_t.date.hour,\
                                        24);
            /* 30 d = 1 m */
            cc_timer_dateupdateCarryBit(&cc_timer_t.date.month,\
                                        &cc_timer_t.date.day,\
                                        30);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_mainfunction()
****************************************************************************************************/
cc_result cc_timer_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* update date */
        cc_timer_dateupdate();
        /* check timeout */
        cc_timer_checktimeout();
    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_timer.c End!
****************************************************************************************************/

