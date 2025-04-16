
/****************************************************************************************************
* File cc_service.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_service.h"
#include "cc_service_cfg.h"
#include "cc_mem.h"
#include "cc_com.h"
#include "cc_list.h"
#include "cc_trace.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* service list */
typedef struct
{
    /* base all discover service list */
    cc_list_struct service;
    /* service */
    cc_list_struct ready;
    cc_list_struct running;
    cc_list_struct block;
    cc_list_struct wait;
    cc_list_struct stop;
    /* service table */
    cc_list_struct alive;
    cc_list_struct dead;
}cc_service_list_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* service init flag */
cc_boolean cc_service_initflag = CC_FALSE;
cc_boolean cc_service_startflag = CC_FALSE;
cc_boolean cc_service_triggerdiscoverflag = CC_FALSE;

/* service list */
cc_service_list_struct cc_service_list_t;

/* module name */
cc_int8 cc_service_name[CC_NAME_MAX_LEN] = "service";

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_service_init()
****************************************************************************************************/
cc_result cc_service_init(void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_service_initflag != CC_TRUE));

        /* init service list */
        cc_list_init(&cc_service_list_t.service);
        cc_list_init(&cc_service_list_t.ready);
        cc_list_init(&cc_service_list_t.running);
        cc_list_init(&cc_service_list_t.block);
        cc_list_init(&cc_service_list_t.wait);
        cc_list_init(&cc_service_list_t.stop);
        cc_list_init(&cc_service_list_t.alive);
        cc_list_init(&cc_service_list_t.dead);

        /* start service discover */
        cc_service_initflag = CC_TRUE;
        cc_service_startflag = CC_TRUE;

        /* init flag */
        cc_service_initflag = CC_TRUE;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_detach()
