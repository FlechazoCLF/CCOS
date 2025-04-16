
/****************************************************************************************************
* File cc_mem.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_mem.h"
#include "cc_trace.h"
#include "cc_kernel.h"
#include "cc_list.h"
#include "cc_mem_cfg.h"
#include "cc_timer.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/
/* mem */
cc_mem_struct cc_mem_t;
/* init flag */
cc_boolean cc_mem_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_mem_object_init()
****************************************************************************************************/
cc_result cc_mem_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "mem obj";
    cc_int8 log[CC_LOG_MAX_LEN] = "mem obj init";

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
        object->id = CC_SERVICE_TYPE_MEMORY;
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
* cc_mem_service_init()
****************************************************************************************************/
cc_result cc_mem_service_init(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_int8 *name = "mem";
    cc_int8 *log = "mem service init";

    do
    {
        /* check parameter */
        CHECK_PTR(result,service);
        /* impletement */
        /* parent */
        service->parent = CC_NULL_PTR;
        /* object */
        service->object = &cc_mem_t.object;
        /* name */
        cc_mem_strncpy(service->name,name,CC_NAME_MAX_LEN);
        /* method */
        service->method = CC_SERVICE_METHOD_LOCAL;
        /* level */
        service->level = CC_SERVICE_LEVEL_KERNEL;
        /* type */
        service->type = CC_SERVICE_TYPE_MEMORY;
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
        service->scheduler.init = cc_mem_init;
        service->scheduler.mainfunction = cc_mem_mainfunction;
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
* cc_mem_internal_init()
****************************************************************************************************/
cc_result cc_mem_internal_init(cc_mem_struct *mem)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,mem);
        /* impletement */
        mem->func.init = cc_mem_init;
        mem->func.detach = cc_mem_detach;
        mem->func.memcpy = cc_mem_cpy;
        mem->func.memset = cc_mem_set;
        mem->func.memcmp = cc_mem_cmp;
        mem->func.strlen = cc_mem_strlen;
        mem->func.strnlen = cc_mem_strnlen;
        mem->func.strcpy = cc_mem_strcpy;
        mem->func.strncpy = cc_mem_strncpy;
        mem->func.strcmp = cc_mem_strcmp;
        mem->func.strncmp = cc_mem_strncmp;
        mem->func.strstr = cc_mem_strstr;
        mem->func.strchr = cc_mem_strchr;
        mem->func.strtok = cc_mem_strtok;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_init()
****************************************************************************************************/
cc_result cc_mem_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_mem_initflag != CC_TRUE));
        
        /* init mem object */
        cc_mem_object_init(&cc_mem_t.object);
        /* register object */
        cc_object_register(&cc_mem_t.object);

        /* init mem */
        cc_mem_internal_init(&cc_mem_t);

        /* init service */
        cc_mem_service_init(&cc_mem_t.service);
        /* register service */
        cc_service_register(&cc_mem_t.service);

        /* start service */
        cc_service_start("mem");

        /* init flag */
        cc_mem_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_detach()
