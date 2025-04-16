
/****************************************************************************************************
* File cc_flash.c Start!
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
 * 2025-04-11     cc          the first version
 *
*/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_flash.h"
#include "cc_kernel.h"
/* log */
#include "cc_trace.h"
/* sub module */
#include "cc_flash_cfg.h"
#include "cc_flash_device_cfg.h"
/* components */
#include "cc_mem.h"
#include "cc_heap.h"
#include "cc_list.h"
#include "cc_timer.h"
#include "cc_algorithm_verify.h"
#include "cc_algorithm_search.h"

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

/* cc_flash */
cc_flash_struct cc_flash_t;
/* init flag */
cc_boolean cc_flash_initflag = CC_FALSE;
/* page header id */
cc_uint8 cc_flash_headerid[CC_FLASH_PAGE_HEADER_ID_LEN] = {0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC};
/* free value */
cc_uint8 cc_flash_freevalue[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_flash_object_init()
****************************************************************************************************/
cc_result cc_flash_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 name[CC_NAME_MAX_LEN] = "flash obj";
    cc_int8 log[CC_LOG_MAX_LEN] = "flash obj init";

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
* cc_flash_service_init()
****************************************************************************************************/
cc_result cc_flash_service_init(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_int8 *name = "flash";
    cc_int8 *log = "flash service init";

    do
    {
        /* check parameter */
        CHECK_PTR(result,service);
        /* impletement */
        /* parent */
        service->parent = CC_NULL_PTR;
        /* object */
        service->object = &cc_flash_t.object;
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
        service->scheduler.init = cc_flash_init;
        service->scheduler.mainfunction = cc_flash_mainfunction;
        /* signal */
        service->signal.mutex = 0;
        service->signal.event = 0;
        service->signal.semaphore = 0;
        service->signal.signal = 0;
        /* func */
        service->func.send = cc_service_send;
        service->func.recv = cc_flash_recv;
        /* state */
        service->info.state = CC_SERVICE_STATE_INIT;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_get_headerid()
****************************************************************************************************/
cc_result cc_flash_get_headerid(cc_uint8 *header)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,header);
        /* impletement */
        /* check id */
        CHECK_FUNC(result,cc_mem_cpy(header,cc_flash_headerid,CC_FLASH_PAGE_HEADER_ID_LEN));
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_check_header()
****************************************************************************************************/
cc_result cc_flash_check_header(cc_flash_info_header_struct *header,cc_flash_page_type_enum type)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,header);
        /* impletement */
        /* check id */
        CHECK_FUNC(result,cc_mem_cmp(cc_flash_headerid,header->id,CC_FLASH_PAGE_HEADER_ID_LEN));
        /* check type */
        CHECK_LOGIC(result,(header->type == type));
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_mainpage()
****************************************************************************************************/
cc_result cc_flash_internal_init_mainpage(cc_flash_info_main_struct *mainpage)
{
    cc_result result = CC_E_OK;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN] = "flash main page";
    /* author */
    cc_int8 author[CC_NAME_MAX_LEN] = "flechazo";
    /* information */
    cc_int8 information[CC_NAME_MAX_LEN] = "flash main page";

    do
    {
        /* check parameter */
        CHECK_PTR(result,mainpage);
        /* impletement */
        /* init */
        /* header */
        cc_mem_cpy(mainpage->id,cc_flash_headerid,CC_FLASH_PAGE_HEADER_ID_LEN);
        /* type */
        mainpage->type = CC_FLASH_PAGE_TYPE_MAIN;
        /* name */
        cc_mem_strncpy(mainpage->name,name,CC_NAME_MAX_LEN);
        cc_mem_strncpy(mainpage->author,author,CC_NAME_MAX_LEN);
        /* author */
        cc_mem_strncpy(mainpage->information,information,CC_NAME_MAX_LEN);
        /* version */
        mainpage->version = CC_FLASH_VERSION;
        /* verify */
        ____________________________TO_DO__________________________
        cc_uint8 verify;
        cc_algorithm_verify_sum(&verify,(cc_uint8 *)mainpage,(sizeof(cc_flash_info_main_struct) - sizeof(mainpage->reserve) - sizeof(mainpage->verify)));
        mainpage->verify = verify;
        /* reserve */
        cc_mem_set(mainpage->reserve,0xFF,sizeof(mainpage->reserve));
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_sizepage_totlesize()
****************************************************************************************************/
cc_result cc_flash_internal_init_sizepage_totlesize(cc_uint32 *totlesize)
{
    cc_result result = CC_E_OK;
    cc_uint32 devicetotlesize;

    do
    {
        /* check parameter */
        CHECK_PTR(result,totlesize);
        /* impletement */
        for (cc_uint32 i = 0; i < cc_flash_t.info.devpage.num; i++)
        {
            cc_flash_device_cfg_gettotlesize(i,&devicetotlesize);
            *totlesize += devicetotlesize;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_sizepage_usesize()
****************************************************************************************************/
cc_result cc_flash_internal_init_sizepage_usesize(cc_uint32 *usesize)
{
    cc_result result = CC_E_OK;
    cc_uint32 deviceusesize;

    do
    {
        /* check parameter */
        CHECK_PTR(result,usesize);
        /* impletement */
        for (cc_uint32 i = 0; i < cc_flash_t.info.devpage.num; i++)
        {
            cc_flash_device_cfg_getusesize(i,&deviceusesize);
            *usesize += deviceusesize;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_sizepage()
****************************************************************************************************/
cc_result cc_flash_internal_init_sizepage(cc_flash_info_size_struct *sizepage)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,sizepage);
        /* impletement */
        /* init */
        cc_mem_cpy(sizepage->id,cc_flash_headerid,CC_FLASH_PAGE_HEADER_ID_LEN);
        sizepage->type = CC_FLASH_PAGE_TYPE_SIZE;
        cc_flash_internal_init_sizepage_totlesize(&sizepage->totlesize);
        cc_flash_internal_init_sizepage_usesize(&sizepage->usesize);
        /* verify */
        ____________________________TO_DO__________________________
        cc_uint8 verify;
        cc_algorithm_verify_sum(&verify,(cc_uint8 *)&sizepage->totlesize,sizeof(sizepage->totlesize) + sizeof(sizepage->usesize));
        sizepage->verify = verify;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_get_devicesnum()
****************************************************************************************************/
cc_result cc_flash_internal_get_devnum(cc_uint32 *devnum)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,devnum);
        /* impletement */
        *devnum = cc_flash_t.info.devpage.num;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_devpage()
****************************************************************************************************/
cc_result cc_flash_internal_init_devpage(cc_flash_info_devices_struct *devpage)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,devpage);
        /* impletement */
        /* init */
        cc_mem_cpy(devpage->id,cc_flash_headerid,CC_FLASH_PAGE_HEADER_ID_LEN);
        devpage->type = CC_FLASH_PAGE_TYPE_DEVICE;
        /* num */
        cc_flash_device_cfg_getnum(&devpage->num);
        for (cc_uint32 i = 0; i < devpage->num; i++)
        {
            /* name */
            cc_flash_device_cfg_getname(i,devpage->item[i].name);
            /* info */
            cc_flash_device_cfg_getinfoaddr(i,&devpage->item[i].infoaddr);
            /* init */
            cc_flash_device_page_init(i);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_verifypage()
****************************************************************************************************/
cc_result cc_flash_internal_init_verifypage(cc_flash_info_verify_struct *verifypage)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,verifypage);
        /* impletement */
        /* init */
        cc_mem_cpy(verifypage->id,cc_flash_headerid,CC_FLASH_PAGE_HEADER_ID_LEN);
        verifypage->type = CC_FLASH_PAGE_TYPE_VERIFY;
        /* calc verify value */
        ____________________________TO_DO__________________________
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_get_pagecurrentaddr()
****************************************************************************************************/
cc_result cc_flash_get_pagecurrentaddr(cc_flash_page_type_enum page,cc_uint32 *pageaddr)
{
    cc_result result = CC_E_OK;
    cc_uint32 baseaddress;
    cc_uint32 pagesize;
    cc_uint32 pageitemsize;
    cc_uint8 *pagecontent;
    cc_uint32 pos;

    do
    {
        /* check */
        CHECK_PTR(result,pageaddr);
        /* impletement */
        cc_flash_cfg_getstartaddr(&baseaddress);
        cc_flash_cfg_getpagesize(&pagesize);
        cc_flash_cfg_getpageitemsize(page,&pageitemsize);
        cc_flash_cfg_getpagecontent(&pagecontent);
        /* page shift */
        baseaddress += (page * pagesize);
        /* find last address */
        cc_flash_cfg_read(pagecontent,baseaddress,pagesize);
        ____________________________TO_DO__________________________
        cc_algorithm_search_binary(&pos,pagecontent,pagesize,cc_flash_freevalue,16);
        /* find content */
        /* verify */
        ____________________________TO_DO__________________________
        /* output */
        *pageaddr = (baseaddress + pos - pageitemsize);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_info()
****************************************************************************************************/
cc_result cc_flash_internal_init_info(cc_flash_info_struct *info)
{
    cc_result result = CC_E_OK;
    cc_uint32 address;
    cc_uint32 pagesize;
    cc_uint32 currentaddress;

    do
    {
        /* check parameter */
        CHECK_PTR(result,info);
        /* impletement */
        cc_flash_cfg_getstartaddr(&address);
        cc_flash_cfg_getpagesize(&pagesize);
        /* read info */
        cc_flash_get_pagecurrentaddr(CC_FLASH_PAGE_TYPE_MAIN,&currentaddress);
        cc_flash_cfg_read((cc_uint8 *)&info->mainpage,currentaddress,sizeof(cc_flash_info_main_struct));
        /* check header */
        if(cc_flash_check_header((cc_flash_info_header_struct *)&info->mainpage,CC_FLASH_PAGE_TYPE_MAIN) != CC_E_OK)
        {
            /* init main page */
            cc_flash_internal_init_mainpage(&info->mainpage);
            /* erase */
            ____________________________TO_DO__________________________
            /* write */
            cc_flash_cfg_write((cc_uint8 *)&info->mainpage,address + (pagesize * CC_FLASH_PAGE_TYPE_MAIN),sizeof(info->mainpage));
        }
        
        cc_flash_get_pagecurrentaddr(CC_FLASH_PAGE_TYPE_SIZE,&currentaddress);
        cc_flash_cfg_read((cc_uint8 *)&info->sizepage,currentaddress,CC_FLASH_PAGE_HEADER_LEN);
        if(cc_flash_check_header((cc_flash_info_header_struct *)&info->sizepage,CC_FLASH_PAGE_TYPE_SIZE) != CC_E_OK)
        {
            /* init size page */
            cc_flash_internal_init_sizepage(&info->sizepage);
            /* erase */
            ____________________________TO_DO__________________________
            /* write */
            cc_flash_cfg_write((cc_uint8 *)&info->sizepage,address + (pagesize * CC_FLASH_PAGE_TYPE_SIZE),sizeof(info->sizepage));
        }

        cc_flash_get_pagecurrentaddr(CC_FLASH_PAGE_TYPE_DEVICE,&currentaddress);
        cc_flash_cfg_read((cc_uint8 *)&info->devpage,currentaddress,CC_FLASH_PAGE_HEADER_LEN);
        if(cc_flash_check_header((cc_flash_info_header_struct *)&info->devpage,CC_FLASH_PAGE_TYPE_DEVICE) != CC_E_OK)
        {
            /* init devices page */
            cc_flash_internal_init_devpage(&info->devpage);
            /* erase */
            ____________________________TO_DO__________________________
            /* write */
            cc_flash_cfg_write((cc_uint8 *)&info->devpage,address + (pagesize * CC_FLASH_PAGE_TYPE_DEVICE),sizeof(info->devpage));
        }

        cc_flash_get_pagecurrentaddr(CC_FLASH_PAGE_TYPE_VERIFY,&currentaddress);
        cc_flash_cfg_read((cc_uint8 *)&info->verifypage,currentaddress,CC_FLASH_PAGE_HEADER_LEN);
        if(cc_flash_check_header((cc_flash_info_header_struct *)&info->verifypage,CC_FLASH_PAGE_TYPE_VERIFY) != CC_E_OK)
        {
            /* init crc page */
            cc_flash_internal_init_verifypage(&info->verifypage);
            /* erase */
            ____________________________TO_DO__________________________
            /* write */
            cc_flash_cfg_write((cc_uint8 *)&info->verifypage,address + (pagesize * CC_FLASH_PAGE_TYPE_VERIFY),sizeof(info->verifypage));
        }
        /* verify info */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_devices()
****************************************************************************************************/
cc_result cc_flash_internal_init_devices(cc_flash_device_struct *devices)
{
    cc_result result = CC_E_OK;
    cc_uint32 devnum;
    cc_flash_info_devices_item_struct devitem;
    cc_uint32 address;
    cc_uint32 pagesize;
    cc_uint32 deviceitemsize;

    do
    {
        /* check parameter */
        CHECK_PTR(result,devices);
        /* impletement */
        cc_flash_device_init(&cc_flash_t.devices);
        /* init default device */
        /* get addr */
        cc_flash_cfg_getpagesize(&pagesize);
        cc_flash_internal_get_devnum(&devnum);
        deviceitemsize = sizeof(cc_flash_info_devices_item_struct);
        /* for page */
        for (cc_uint32 i = 0; i < devnum; i++)
        {
            /* get current address */
            cc_flash_get_pagecurrentaddr(CC_FLASH_PAGE_TYPE_DEVICE,address);
            cc_uint32 itemaddr = address + CC_FLASH_PAGE_HEADER_ID_LEN + sizeof(CC_FLASH_PAGE_HEADER_ID_LEN) + sizeof(cc_uint32) + (i * deviceitemsize);
            /* read device item */
            cc_flash_cfg_read((cc_uint8 *)&devitem,itemaddr,deviceitemsize);
            /* get devices */
            cc_flash_device_struct *device;
            cc_heap_allocate("heap",&device,sizeof(cc_flash_device_struct));
            cc_flash_device_discover(device,devitem.name,devitem.devicetype,devitem.infoaddr);
            /* create devices list */
            cc_list_insert_after(&cc_flash_t.devices.list,&device->list);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init_func()
****************************************************************************************************/
cc_result cc_flash_internal_init_func(cc_flash_func_struct *func)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,func);
        /* impletement */
        func->read = cc_flash_read;
        func->write = cc_flash_write;
        func->erase = cc_flash_erase;
        func->erase_folder = cc_flash_erase_folder;
        func->erase_file = cc_flash_erase_file;
        func->create = cc_flash_create;
        func->delete = cc_flash_delete;
        func->create_folder = cc_flash_create_folder;
        func->delete_folder = cc_flash_delete_folder;
        func->create_file = cc_flash_create_file;
        func->delete_file = cc_flash_delete_file;        
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_internal_init()
****************************************************************************************************/
cc_result cc_flash_internal_init(cc_flash_struct *flash)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,flash);
        /* impletement */
        /* init info */
        cc_flash_internal_init_info(&flash->info);
        /* init devices */
        cc_flash_internal_init_devices(&flash->devices);
        /* init func */
        cc_flash_internal_init_func(&flash->func);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_init()
****************************************************************************************************/
cc_result cc_flash_init(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_flash_initflag != CC_TRUE));
        
        /* init flash object */
        cc_flash_object_init(&cc_flash_t.object);
        /* register object */
        cc_object_register(&cc_flash_t.object);

        /* init flash */
        cc_flash_internal_init(&cc_flash_t);

        /* init service */
        cc_flash_service_init(&cc_flash_t.service);
        /* register service */
        cc_service_register(&cc_flash_t.service);

        /* start service */
        cc_service_start("flash");

        /* init flag */
        cc_flash_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_read()
****************************************************************************************************/
cc_result cc_flash_read(cc_int8 *path,cc_uint8 *buffer,cc_uint32 *length)
{
    cc_result result = CC_E_OK;
    cc_flash_device_struct *device;
    cc_int8 devicename[CC_NAME_MAX_LEN];
    cc_int8 *devicepath;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        CHECK_PTR(result,buffer);
        CHECK_PTR(result,length);
        CHECK_LOGIC(result,(*length > 0));
        /* impletement */
        /* get device name */
        devicepath = path;
        cc_mem_strtok(&devicename,&devicepath,"/");
        /* find device */
        cc_flash_device_get(&device,devicename);
        /* call device read */
        cc_flash_device_read(devicename,devicepath,buffer,length);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_write()
****************************************************************************************************/
cc_result cc_flash_write(cc_int8 *path,cc_uint8 *buffer,cc_uint32 length)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        CHECK_PTR(result,buffer);
        CHECK_LOGIC(result,(length > 0));
        /* impletement */
        /* find device */

        /* call device write */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_erase()
****************************************************************************************************/
cc_result cc_flash_erase(cc_flash_storage_type_enum type,cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        CHECK_LOGIC(result,(eraseaddr > 0));
        CHECK_LOGIC(result,(eraselen > 0));
        /* impletement */
        switch(type)
        {
        case CC_FLASH_STORAGE_TYPE_FILE:
            cc_flash_erase_file(path,eraseaddr,eraselen);
            break;
        case CC_FLASH_STORAGE_TYPE_FOLDER:
            cc_flash_erase_folder(path,eraseaddr,eraselen);
            break;
        default:
            break;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_erase_folder()
****************************************************************************************************/
cc_result cc_flash_erase_folder(cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        CHECK_LOGIC(result,(eraseaddr > 0));
        CHECK_LOGIC(result,(eraselen > 0));
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_erase_file()
****************************************************************************************************/
cc_result cc_flash_erase_file(cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        CHECK_LOGIC(result,(eraseaddr > 0));
        CHECK_LOGIC(result,(eraselen > 0));
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_create()
****************************************************************************************************/
cc_result cc_flash_create(cc_flash_storage_type_enum type,cc_int8 *path,cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        CHECK_PTR(result,name);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_delete()
****************************************************************************************************/
cc_result cc_flash_delete(cc_flash_storage_type_enum type,cc_int8 *path)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_create_folder()
****************************************************************************************************/
cc_result cc_flash_create_folder(cc_int8 *path,cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        CHECK_PTR(result,name);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_delete_folder()
****************************************************************************************************/
cc_result cc_flash_delete_folder(cc_int8 *path)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_create_file()
****************************************************************************************************/
cc_result cc_flash_create_file(cc_int8 *path,cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        CHECK_PTR(result,name);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_delete_file()
****************************************************************************************************/
cc_result cc_flash_delete_file(cc_int8 *path)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,path);
        /* impletement */

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_recv()
****************************************************************************************************/
cc_result cc_flash_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,dstname);
        CHECK_PTR(result,srcname);
        CHECK_PTR(result,data);

        /* check dstname */
        CHECK_FUNC(result,cc_mem_strncmp(cc_flash_t.service.name,dstname,CC_NAME_MAX_LEN));
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
                CHECK_FUNC(result,cc_flash_cfg_servicecall(data,len));
            }
            break;
        case CC_SERVICE_MSGTYPE_SERVICE_ALIVE:
            {
                /* set flag then send to service alive */
                cc_flash_t.service.func.send(srcname,dstname,data,len,CC_SERVICE_MSGTYPE_SERVICE_ALIVE);
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
* cc_flash_mainfunction()
****************************************************************************************************/
cc_result cc_flash_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_flash.c End!
****************************************************************************************************/