****************************************************************************************************/
cc_result cc_service_detach(void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* stop service discover */
        cc_service_initflag = CC_FALSE;
        cc_service_startflag = CC_FALSE;

        /* deinit service list */
        cc_list_detach(&cc_service_list_t.service);
        cc_list_detach(&cc_service_list_t.ready);
        cc_list_detach(&cc_service_list_t.running);
        cc_list_detach(&cc_service_list_t.block);
        cc_list_detach(&cc_service_list_t.wait);
        cc_list_detach(&cc_service_list_t.stop);
        cc_list_detach(&cc_service_list_t.alive);
        cc_list_detach(&cc_service_list_t.dead);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_create()
****************************************************************************************************/
cc_result cc_service_create(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        ____________________________TO_DO__________________________
        /* malloc mem */

        /*  */


    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_delete()
****************************************************************************************************/
cc_result cc_service_delete(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        ____________________________TO_DO__________________________
        /* find service */

        /* remove service */

        /* free malloc mem */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_findtable()
****************************************************************************************************/
cc_result cc_service_findtable(cc_int8 *name,cc_service_table_struct **table)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_service_table_struct *temptable;
    cc_uint32 i;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,table);
        /* search service table */
        temptable = cc_service_cfg_gettable();
        for(i = 0;i < CC_SERVICE_CFG_NUMBER;i++)
        {
            /* check name in table */
            CHECK_PTR(result,temptable[i].name);
            if(cc_mem_strncmp(temptable[i].name,name,CC_NAME_MAX_LEN) == CC_E_OK)
            {
                /* find */
                *table = &temptable[i];
                result = CC_E_OK;
                break;
            }
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_find()
****************************************************************************************************/
cc_result cc_service_find(cc_int8 *name,cc_service_struct **service)
{
    cc_result result = CC_E_OK;
    cc_service_table_struct *table;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,service);
        /* search service table */
        CHECK_FUNC(result,cc_service_findtable(name,&table));
        /* output service */
        *service = table->service;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_gettablenum()
****************************************************************************************************/
cc_uint32 cc_service_gettablenum(void)
{
    cc_service_table_struct *temptable;
    cc_uint32 num;
    cc_uint32 namelen;
    cc_uint32 i;

    do
    {
        /* get free table */
        num = 0;
        temptable = cc_service_cfg_gettable();
        /* foreach */
        for(i = 0;i < CC_SERVICE_CFG_NUMBER;i++)
        {
            /* get service name len */
            if(cc_mem_strlen(temptable[i].name,&namelen) != CC_E_OK)
            {
                continue;
            }

            /* check service name len */
            if(namelen <= 0)
            {
                continue;
            }

            /* find a service */
            num++;
        }
    }while(0u);

    return num;
}

/****************************************************************************************************
* cc_service_getfreetable()
****************************************************************************************************/
cc_result cc_service_getfreetable(cc_service_table_struct **table)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_service_table_struct *temptable;
    cc_uint32 len;
    cc_uint32 i;

    do
    {
        /* check parameter */
        CHECK_PTR(result,table);
        /* get free table */
        len = 0;
        temptable = cc_service_cfg_gettable();
        for(i = 0;i < CC_SERVICE_CFG_NUMBER;i++)
        {
            /* check name */
            if(cc_mem_strlen(temptable[i].name,&len) == CC_E_OK)
            {
                continue;
            }
            /* get a free service table */
            *table = &temptable[i];
            result = CC_E_OK;
            break;
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_inserttable()
****************************************************************************************************/
cc_result cc_service_inserttable(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_service_table_struct *table;

    do
    {
        /* check parameter */
        CHECK_PTR(result,service);
        /* find service in table */
        CHECK_PTR(result,service->name);
        CHECK_LOGIC(result,(cc_service_findtable(service->name,&table) == CC_E_NOT_OK_NOT_FIND));
        /* get free table */
        CHECK_FUNC(result,cc_service_getfreetable(&table));
        /* insert info */
        table->ctrlidx = cc_service_gettablenum();
        cc_mem_strncpy(table->name,service->name,CC_NAME_MAX_LEN);
        table->service = service;
        table->level = service->level;
        table->method = service->method;
        table->type = service->type;
        table->state = CC_SERVICE_STATE_INIT;
        table->version = service->info.version;
        table->func = &service->func;
        table->parent = service->parent;
        table->list = &service->list;
        cc_mem_strncpy(table->log,service->info.log,CC_LOG_MAX_LEN);
        table->inittime = service->info.inittime;
        table->starttime = service->info.starttime;
        table->stoptime = service->info.stoptime;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_removetable()
****************************************************************************************************/
cc_result cc_service_removetable(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_service_table_struct *table;

    do
    {
        /* check parameter */
        CHECK_PTR(result,service);
        /* find service in table */
        CHECK_PTR(result,service->name);
        CHECK_FUNC(result,cc_service_findtable(service->name,&table));
        /* clear service name */
        CHECK_FUNC(result,cc_mem_set(table->name,0x00,CC_NAME_MAX_LEN));
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_register()
****************************************************************************************************/
cc_result cc_service_register(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_service_table_struct *table;

    do
    {
        /* check parameter */
        CHECK_PTR(result,service);
        /* check init */
        CHECK_LOGIC(result,(cc_service_initflag == CC_TRUE));
        /* find service in table */
        CHECK_PTR(result,service->name);
        CHECK_LOGIC(result,(cc_service_findtable(service->name,&table) == CC_E_NOT_OK_NOT_FIND));
        /* insert service in table */
        CHECK_FUNC(result,cc_service_inserttable(service));
        /* set flag */
        cc_service_triggerdiscoverflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_deregister()
****************************************************************************************************/
cc_result cc_service_deregister(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_service_table_struct *table;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        /* find service in table */
        CHECK_FUNC(result,cc_service_findtable(name,&table));
        /* remove service in table */
        CHECK_FUNC(result,cc_mem_set(table->name,0x00,CC_NAME_MAX_LEN));

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_start()
****************************************************************************************************/
cc_result cc_service_start(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_service_table_struct *table;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        /* find service in table */
        CHECK_FUNC(result,cc_service_findtable(name,&table));
        /* set service state */
        table->state = CC_SERVICE_STATE_READY;
        /* insert ready list */
        cc_list_insert_after(&cc_service_list_t.ready,table->list);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_stop()
****************************************************************************************************/
cc_result cc_service_stop(cc_int8 *name)
{
    cc_result result = CC_E_OK;
    cc_service_table_struct *table;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        /* find service in table */
        CHECK_FUNC(result,cc_service_findtable(name,&table));
        /* set service state */
        table->state = CC_SERVICE_STATE_STOP;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_discoveralive()
****************************************************************************************************/
cc_result cc_service_findinlist(cc_list_struct *dstlist,cc_list_struct *srclist)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dstlist);
        CHECK_PTR(result,srclist);

        /* search */
        CHECK_FUNC(result,cc_list_search(dstlist,srclist));

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_discovernew()
****************************************************************************************************/
cc_result cc_service_discovernew(void)
{
    cc_result result = CC_E_OK;
    cc_service_table_struct *temptable;
    cc_uint32 i;

    do
    {
        /* get config service table */
        temptable = cc_service_cfg_gettable();
        CHECK_PTR(result,temptable);

        for(i = 0;i < CC_SERVICE_CFG_NUMBER;i++)
        {
            /* find in list */
            if(cc_service_findinlist(&cc_service_list_t.service,temptable[i].list) == CC_E_OK)
            {
                continue;
            }
            /* insert list */
            cc_list_insert_after(&cc_service_list_t.service,temptable[i].list);
            /* insert alive/dead to check alive */
            cc_list_insert_after(&cc_service_list_t.dead,temptable[i].list);
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_send()
****************************************************************************************************/
cc_result cc_service_send(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type)
{
    cc_result result = CC_E_OK;
    cc_service_cfg_msgformat_union msg;
    cc_service_table_struct *srctable;
    cc_service_table_struct *dsttable;

    do
    {
        /* 1.check parameter */
        CHECK_PTR(result,dstname);
        CHECK_PTR(result,srcname);
        CHECK_PTR(result,data);

        /* 2.1 check src service */
        CHECK_FUNC(result,cc_service_findtable(srcname,&srctable));
        /* 2.2 find dst service */
        CHECK_FUNC(result,cc_service_findtable(dstname,&dsttable));

        /* 3 fill msg head */
        msg.msg.head.bytes[0] = 0xCC;
        msg.msg.head.bytes[1] = 0xCC;
        /* fill msg len */
        msg.msg.len.value = len;
        /* fill msg user */
        msg.msg.user.value = 0;
        /* fill msg type */
        msg.msg.type = type;
        /* fill msg srcname */
        CHECK_FUNC(result,cc_mem_strncpy(msg.msg.srcname,srcname,CC_NAME_MAX_LEN));
        /* fill msg dstname */
        CHECK_FUNC(result,cc_mem_strncpy(msg.msg.dstname,dstname,CC_NAME_MAX_LEN));
        /* fill msg data */
        CHECK_FUNC(result,cc_mem_cpy(msg.msg.data,data,len));
        /* fill crc */
        ____________________________TO_DO__________________________
        msg.msg.crc.value = 0xCC;
        /* call service recv */
        /* local service */
        switch(dsttable->method)
        {
        case CC_SERVICE_METHOD_LOCAL:
            {
                CHECK_FUNC(result,cc_service_recv(dstname,srcname,msg.bytes,len,type));
            }
            break;
        case CC_SERVICE_METHOD_REMOTE:
            {
                /* remote service */
                ____________________________TO_DO__________________________
            }
            break;
        default:
            break;
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_recv_checkhead()
****************************************************************************************************/
cc_result cc_service_recv_checkhead(cc_uint8 *data,cc_uint16 len)
{
    cc_result result = CC_E_OK;
    cc_uint8 head[2] = {0xCC,0xCC};

    do
    {
        /* check parameter */
        CHECK_PTR(result,data);
        CHECK_LOGIC(result,(len >= 2));

        /* cmp head */
        CHECK_FUNC(result,cc_mem_cmp(head,data,2));

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_reloadagingtime()
****************************************************************************************************/
cc_result cc_service_reloadagingtime(cc_int8 *name)
{
    cc_result result = CC_E_OK; 
    cc_service_table_struct *table;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        /* find service in table */
        CHECK_FUNC(result,cc_service_findtable(name,&table));
        /* remove dead list & insert alive list */
        cc_list_remove(table->list);
        cc_list_insert_after(&cc_service_list_t.alive,table->list);
        /* set service state */
        table->agingtime = CC_SERVICE_CFG_AGINGTIME;
        table->state = CC_SERVICE_STATE_ALIVE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_recvself()
****************************************************************************************************/
cc_result cc_service_recvself(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dstname);
        CHECK_PTR(result,srcname);
        CHECK_PTR(result,data);
        CHECK_FUNC(result,cc_mem_strncmp(cc_service_name,dstname,CC_NAME_MAX_LEN));

        /* check data */

        /* type */
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

            }
            break;
        case CC_SERVICE_MSGTYPE_SERVICE_ALIVE:
            {
                /* reload service aging time */
                cc_service_reloadagingtime(srcname);
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
* cc_service_recv()
****************************************************************************************************/
cc_result cc_service_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type)
{
    cc_result result = CC_E_OK;
    cc_service_cfg_msgformat_union *msg;
    cc_service_table_struct *srctable;
    cc_service_table_struct *dsttable;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dstname);
        CHECK_PTR(result,srcname);
        CHECK_PTR(result,data);

        /* check head */
        CHECK_FUNC(result,cc_service_recv_checkhead(data,len));
        /* format data */
        msg = (cc_service_cfg_msgformat_union *)data;
        /* check crc */
        ____________________________TO_DO__________________________
        /* check src service */
        CHECK_FUNC(result,cc_service_findtable(srcname,&srctable));
        /* switch self or other service */
        if(cc_mem_strncmp(cc_service_name,dstname,CC_NAME_MAX_LEN))
        {
            /* recv self */
            cc_service_recvself(dstname,srcname,msg->msg.data,len,type);
        }
        else
        {
            /* find dst service */
            CHECK_FUNC(result,cc_service_findtable(dstname,&dsttable));
            /* check alive */
            CHECK_LOGIC(result,(dsttable->state == CC_SERVICE_STATE_ALIVE));
            /* recv switch type */
            ____________________________TO_DO__________________________
            /* recv switch msgtype */
            dsttable->func->recv(dstname,srcname,msg->msg.data,len,type);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_discoveralive_local()
****************************************************************************************************/
cc_result cc_service_discoveralive_local(cc_int8 *servicename)
{
    cc_result result = CC_E_OK;
    cc_uint8 data[4] = {0xCC,0xCC,0xCC,0xCC};

    do
    {
        /* check parameter */
        CHECK_PTR(result,servicename);
        /* send alive message */
        CHECK_FUNC(result,cc_service_send(servicename,cc_service_name,data,4,CC_SERVICE_MSGTYPE_SERVICE_ALIVE));
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_discoveralive_remote()
****************************************************************************************************/
cc_result cc_service_discoveralive_remote(cc_int8 *servicename)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,servicename);
        /* create call func message */
        ____________________________TO_DO__________________________
        /* create func parameter message */

        /* create alive message */

        /* send message */

    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_service_discoverstate()
****************************************************************************************************/
cc_result cc_service_discoverstate(void)
{
    cc_result result = CC_E_OK;
    cc_list_struct *headlist;
    cc_list_struct *iterator;
    cc_service_table_struct *table;
    cc_service_struct *service;

    do
    {
        /* forech all service list */
        iterator = &cc_service_list_t.service;
        CHECK_PTR(result,iterator);
        headlist = iterator;
        while(iterator->next != CC_NULL_PTR)
        {
            /* get table */
            service = CC_SERVICE_REFLECT_LIST(iterator);
            cc_service_findtable(service->name,&table);
            CHECK_PTR(result,table);

            /* get service agingtime */
            if(table->agingtime > 0)
            {
                /* set state */
                table->state = CC_SERVICE_STATE_ALIVE;
                table->agingtime--;
            }
            else
            {
                /* set state */
                table->state = CC_SERVICE_STATE_DEAD;
                /* remove alive list & insert dead list */
                cc_list_remove(table->list);
                cc_list_insert_after(&cc_service_list_t.dead,table->list);
            }

            /* tail list */
            if(iterator->next == headlist)
            {
                break;
            }
            /* next */
            iterator = iterator->next;
        }
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_service_discoveralive()
****************************************************************************************************/
cc_result cc_service_discoveralive(void)
{
    cc_result result = CC_E_OK;
    cc_list_struct *headlist;
    cc_list_struct *iterator;
    cc_service_table_struct *table;
    cc_service_struct *service;

    do
    {
        /* foreach service dead list */
        iterator = &cc_service_list_t.dead;
        CHECK_PTR(result,iterator);
        headlist = iterator;
        while(iterator->next != CC_NULL_PTR)
        {
            /* get table */
            service = CC_SERVICE_REFLECT_LIST(iterator);
            cc_service_findtable(service->name,&table);
            CHECK_PTR(result,table);

            /* switch local service or remote */
            switch(table->method)
            {
            case CC_SERVICE_METHOD_LOCAL:
                {
                    /* com with local service */
                    cc_service_discoveralive_local(table->name);
                }
                break;
            case CC_SERVICE_METHOD_REMOTE:
                {
                    /* com with remote service */
                    cc_service_discoveralive_remote(table->name);
                }
                break;
            
            default:
                break;
            }

            /* tail list */
            if(iterator->next == headlist)
            {
                break;
            }
            /* next */
            iterator = iterator->next;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_discover()
****************************************************************************************************/
cc_result cc_service_discover(void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* to find alive service trigger or timeout */
        if(!((cc_service_triggerdiscoverflag == CC_TRUE) || (CC_FALSE)))
        {
            continue;
        }

        /* find service */
        cc_service_discovernew();
        /* alive service */
        cc_service_discoveralive();
        /* service state */
        cc_service_discoverstate();
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_call()
****************************************************************************************************/
cc_result cc_service_call(cc_uint32 ctrlidx,cc_int8 *servicename,cc_uint8 *data)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_callback()
****************************************************************************************************/
cc_result cc_service_callback(cc_uint32 ctrlidx,cc_int8 *servicename,cc_uint8 *data)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_callmainfuntion()
****************************************************************************************************/
cc_result cc_service_callmainfuntion_local(cc_service_struct *service)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,service);
        CHECK_PTR(result,service->scheduler.mainfunction);
        /* run mainfunction of alive service */
        service->scheduler.mainfunction();
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_callmainfuntion()
****************************************************************************************************/
cc_result cc_service_callmainfuntion_remote(cc_service_struct *service)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,service);

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_callmainfuntion()
****************************************************************************************************/
cc_result cc_service_callmainfuntion(cc_void)
{
    cc_result result = CC_E_OK;
    cc_list_struct *headlist;
    cc_list_struct *iterator;
    cc_service_table_struct *table;
    cc_service_struct *service;

    do
    {
        /* get alive service */
        /* foreach service dead list */
        iterator = &cc_service_list_t.alive;
        CHECK_PTR(result,iterator);
        headlist = iterator;
        while(iterator->next != CC_NULL_PTR)
        {
            /* get service */
            service = CC_SERVICE_REFLECT_LIST(iterator);
            cc_service_findtable(service->name,&table);
            CHECK_PTR(result,table);

            /* switch local service or remote */
            switch(table->method)
            {
            case CC_SERVICE_METHOD_LOCAL:
                {
                    /* com with local service */
                    cc_service_callmainfuntion_local(service);
                }
                break;
            case CC_SERVICE_METHOD_REMOTE:
                {
                    /* com with remote service */
                    cc_service_callmainfuntion_remote(service);
                }
                break;
            
            default:
                break;
            }

            /* tail list */
            if(iterator->next == headlist)
            {
                break;
            }
            /* next */
            iterator = iterator->next;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_service_mainfunction()
****************************************************************************************************/
cc_result cc_service_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* service discover */
        cc_service_discover();
        /* service mainfunction */
        cc_service_callmainfuntion();

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_service.c End!
****************************************************************************************************/