****************************************************************************************************/
cc_result cc_mem_detach(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* stop service */
        cc_service_stop("mem");
        /* deregister object */
        cc_object_deregister("mem");
        /* deregister service */
        cc_service_deregister("mem");
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_cpy()
****************************************************************************************************/
cc_result cc_mem_cpy(cc_void *dst,cc_void *src,cc_uint32 len)
{
    cc_result result = CC_E_OK;
    cc_uint8 *pDst;
    cc_uint8 *pSrc;
    cc_uint32 l;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);

        /* get pointer */
        pDst = (cc_uint8 *)dst;
        pSrc = (cc_uint8 *)src;

        /* Copy Algorithm */
        /* 
         *      |    len     |               |    len     |
         * ------------------------ 1     ------------------------ 2
         *      ^              ^             ^              ^
         *     dst            src           src            dst
         * 
         *      |    len xxxx|               |    len xxxx|
         * ------------------------ 3     ------------------------ 4
         *      ^        ^                   ^        ^
         *     dst      src                 src      dst
         */
        if((pDst <= pSrc)||(pDst > (pSrc + len)))
        {
            /* branch1 (1,2,3) */
            while(len--)
            {
                *pDst++ = *pSrc++;
            }
        }
        else
        {
            /* branch2 (4) */
            for(l = len;l > 0; l--)
            {
                pDst[l-1] = pSrc[l-1];
            }
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_set()
****************************************************************************************************/
cc_result cc_mem_set(cc_void *dst,cc_uint32 value,cc_uint32 len)
{
    cc_result result = CC_E_OK;
    cc_uint8 *pDst;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);

        /* set */
        pDst = (cc_uint8 *)dst;
        while(len--)
        {
            *pDst++ = value;
        }
        
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_cmp()
****************************************************************************************************/
cc_result cc_mem_cmp(cc_void *dst,cc_void *src,cc_uint32 len)
{
    cc_result result = CC_E_OK;
    cc_uint8 *pDst;
    cc_uint8 *pSrc;
    
    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);

        /* get pointer */
        pDst = (cc_uint8 *)dst;
        pSrc = (cc_uint8 *)src;
        /* compare */
        while(len--)
        {
            CHECK_LOGIC(result,(*pDst++ == *pSrc++));
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strlen()
****************************************************************************************************/
cc_result cc_mem_strlen(cc_int8 *src,cc_uint32 *len)
{
    cc_result result = CC_E_OK;
    const char *str;

    do
    {
        /* check parameter */
        CHECK_PTR(result,src);
        CHECK_PTR(result,len);

        /* impletement */
        str = src;
        while((*str) != '\0')
        {
            str++;
        }
        /* len */
        *len = (str - src);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strnlen()
****************************************************************************************************/
cc_result cc_mem_strnlen(cc_int8 *src,cc_uint32 *len,cc_uint32 maxlen)
{
    cc_result result = CC_E_OK;
    const char *str;

    do
    {
        /* check parameter */
        CHECK_PTR(result,src);
        CHECK_PTR(result,len);

        /* impletement */
        str = src;
        while(((*str) != '\0') && ((str - src) < maxlen))
        {
            str++;
        }
        /* len */
        *len = (str - src);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strcpy()
****************************************************************************************************/
cc_result cc_mem_strcpy(cc_int8 *dst,cc_int8 *src)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);

        /* impletement */
        while((*src) != '\0')
        {
            (*dst++) = (*src++);
        }
        (*dst) = '\0';

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strncpy()
****************************************************************************************************/
cc_result cc_mem_strncpy(cc_int8 *dst,cc_int8 *src,cc_uint32 maxlen)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);

        /* impletement */
        while(((*src) != '\0') && ((maxlen--) != 0))
        {
            (*dst++) = (*src++);
        }
        (*dst) = '\0';
        
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strcmp()
****************************************************************************************************/
cc_result cc_mem_strcmp(cc_int8 *dst,cc_int8 *src)
{
    cc_result result = CC_E_OK;
    cc_int32 value;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);

        /* impletement */
        while(((*src) != '\0') && ( (*src++) == (*dst++) ))
        {
            /* code */
        }

        /* get diff */
        value = (*src) - (*dst);
        
        if(value == 0)
        {
            /* do nothing */
        }
        else if (value > 0)
        {
            result = CC_E_NOT_OK_BIGGER;
        }
        else
        {
            result = CC_E_NOT_OK_SMALLER;
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strncmp()
****************************************************************************************************/
cc_result cc_mem_strncmp(cc_int8 *dst,cc_int8 *src,cc_uint32 maxlen)
{
    cc_result result = CC_E_OK;
    cc_int32 value;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);

        /* impletement */
        while(((*src) != '\0') && ((maxlen--) != 0) && ( (*src++) == (*dst++) ))
        {
            /* code */
        }

        /* get diff */
        value = (*src) - (*dst);
        
        if(value == 0)
        {
            /* do nothing */
        }
        else if (value > 0)
        {
            result = CC_E_NOT_OK_BIGGER;
        }
        else
        {
            result = CC_E_NOT_OK_SMALLER;
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strstr()
****************************************************************************************************/
cc_result cc_mem_strstr(cc_int8 *dst,cc_int8 *src,cc_int8 **findstr)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_uint32 srclen;
    cc_uint32 dstlen;
    cc_int8 *str;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);
        CHECK_PTR(result,findstr);

        /* impletement */
        str = dst;
        *findstr = CC_NULL;
        /* get len */ 
        CHECK_FUNC(result,cc_mem_strlen(src,&srclen));
        CHECK_FUNC(result,cc_mem_strlen(dst,&dstlen));
        /* find */
        while(dstlen >= srclen)
        {
            if(cc_mem_strcmp(str,src) == CC_E_OK)
            {
                *findstr = str;
                result = CC_E_OK;
                break;
            }
            str++;
            dstlen--;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strchr()
****************************************************************************************************/
cc_result cc_mem_strchr(cc_int8 **dst,cc_int8 *src,cc_int8 ch)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);
        CHECK_LOGIC(result,(ch != '\0'));

        /* impletement */
        /* find */
        while(*src != '\0')
        {
            if(*src == ch)
            {
                *dst = src;
                result = CC_E_OK;
                break;
            }
            src++;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_mem_strtok()
****************************************************************************************************/
cc_result cc_mem_strtok(cc_int8 *dst,cc_int8 **src,cc_int8 *delimiter)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_int8 *srcstr;
    cc_uint32 srclen;
    cc_uint32 delimiterlen;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dst);
        CHECK_PTR(result,src);
        CHECK_PTR(result,delimiter);

        /* impletement */
        srcstr = *src;
        /* get len */ 
        CHECK_FUNC(result,cc_mem_strlen(*src,&srclen));
        CHECK_FUNC(result,cc_mem_strlen(delimiter,&delimiterlen));
        /* check */
        CHECK_LOGIC(result,(delimiterlen < srclen));
        /* find */
        while(**src != '\0')
        {
            /* check */
            if(cc_mem_strcmp(delimiter,*src) == CC_E_OK)
            {
                /* output */
                cc_mem_strncpy(dst,srcstr,(*src - srcstr));
                /* shift */
                *src += delimiterlen;
                /* return */
                result = CC_E_OK;
                break;
            }
            *src++;
        }
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
        CHECK_FUNC(result,cc_mem_strncmp(cc_mem_t.service.name,dstname,CC_NAME_MAX_LEN));
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
                CHECK_FUNC(result,cc_mem_cfg_servicecall(data,len));
            }
            break;
        case CC_SERVICE_MSGTYPE_SERVICE_ALIVE:
            {
                /* set flag then send to service alive */
                cc_mem_t.service.func.send(srcname,dstname,data,len,CC_SERVICE_MSGTYPE_SERVICE_ALIVE);
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
* cc_mem_mainfunction()
****************************************************************************************************/
cc_result cc_mem_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* service send & recv list */
        ____________________________TO_DO__________________________

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_mem.c End!
****************************************************************************************************/

