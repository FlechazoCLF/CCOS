
/****************************************************************************************************
* File flash_device.c Start!
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
#include "cc_flash_device.h"
/* log */
#include "cc_trace.h"
/* sub module */
#include "cc_flash_device_cfg.h"
/* components */
#include "cc_flash.h"
#include "cc_mem.h"
#include "cc_list.h"
#include "cc_flash_cfg.h"

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

/* cc_flash_device */
cc_flash_device_struct cc_flash_device_t;
/* init flag */
cc_boolean cc_flash_device_initflag = CC_FALSE;
/* cc_flash_device */
cc_flash_device_struct *cc_flash_device_root_t;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_flash_device_init()
****************************************************************************************************/
cc_result cc_flash_device_init(cc_flash_device_struct *device)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,device);
        CHECK_LOGIC(result,(cc_flash_device_initflag == CC_FALSE));
        /* init default device */

        cc_flash_device_root_t = device;
        /* init flag */
        cc_flash_device_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_check_header()
****************************************************************************************************/
cc_result cc_flash_device_check_header(cc_flash_device_header_struct *header,cc_flash_device_page_type_enum type)
{
    cc_result result = CC_E_OK;
    cc_uint8 headerid[CC_FLASH_PAGE_HEADER_ID_LEN];

    do
    {
        /* check parameter */
        CHECK_PTR(result,header);
        /* impletement */
        /* check id */
        cc_flash_get_headerid(headerid);
        CHECK_FUNC(result,cc_mem_cmp(headerid,header->id,CC_FLASH_PAGE_HEADER_ID_LEN));
        /* check type */
        CHECK_LOGIC(result,(header->type == type));
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_discover()
****************************************************************************************************/
cc_result cc_flash_device_discover(cc_flash_device_struct *device,cc_int8 *name,cc_flash_device_enum devicetype,cc_uint32 address)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,device);
        CHECK_PTR(result,name);
        /* impletement */
        cc_flash_device_cfg_getfunc(devicetype,&device->func);
        /* read info */
        device->func.read((cc_uint8 *)&device->attribute,address,sizeof(cc_flash_device_attribute_struct));
        /* check header */
        cc_flash_device_check_header(&device->attribute,CC_FLASH_DEVICE_PAGE_TYPE_ATTRIBUTE);
        /* check name */
        cc_mem_strncmp(device->attribute.name,name,CC_NAME_MAX_LEN);
        /* init other info */

        /* init list */
        cc_list_init(&device->list);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_find()
****************************************************************************************************/
cc_result cc_flash_device_find(cc_flash_device_struct **device,cc_int8 *name)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_flash_device_struct *iterator;

    do
    {
        /* check */
        CHECK_PTR(result,device);
        CHECK_PTR(result,name);
        CHECK_LOGIC(result,(cc_flash_device_initflag == CC_TRUE));
        /* impletement */
        iterator = cc_flash_device_root_t;
        /* iterator */
        while((iterator != CC_NULL_PTR) && (iterator->list.next != &cc_flash_device_root_t->list))
        {
            /* cmp name */
            if(cc_mem_strncmp(name,iterator->attribute.name,CC_NAME_MAX_LEN) == CC_E_OK)
            {
                /* output */
                *device = iterator;
                result = CC_E_OK;
                break;
            }
            /* next */
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_flash_device_struct,list);
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_get()
****************************************************************************************************/
cc_result cc_flash_device_get(cc_flash_device_struct **device,cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,device);
        CHECK_PTR(result,name);
        /* impletement */
        cc_flash_device_find(device,name);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_page_init_attribute()
****************************************************************************************************/
cc_result cc_flash_device_page_init_attribute(cc_uint32 ctrlidx,cc_flash_device_attribute_struct *attribute)
{
    cc_result result = CC_E_OK;
    cc_uint32 pagesize;
    cc_uint32 deviceinfoaddress;
    cc_flash_device_func_struct devicefunc;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_flash_device_initflag == CC_TRUE));
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,attribute);
        /* init */
        /* get address */
        cc_flash_device_cfg_getinfoaddr(ctrlidx,&deviceinfoaddress);
        cc_flash_device_cfg_getfunc(ctrlidx,&devicefunc);
        cc_flash_cfg_getpagesize(&pagesize);
        /* read */
        devicefunc.read((cc_uint8 *)attribute,deviceinfoaddress + (pagesize * CC_FLASH_DEVICE_PAGE_TYPE_ATTRIBUTE),sizeof(cc_flash_device_attribute_struct));
        /* check header */
        if(cc_flash_device_check_header((cc_flash_device_header_struct *)attribute,CC_FLASH_DEVICE_PAGE_TYPE_ATTRIBUTE) != CC_E_OK)
        {
            /* init page */
            cc_flash_device_attribute_struct *attribute_cfg;
            cc_flash_device_cfg_getattributepage(ctrlidx,&attribute_cfg);
            cc_mem_cpy(attribute,attribute_cfg,sizeof(cc_flash_device_attribute_struct));
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_page_init_sizepage()
****************************************************************************************************/
cc_result cc_flash_device_page_init_sizepage(cc_uint32 ctrlidx,cc_flash_device_info_size_struct *sizepage)
{
    cc_result result = CC_E_OK;
    cc_uint32 pagesize;
    cc_uint32 deviceinfoaddress;
    cc_flash_device_func_struct devicefunc;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_flash_device_initflag == CC_TRUE));
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,sizepage);
        /* init */
        /* get address */
        cc_flash_device_cfg_getinfoaddr(ctrlidx,&deviceinfoaddress);
        cc_flash_device_cfg_getfunc(ctrlidx,&devicefunc);
        cc_flash_cfg_getpagesize(&pagesize);
        /* read */
        devicefunc.read((cc_uint8 *)sizepage,deviceinfoaddress + (pagesize * CC_FLASH_DEVICE_PAGE_TYPE_SIZE),sizeof(cc_flash_device_info_size_struct));
        /* check header */
        if(cc_flash_device_check_header((cc_flash_device_header_struct *)sizepage,CC_FLASH_DEVICE_PAGE_TYPE_SIZE) != CC_E_OK)
        {
            /* init page */
            cc_flash_device_info_size_struct *sizepage_cfg;
            cc_flash_device_cfg_getsizepage(ctrlidx,&sizepage_cfg);
            cc_mem_cpy(sizepage,sizepage_cfg,sizeof(cc_flash_device_info_size_struct));
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_page_init_cataloguepage()
****************************************************************************************************/
cc_result cc_flash_device_page_init_cataloguepage(cc_uint32 ctrlidx,cc_flash_device_info_catalogue_struct *cataloguepage)
{
    cc_result result = CC_E_OK;
    cc_uint32 pagesize;
    cc_uint32 deviceinfoaddress;
    cc_flash_device_func_struct devicefunc;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_flash_device_initflag == CC_TRUE));
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,cataloguepage);
        /* init */
        /* get address */
        cc_flash_device_cfg_getinfoaddr(ctrlidx,&deviceinfoaddress);
        cc_flash_device_cfg_getfunc(ctrlidx,&devicefunc);
        cc_flash_cfg_getpagesize(&pagesize);
        /* read */
        devicefunc.read((cc_uint8 *)cataloguepage,deviceinfoaddress + (pagesize * CC_FLASH_DEVICE_PAGE_TYPE_CATALOGUE),sizeof(cc_flash_device_info_catalogue_struct));
        /* check header */
        if(cc_flash_device_check_header((cc_flash_device_header_struct *)cataloguepage,CC_FLASH_DEVICE_PAGE_TYPE_ATTRIBUTE) != CC_E_OK)
        {
            /* init page */
            cc_flash_device_info_catalogue_struct *cataloguepage_cfg;
            cc_flash_device_cfg_getcataloguepage(ctrlidx,&cataloguepage_cfg);
            cc_mem_cpy(cataloguepage,cataloguepage_cfg,sizeof(cc_flash_device_info_catalogue_struct));
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_page_init_verifypage()
****************************************************************************************************/
cc_result cc_flash_device_page_init_verifypage(cc_uint32 ctrlidx,cc_flash_device_info_verify_struct *verifypage)
{
    cc_result result = CC_E_OK;
    cc_uint32 pagesize;
    cc_uint32 deviceinfoaddress;
    cc_flash_device_func_struct devicefunc;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_flash_device_initflag == CC_TRUE));
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        CHECK_PTR(result,verifypage);
        /* init */
        /* get address */
        cc_flash_device_cfg_getinfoaddr(ctrlidx,&deviceinfoaddress);
        cc_flash_device_cfg_getfunc(ctrlidx,&devicefunc);
        cc_flash_cfg_getpagesize(&pagesize);
        /* read */
        devicefunc.read((cc_uint8 *)verifypage,deviceinfoaddress + (pagesize * CC_FLASH_DEVICE_PAGE_TYPE_VERIFY),sizeof(cc_flash_device_info_verify_struct));
        /* check header */
        if(cc_flash_device_check_header((cc_flash_device_header_struct *)verifypage,CC_FLASH_DEVICE_PAGE_TYPE_ATTRIBUTE) != CC_E_OK)
        {
            /* init page */
            cc_flash_device_info_verify_struct *verifypage_cfg;
            cc_flash_device_cfg_getverifypage(ctrlidx,&verifypage_cfg);
            cc_mem_cpy(verifypage,verifypage_cfg,sizeof(cc_flash_device_info_verify_struct));
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_page_init()
****************************************************************************************************/
cc_result cc_flash_device_page_init(cc_uint32 ctrlidx)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_flash_device_initflag == CC_TRUE));
        CHECK_LOGIC(result,(ctrlidx < CC_FLASH_DEVICE_END));
        /* init */
        cc_flash_device_page_init_attribute(ctrlidx,&cc_flash_device_t.attribute);
        cc_flash_device_page_init_sizepage(ctrlidx,&cc_flash_device_t.info.sizepage);
        cc_flash_device_page_init_cataloguepage(ctrlidx,&cc_flash_device_t.info.cataloguepage);
        cc_flash_device_page_init_verifypage(ctrlidx,&cc_flash_device_t.info.verifypage);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_read()
