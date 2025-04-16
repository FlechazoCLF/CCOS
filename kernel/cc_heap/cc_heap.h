
/****************************************************************************************************
* File cc_heap.h Start!
****************************************************************************************************/
#ifndef _CC_HEAP_H
#define _CC_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"
#include "cc_service.h"

/****************************************************************************************************
* Define
****************************************************************************************************/
#define CC_HEAP_NAME ("heap")

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* heap list */
typedef struct cc_heap_item_struct_tag
{
    /* flag of heap block head */
    cc_uint32 headflag;
    /* unique id */
    cc_uint32 uniqueid;
    /* size */
    cc_uint32 size;
    /* current add */
    void *currentadd;
    /* list */
    struct cc_heap_item_struct_tag *prev;
    struct cc_heap_item_struct_tag *next;
    struct cc_heap_item_struct_tag *prevfree;
    struct cc_heap_item_struct_tag *nextfree;
    struct cc_heap_item_struct_tag *prevused;
    struct cc_heap_item_struct_tag *nextused;
}cc_heap_item_struct;

/* heap func */
typedef struct
{
    /* init void *heap need to modify */
    ____________________________TO_DO__________________________
    cc_result (*init)(void *heap,cc_int8 *name,void *address,cc_uint32 size);
    /* init */
    cc_result (*detach)(cc_int8 *name);
    /* init */
    cc_result (*allocate)(cc_int8 *name,void **address,cc_uint32 size);
    /* init */
    cc_result (*free)(cc_int8 *name,void *address);
    /* init */
    cc_result (*getInfo)(cc_int8 *name);
}cc_heap_func_struct;

/* heap */
typedef struct cc_heap_struct_tag
{
    /* inherit object */
    cc_object_struct object;
    /* service */
    cc_service_struct service;
    ____________________________TO_DO__________________________
    /* heap name: current support one heap, name for multi heap */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* func */
    cc_heap_func_struct func;
    /* startaddress */
    void *startaddress;
    /* size */
    cc_uint32 totalsize;
    cc_uint32 freesize;
    cc_uint32 usedsize;
    /* heap item list */
    cc_heap_item_struct *totalheaplist;
    cc_heap_item_struct *freeheaplist;
    cc_heap_item_struct *usedheaplist;
    /* heap list */
    struct cc_heap_struct_tag *prev;
    struct cc_heap_struct_tag *next;
}cc_heap_struct;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/
cc_result cc_heap_init(cc_heap_struct *heap,cc_int8 *name,void *address,cc_uint32 size);
cc_result cc_heap_detach(cc_int8 *name);
cc_result cc_heap_allocate(cc_int8 *name,void **address,cc_uint32 size);
cc_result cc_heap_free(cc_int8 *name,void *address);
cc_result cc_heap_getInfo(cc_int8 *name);
cc_result cc_heap_mainfunction(cc_void);
cc_result cc_heap_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_HEAP_H */
/****************************************************************************************************
* File cc_heap.h End!
****************************************************************************************************/

