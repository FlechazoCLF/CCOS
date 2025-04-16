
/****************************************************************************************************
* File cc_type.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"
#include "cc_mem.h"
#include "cc_list.h"
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

/* object */
cc_object_struct cc_object_t[CC_OBJECT_TYPE(CC_END)];
/* object init flag */
cc_boolean cc_object_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_object_init()
****************************************************************************************************/
cc_result cc_object_init(cc_void)
{
    cc_result result = CC_E_OK;
    cc_uint8 i;
    cc_int8 name[CC_NAME_MAX_LEN] = "kernel obj";
    cc_int8 log[CC_LOG_MAX_LEN] = "kernel obj init";

    do
    {
        /* check parameter */
        CHECK_LOGIC(result,(cc_object_initflag != CC_TRUE));

        /* init object */
        for(i = 0;i < CC_OBJECT_TYPE(CC_END);i++)
        {
            cc_object_t[i].parent = CC_NULL;
            cc_mem_cpy(cc_object_t[i].name,name,CC_NAME_MAX_LEN);
            cc_object_t[i].id = i;
            cc_object_t[i].state = CC_OBJECT_STATE_INIT;
            cc_object_t[i].type = i;
            cc_object_t[i].flag = CC_OBJECT_FLAG_FREE;
            cc_mem_cpy(cc_object_t[i].info.log,log,CC_LOG_MAX_LEN);
            cc_object_t[i].authority = i;
            cc_list_init(&cc_object_t[i].list);
        }

        /* set init flag */
        cc_object_initflag = CC_TRUE;

    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_object_detach()
****************************************************************************************************/
cc_result cc_object_detach(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_object_create()
****************************************************************************************************/
cc_result cc_object_create(cc_object_type_enum type,cc_object_struct *object)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_object_delete()
****************************************************************************************************/
cc_result cc_object_delete(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_object_gethead()
****************************************************************************************************/
cc_result cc_object_gethead(cc_object_type_enum type,cc_object_struct **objecthead)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,objecthead);
        CHECK_LOGIC(result,(type < CC_OBJECT_TYPE(CC_END)));

        /* impletement */
        *objecthead = &cc_object_t[type];
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_object_gettail()
****************************************************************************************************/
cc_result cc_object_gettail(cc_object_struct *objecthead,cc_object_struct **objecttail)
{
    cc_result result = CC_E_OK;
    cc_object_struct *iterator;

    do
    {
        /* check parameter */
        CHECK_PTR(result,objecthead);
        CHECK_PTR(result,objecttail);

        /* impletement */
        iterator = objecthead;
        while((iterator != CC_NULL_PTR) && (iterator->list.next != &objecthead->list))
        {
            /* next */
            iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_object_struct,list);
        }
        
        /* output */
        *objecttail = iterator;
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_object_find()
****************************************************************************************************/
cc_result cc_object_find(cc_int8 *name,cc_object_struct **object)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_object_struct *objecthead;
    cc_object_struct *iterator;
    cc_uint8 i;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,object);

        /* impletement */
        for (i = 0;i < CC_OBJECT_TYPE(CC_END);i++)
        {
            /* get head */
            cc_object_gethead(i,&objecthead);
            iterator = objecthead;
            /* iterator */
            while((iterator != CC_NULL_PTR) && (iterator->list.next != &objecthead->list))
            {
                /* cmp name */
                if(cc_mem_strncmp(name,iterator->name,CC_NAME_MAX_LEN) == CC_E_OK)
                {
                    /* output */
                    *object = iterator;
                    result = CC_E_OK;
                    break;
                }
                /* next */
                iterator = CC_REFLECT_STRUCT(iterator->list.next,cc_object_struct,list);
            }

            /* exit foreach */
            if(result == CC_E_OK)
            {
                break;
            }
        }
        
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_object_getauthority()
****************************************************************************************************/
cc_object_authority_enum cc_object_getauthority(cc_object_type_enum type)
{
    cc_object_authority_enum authority = CC_OBJECT_AUTHORITY(CC_USER);

    do
    {
        switch(type)
        {
        case CC_OBJECT_TYPE(CC_USER):
            authority = CC_OBJECT_AUTHORITY(CC_USER);
            break;
        case CC_OBJECT_TYPE(CC_TASK):
            authority = CC_OBJECT_AUTHORITY(CC_TASK);
            break;
        case CC_OBJECT_TYPE(CC_SERVICE):
            authority = CC_OBJECT_AUTHORITY(CC_SERVICE);
            break;
        case CC_OBJECT_TYPE(CC_THREAD):
            authority = CC_OBJECT_AUTHORITY(CC_THREAD);
            break;
        case CC_OBJECT_TYPE(CC_KERNEL):
            authority = CC_OBJECT_AUTHORITY(CC_KERNEL);
            break;
        default:
            authority = CC_OBJECT_AUTHORITY(CC_USER);
            break;
        }

    }while(0u);
    
    return authority;
}

/****************************************************************************************************
* cc_object_register()
****************************************************************************************************/
cc_result cc_object_register(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 log[CC_LOG_MAX_LEN] = "object register";
    cc_object_struct *objecthead = CC_NULL_PTR;
    cc_object_struct *objecttail = CC_NULL_PTR;
    cc_object_struct *objectfind = CC_NULL_PTR;

    do
    {
        /* check parameter */
        CHECK_PTR(result,object);
        /* check init flag */
        CHECK_LOGIC(result,(cc_object_initflag == CC_TRUE));
        /* impletement */
        /* check repeat by find object */
        CHECK_LOGIC(result,(cc_object_find(object->name,&objectfind) != CC_E_OK));
        /* get kernel object head  */
        CHECK_FUNC(result,cc_object_gethead(object->type,&objecthead));
        /* iterator find tail */
        CHECK_FUNC(result,cc_object_gettail(objecthead,&objecttail));

        /* info */
        object->state = CC_OBJECT_STATE_REGISTER;
        object->authority = cc_object_getauthority(object->type);
        cc_mem_strncpy(object->info.log,log,CC_LOG_MAX_LEN);

        /* insert object */
        CHECK_FUNC(result,cc_list_insert_after(&objecttail->list,&object->list));

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_object_deregister()
****************************************************************************************************/
cc_result cc_object_deregister(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_type.c End!
****************************************************************************************************/

