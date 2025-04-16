
/****************************************************************************************************
* File cc_timer_cfg.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_timer_cfg.h"
#include "cc_timer.h"
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
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

cc_timer_cfg_functable_struct cc_timer_cfg_functable_t[CC_TIMER_CFG_FUNCTABLE_NUM] = 
{
    /*      .ctrlidx,                     .funcname,          .func,                .parameter,                                     .info */
    { CC_TIMER_FUNCCTRLIDX_INIT         ,   "init"         , cc_timer_init         , "cc_void"                                      , "1"},
    { CC_TIMER_FUNCCTRLIDX_DETACH       ,   "detach"       , cc_timer_detach       , "cc_void"                                      , "2"},
    { CC_TIMER_FUNCCTRLIDX_CREATE       ,   "create"       , cc_timer_create       , "cc_void *dst,cc_void *src,cc_uint32 len"      , "3"},
    { CC_TIMER_FUNCCTRLIDX_DELETE       ,   "delete"       , cc_timer_delete       , "cc_void *dst,cc_uint32 value,cc_uint32 len"   , "4"},
    { CC_TIMER_FUNCCTRLIDX_START        ,   "start"        , cc_timer_start        , "cc_void *dst,cc_void *src,cc_uint32 len"      , "5"},
    { CC_TIMER_FUNCCTRLIDX_STOP         ,   "stop"         , cc_timer_stop         , "cc_int8 *src,cc_uint32 *len"                  , "6"},
    { CC_TIMER_FUNCCTRLIDX_GETLOCALTIME ,   "getlocaltime" , cc_timer_getlocaltime , "cc_int8 *src,cc_uint32 *len,cc_uint32 maxlen" , "7"},
};

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_timer_cfg_getfunc()
****************************************************************************************************/
cc_result cc_timer_cfg_getfunc(cc_uint8 ctrlidx,void **func)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_uint8 i;

    do
    {
        /* check parameter */
        CHECK_PTR(result,func);
        /* foreach */
        for(i = 0;i < CC_TIMER_CFG_FUNCTABLE_NUM;i++)
        {
            if(ctrlidx != cc_timer_cfg_functable_t[i].ctrlidx)
            {
                continue;
            }
            /* find */
            *func = cc_timer_cfg_functable_t[i].func;
            result = CC_E_OK;
            break;
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_timer_cfg_servicecall()
****************************************************************************************************/
cc_result cc_timer_cfg_servicecall(cc_uint8 *data,cc_uint16 len)
{
    cc_result result = CC_E_OK;
    cc_timer_cfg_msgformat_union *msg;
    cc_timer_cfg_funcptr_union func;

    do
    {
        /* check parameter */
        CHECK_PTR(result,data);
        func.func = CC_NULL_PTR;
        /* get msg */
        msg = (cc_timer_cfg_msgformat_union *)data;
        CHECK_FUNC(result,cc_timer_cfg_getfunc(msg->msg.ctrl.ctrlidx,(void **)&func.func));
        /* check null pointer */
        CHECK_PTR(result,func.func);
        /* switch */
        switch(msg->msg.ctrl.ctrlidx)
        {
        case CC_TIMER_FUNCCTRLIDX_INIT:
            {
                func.init();
            }
            break;
        case CC_TIMER_FUNCCTRLIDX_DETACH:
            {
                func.detach();
            }
            break;
        case CC_TIMER_FUNCCTRLIDX_CREATE:
            {
                func.create((cc_void *)msg->msg.parameter1,(cc_void *)msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_TIMER_FUNCCTRLIDX_DELETE:
            {
                func.delete((cc_void *)msg->msg.parameter1,msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_TIMER_FUNCCTRLIDX_START:
            {
                func.start((cc_void *)msg->msg.parameter1,(cc_void *)msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_TIMER_FUNCCTRLIDX_STOP:
            {
                func.stop((cc_int8 *)msg->msg.parameter1,(cc_uint32 *)msg->msg.parameter2);
            }
            break;
        case CC_TIMER_FUNCCTRLIDX_GETLOCALTIME:
            {
                func.getlocaltime((cc_int8 *)msg->msg.parameter1,(cc_uint32 *)msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        default:
            break;
        }
        
    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_timer_cfg.c End!
****************************************************************************************************/

