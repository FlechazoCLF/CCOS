
/****************************************************************************************************
* File cc_thread.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_thread.h"
#include "cc_thread_cfg.h"
#include "cc_kernel.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */
#include "cc_service.h"
#include "cc_port.h"
#include "cc_mem.h"
#include "cc_list.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* thread */
cc_thread_struct cc_thread_t;
/* init flag */
cc_boolean cc_thread_initflag = CC_FALSE;
/* stack */
cc_uint8 cc_thread_stack[CC_THREAD_CFG_STACK_SIZE];

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_thread_object_init()
****************************************************************************************************/
cc_result cc_thread_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "thread obj";
    cc_int8 log[CC_LOG_MAX_LEN] = "thread obj init";

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
        object->id = CC_SERVICE_TYPE_KERNEL;
        /* state */
        object->state = CC_OBJECT_STATE_UNINIT;
        /* type */
        object->type = CC_OBJECT_TYPE(CC_THREAD);
        /* flag */
        object->flag = CC_OBJECT_FLAG_FREE;
        /* info */
        cc_mem_strncpy(object->info.log,log,CC_LOG_MAX_LEN);
        /* authority */
        object->authority = CC_OBJECT_AUTHORITY(CC_THREAD);
        /* list */
        cc_list_init(&object->list);
        /* state */
        object->state = CC_OBJECT_STATE_INIT;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_thread_internal_init()
****************************************************************************************************/
cc_result cc_thread_internal_init(cc_thread_struct *thread)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "thread kernel";
    cc_port_stack_struct cc_port_stack_t;

    do
    {
        /* check parameter */
        CHECK_PTR(result,thread);

        /* name */
        cc_mem_strncpy(thread->name,name,CC_NAME_MAX_LEN);
        /* type */
        thread->type = CC_THREAD_TYPE_KERNEL;
        /* list */
        cc_list_init(&thread->list);
        /* info */
        thread->info.id = 0;
        thread->info.state = CC_THREAD_STATE_UNINIT;
        thread->info.cpuid = 0;
        /* scheduler */
        thread->scheduler.type = CC_THREAD_SCHEDULER_TYPE_IDLE;
        thread->scheduler.block = 0;
        thread->scheduler.time = 0;
        thread->scheduler.tick = 0;
        thread->scheduler.priority = CC_THREAD_PRIORITY_MAX - 1;
        thread->scheduler.currentpriority = CC_THREAD_PRIORITY_MAX - 1;
        /* signal */
        thread->signal.mutex = 0;
        thread->signal.event = 0;
        thread->signal.semaphore = 0;
        thread->signal.signal = 0;
        /* context */
        thread->context.entry = cc_thread_idle_entry;
        thread->context.parameter = CC_NULL_PTR;
        thread->context.stackadd = cc_thread_stack;
        thread->context.stacksize = CC_THREAD_CFG_STACK_SIZE;
        /* port */
        cc_port_stack_t.stackptr = (cc_uint8 *)((cc_uint8 *)thread->context.stackadd + CC_THREAD_CFG_STACK_SIZE - sizeof(cc_uint32));
        cc_port_stack_t.entry = thread->context.entry;
        cc_port_stack_t.parameter = thread->context.parameter;
        cc_port_stack_t.exit = cc_thread_exit;
        cc_port_stack_init(&thread->context.stackptr,&cc_port_stack_t);
        /* func */
        thread->func.init = cc_thread_init;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_thread_init()
****************************************************************************************************/
cc_result cc_thread_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_thread_initflag != CC_TRUE));

        /* init thread object */
        cc_thread_object_init(&cc_thread_t.object);
        /* register object */
        cc_object_register(&cc_thread_t.object);

        /* init thread */
        cc_thread_internal_init(&cc_thread_t);

        cc_thread_initflag = CC_TRUE;

    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_thread_detach()
****************************************************************************************************/
cc_result cc_thread_detach(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_thread_initflag == CC_TRUE));

        cc_thread_initflag = CC_FALSE;

    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_thread_idle_entry()
****************************************************************************************************/
cc_result cc_thread_idle_entry(cc_void *parameter)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_thread_initflag == CC_TRUE));


    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_thread_exit()
****************************************************************************************************/
cc_result cc_thread_exit(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_thread_initflag == CC_TRUE));


    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_thread_create()
****************************************************************************************************/
cc_result cc_thread_create(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_thread_initflag == CC_TRUE));


    }while(0u);
    
    return result;
}

/****************************************************************************************************
* File cc_thread.c End!
****************************************************************************************************/

