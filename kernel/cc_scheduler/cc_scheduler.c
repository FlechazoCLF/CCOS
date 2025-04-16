
/****************************************************************************************************
* File cc_scheduler.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_scheduler.h"
#include "cc_kernel.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */
#include "cc_service.h"
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

/* init flag */
cc_boolean cc_scheduler_initflag = CC_FALSE;

/* sheduler */
cc_scheduler_struct cc_scheduler_t;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_scheduler_object_init()
****************************************************************************************************/
cc_result cc_scheduler_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "scheduler obj";
    cc_int8 log[CC_LOG_MAX_LEN] = "scheduler obj init";

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
        object->type = CC_OBJECT_TYPE(CC_KERNEL);
        /* flag */
        object->flag = CC_OBJECT_FLAG_FREE;
        /* info */
        cc_mem_strncpy(object->info.log,log,CC_LOG_MAX_LEN);
        /* authority */
        object->authority = CC_OBJECT_AUTHORITY(CC_KERNEL);
        /* list */
        cc_list_init(&object->list);
        /* state */
        object->state = CC_OBJECT_STATE_INIT;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_scheduler_internal_init()
****************************************************************************************************/
cc_result cc_scheduler_internal_init(cc_scheduler_struct *scheduler)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,scheduler);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_scheduler_init()
****************************************************************************************************/
cc_result cc_scheduler_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_scheduler_initflag != CC_TRUE));

        /* init scheduler object */
        cc_scheduler_object_init(&cc_scheduler_t.object);
        /* register object */
        cc_object_register(&cc_scheduler_t.object);
        /* init scheduler */
        cc_scheduler_internal_init(&cc_scheduler_t);

        cc_scheduler_initflag = CC_TRUE;
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_scheduler_retrevethread()
****************************************************************************************************/
cc_result cc_scheduler_retrevethread(cc_thread_struct **thread)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,thread);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_scheduler_preparethread()
****************************************************************************************************/
cc_result cc_scheduler_preparethread(cc_thread_struct **thread)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,thread);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_scheduler_switchthread()
****************************************************************************************************/
cc_result cc_scheduler_switchthread(cc_thread_struct **thread)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,thread);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_scheduler_start()
****************************************************************************************************/
cc_result cc_scheduler_start(cc_void)
{
    cc_result result = CC_E_OK;
    cc_thread_struct *thread;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_scheduler_initflag == CC_TRUE));

        /* get thread from priority map */
        cc_scheduler_retrevethread(&thread);
        /* modify scheduler info */
        cc_scheduler_preparethread(&thread);
        /* switch thread */
        cc_scheduler_switchthread(&thread);

        /* not reached */
    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_scheduler.c End!
****************************************************************************************************/

