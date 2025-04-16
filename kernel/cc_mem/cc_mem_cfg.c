
/****************************************************************************************************
* File cc_mem_cfg.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_mem_cfg.h"
#include "cc_mem.h"
#include "cc_trace.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* interface information */
cc_mem_cfg_functable_struct cc_mem_cfg_functable_t[CC_MEM_CFG_FUNCTABLE_NUM] = 
{
    /*      .ctrlidx,              .funcname,    .func,        .parameter,                                     .info */
    { CC_MEM_FUNCCTRLIDX_INIT    ,   "init"    , cc_mem_init    , "cc_void"                                      , "1"},
    { CC_MEM_FUNCCTRLIDX_DETACH  ,   "detach"  , cc_mem_detach  , "cc_void"                                      , "2"},
    { CC_MEM_FUNCCTRLIDX_MEMCPY  ,   "memcpy"  , cc_mem_cpy     , "cc_void *dst,cc_void *src,cc_uint32 len"      , "3"},
    { CC_MEM_FUNCCTRLIDX_MEMSET  ,   "memset"  , cc_mem_set     , "cc_void *dst,cc_uint32 value,cc_uint32 len"   , "4"},
    { CC_MEM_FUNCCTRLIDX_MEMCMP  ,   "memcmp"  , cc_mem_cmp     , "cc_void *dst,cc_void *src,cc_uint32 len"      , "5"},
    { CC_MEM_FUNCCTRLIDX_STRLEN  ,   "strlen"  , cc_mem_strlen  , "cc_int8 *src,cc_uint32 *len"                  , "6"},
    { CC_MEM_FUNCCTRLIDX_STRNLEN ,   "strnlen" , cc_mem_strnlen , "cc_int8 *src,cc_uint32 *len,cc_uint32 maxlen" , "7"},
    { CC_MEM_FUNCCTRLIDX_STRCPY  ,   "strcpy"  , cc_mem_strcpy  , "cc_int8 *dst,cc_int8 *src"                    , "8"},
    { CC_MEM_FUNCCTRLIDX_STRNCPY ,   "strncpy" , cc_mem_strncpy , "cc_int8 *dst,cc_int8 *src,cc_uint32 maxlen"   , "9"},
    { CC_MEM_FUNCCTRLIDX_STRCMP  ,   "strcmp"  , cc_mem_strcmp  , "cc_int8 *dst,cc_int8 *src"                    , "10"},
    { CC_MEM_FUNCCTRLIDX_STRNCMP ,   "strncmp" , cc_mem_strncmp , "cc_int8 *dst,cc_int8 *src,cc_uint32 maxlen"   , "11"},
    { CC_MEM_FUNCCTRLIDX_STRSTR  ,   "strstr"  , cc_mem_strstr  , "cc_int8 *dst,cc_int8 *src,cc_int8 **findstr"  , "12"},
};

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_mem_cfg_getfuncname()
****************************************************************************************************/
cc_result cc_mem_cfg_getfuncname(cc_uint8 ctrlidx,cc_int8 **name)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_uint8 i;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        /* foreach */
        for(i = 0;i < CC_MEM_CFG_FUNCTABLE_NUM;i++)
        {
            if(ctrlidx != cc_mem_cfg_functable_t[i].ctrlidx)
            {
                continue;
            }
            /* find */
            *name = cc_mem_cfg_functable_t[i].funcname;
            result = CC_E_OK;
            break;
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_cfg_getfunc()
****************************************************************************************************/
cc_result cc_mem_cfg_getfunc(cc_uint8 ctrlidx,void **func)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_uint8 i;

    do
    {
        /* check parameter */
        CHECK_PTR(result,func);
        /* foreach */
        for(i = 0;i < CC_MEM_CFG_FUNCTABLE_NUM;i++)
        {
            if(ctrlidx != cc_mem_cfg_functable_t[i].ctrlidx)
            {
                continue;
            }
            /* find */
            *func = cc_mem_cfg_functable_t[i].func;
            result = CC_E_OK;
            break;
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_cfg_servicecall()
****************************************************************************************************/
cc_result cc_mem_cfg_servicecall(cc_uint8 *data,cc_uint16 len)
{
    cc_result result = CC_E_OK;
    cc_mem_cfg_msgformat_union *msg;
    cc_mem_cfg_funcptr_union func;

    do
    {
        /* check parameter */
        CHECK_PTR(result,data);
        func.func = CC_NULL_PTR;
        /* get msg */
        msg = (cc_mem_cfg_msgformat_union *)data;
        CHECK_FUNC(result,cc_mem_cfg_getfunc(msg->msg.ctrl.ctrlidx,(void **)&func.func));
        /* check null pointer */
        CHECK_PTR(result,func.func);
        /* switch */
        switch(msg->msg.ctrl.ctrlidx)
        {
        case CC_MEM_FUNCCTRLIDX_INIT:
            {
                func.init();
            }
            break;
        case CC_MEM_FUNCCTRLIDX_DETACH:
            {
                func.detach();
            }
            break;
        case CC_MEM_FUNCCTRLIDX_MEMCPY:
            {
                func.memcpy((cc_void *)msg->msg.parameter1,(cc_void *)msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_MEMSET:
            {
                func.memset((cc_void *)msg->msg.parameter1,msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_MEMCMP:
            {
                func.memcmp((cc_void *)msg->msg.parameter1,(cc_void *)msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_STRLEN:
            {
                func.strlen((cc_int8 *)msg->msg.parameter1,(cc_uint32 *)msg->msg.parameter2);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_STRNLEN:
            {
                func.strnlen((cc_int8 *)msg->msg.parameter1,(cc_uint32 *)msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_STRCPY:
            {
                func.strcpy((cc_int8 *)msg->msg.parameter1,(cc_int8 *)msg->msg.parameter2);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_STRNCPY:
            {
                func.strncpy((cc_int8 *)msg->msg.parameter1,(cc_int8 *)msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_STRCMP:
            {
                func.strcmp((cc_int8 *)msg->msg.parameter1,(cc_int8 *)msg->msg.parameter2);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_STRNCMP:
            {
                func.strncmp((cc_int8 *)msg->msg.parameter1,(cc_int8 *)msg->msg.parameter2,msg->msg.parameter3);
            }
            break;
        case CC_MEM_FUNCCTRLIDX_STRSTR:
            {
                func.strstr((cc_int8 *)msg->msg.parameter1,(cc_int8 *)msg->msg.parameter2,(cc_int8 **)msg->msg.parameter3);
            }
            break;
        
        default:
            break;
        }
        
    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_mem_cfg.c End!
****************************************************************************************************/