****************************************************************************************************/
cc_result cc_flash_device_read(cc_int8 *name,cc_int8 *path,cc_uint8 *buffer,cc_uint32 *length)
{
    cc_result result = CC_E_OK;
    cc_flash_device_struct *device;
    cc_int8 cataloguename[CC_NAME_MAX_LEN];
    cc_int8 *cataloguepath;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,path);
        CHECK_PTR(result,buffer);
        CHECK_PTR(result,length);
        CHECK_LOGIC(result,(*length > 0));
        /* impletement */
        /* find device */
        cc_flash_device_get(&device,name);
        /* get catalogue name */
        cataloguepath = path;
        cc_mem_strtok(&cataloguename,&cataloguepath,"/");
        /* find catalogue */
        
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_flash_device_write()
****************************************************************************************************/
cc_result cc_flash_device_write(cc_int8 *path,cc_uint8 *buffer,cc_uint32 length)
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
* cc_flash_device_erase()
****************************************************************************************************/
cc_result cc_flash_device_erase(cc_flash_storage_type_enum type,cc_int8 *path,cc_uint32 eraseaddr,cc_uint32 eraselen)
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
* cc_flash_device_mainfunction()
****************************************************************************************************/
cc_result cc_flash_device_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File flash_device.c End!
****************************************************************************************************/

