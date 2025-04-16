
/****************************************************************************************************
* File cc_list.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_list.h"
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

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_list_init()
****************************************************************************************************/
cc_result cc_list_init(cc_list_struct *list)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,list);
        /* impletement */
        list->prev = list;
        list->next = list;
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_list_detach()
****************************************************************************************************/
cc_result cc_list_detach(cc_list_struct *list)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,list);
        /* impletement */
        list->prev = CC_NULL_PTR;
        list->next = CC_NULL_PTR;
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_list_insert()
****************************************************************************************************/
cc_result cc_list_insert(cc_list_insert_direct_enum direct,cc_list_struct *list,cc_list_struct *newlist)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,list);
        CHECK_PTR(result,newlist);
        /* impletement */
        switch(direct)
        {
        case CC_LIST_INSERT_DIRECT_AFTER:
            {
                /* after */
                newlist->prev = list;
                newlist->next = list->next;

                list->next->prev = newlist;
                list->next = newlist;
            }
            break;
        case CC_LIST_INSERT_DIRECT_BEFORE:
            {
                /* before */
                newlist->next = list;
                newlist->prev = list->prev;

                list->prev->next = newlist;
                list->prev = newlist;
            }
            break;
        
        default:
            break;
        }

    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_list_insert_before()
****************************************************************************************************/
cc_result cc_list_insert_before(cc_list_struct *list,cc_list_struct *newlist)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,list);
        CHECK_PTR(result,newlist);
        /* impletement */
        cc_list_insert(CC_LIST_INSERT_DIRECT_BEFORE,list,newlist);
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_list_insert_after()
****************************************************************************************************/
cc_result cc_list_insert_after(cc_list_struct *list,cc_list_struct *newlist)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,list);
        CHECK_PTR(result,newlist);
        /* impletement */
        cc_list_insert(CC_LIST_INSERT_DIRECT_AFTER,list,newlist);
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_list_remove()
****************************************************************************************************/
cc_result cc_list_remove(cc_list_struct *list)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,list);
        /* impletement */
        list->next->prev = list->prev;
        list->prev->next = list->next;

        list->prev = list;
        list->next = list;
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_list_getlen()
****************************************************************************************************/
cc_result cc_list_getlen(cc_list_struct *list,cc_uint32 *len)
{
    cc_result result = CC_E_OK;
    cc_list_struct *templist;
    cc_uint32 templen;

    do
    {
        /* check pointer */
        CHECK_PTR(result,list);
        /* impletement */
        templen = 0;
        templist = list;

        while(templist->next != list)
        {
            templist = templist->next;
            templen++;
        }

        *len = templen;

    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_list_checknull()
****************************************************************************************************/
cc_result cc_list_checknull(cc_list_struct *list)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,list);
        /* impletement */
        CHECK_LOGIC(result,(list->next == list));
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* cc_list_checknull()
****************************************************************************************************/
cc_result cc_list_search(cc_list_struct *dstlist,cc_list_struct *srclist)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_list_struct *templist;

    do
    {
        /* check pointer */
        CHECK_PTR(result,dstlist);
        CHECK_PTR(result,srclist);
        /* impletement */
        templist = dstlist;
        
        do
        {
            /* cmp */
            if(templist == srclist)
            {
                result = CC_E_OK;
                break;
            }
            /* check pointer */
            if(templist->next == CC_NULL_PTR)
            {
                break;
            }
            /* next */
            templist = templist->next;
        }while(templist->next != dstlist);
        
    }while(0u);
    
    return result;
}

/****************************************************************************************************
* File cc_list.c End!
****************************************************************************************************/
