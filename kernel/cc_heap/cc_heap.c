
/****************************************************************************************************
* File cc_heap.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_heap.h"
#include "cc_mem.h"
#include "cc_trace.h"
#include "cc_service.h"
#include "cc_kernel.h"
#include "cc_list.h"
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

/* heap */
cc_heap_struct cc_heap_t;
/* init flag */
cc_boolean cc_heap_initflag = CC_FALSE;
/* heap flag of head */
cc_uint32 cc_heap_headflag = 0xCCCCCCCC;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_heap_object_init()
****************************************************************************************************/
cc_result cc_heap_object_init(cc_object_struct *object)
{
    cc_result result = CC_E_OK;
    cc_int8 *name = "heap obj";
    cc_int8 *log = "heap obj init";

    do
    {
        /* check parameter */
        CHECK_PTR(result,object);
        /* impletement */
        object->parent = CC_KERNEL_OBJECT_GET();
        /* name */
        cc_mem_strncpy(object->name,name,CC_NAME_MAX_LEN);
        /* id */
        object->id = CC_SERVICE_TYPE_MEMORY;
        /* state */
        object->state = CC_OBJECT_STATE_INIT;
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
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_get()
****************************************************************************************************/
cc_result cc_heap_get(cc_int8 *name,cc_heap_struct **heap)
{
    cc_result result = CC_E_NOT_OK_NOT_FIND;
    cc_heap_struct *iterator;
    cc_heap_struct *headheap;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,heap);
        /* impletement */
        iterator = &cc_heap_t;
        headheap = &cc_heap_t;
        /* forech all heap list */
        CHECK_PTR(result,iterator);
        while(iterator->next != CC_NULL_PTR)
        {
            /* find heap by name */
            if(cc_mem_strncmp(iterator->name,name,CC_NAME_MAX_LEN) == CC_E_OK)
            {
                *heap = iterator;
                result = CC_E_OK;
                break;
            }
            /* tail list */
            if(iterator->next == headheap)
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
* cc_heap_internalinit()
****************************************************************************************************/
cc_result cc_heap_internalinit(cc_heap_struct *heap,cc_int8 *name,void *address,cc_uint32 size)
{
    cc_result result = CC_E_OK;
    cc_heap_item_struct *item;
    cc_heap_struct *getheap;

    do
    {
        /* check parameter */
        CHECK_PTR(result,heap);
        CHECK_PTR(result,name);
        CHECK_PTR(result,address);
        CHECK_LOGIC(result,size >= sizeof(cc_heap_item_struct));
        CHECK_LOGIC(result,cc_heap_get(name,&getheap) == CC_E_NOT_OK_NOT_FIND);
        /* impletement */
        cc_mem_strncpy(heap->name,name,CC_NAME_MAX_LEN);
        heap->startaddress = address;
        heap->totalsize = size;
        heap->freesize = size - sizeof(cc_heap_item_struct);
        heap->usedsize = sizeof(cc_heap_item_struct);
        /* init heap item */
        item = address;
        item->headflag = cc_heap_headflag;
        item->uniqueid = 0;
        item->size = size - sizeof(cc_heap_item_struct);
        item->currentadd = ((cc_uint8 *)address + sizeof(cc_heap_item_struct));
        item->prev = item;
        item->next = item;
        item->prevfree = item;
        item->nextfree = item;
        item->prevused = CC_NULL_PTR;
        item->nextused = CC_NULL_PTR;
        /* init list */
        heap->totalheaplist = item;
        heap->freeheaplist = item;
        heap->usedheaplist = CC_NULL_PTR;
        heap->prev = heap;
        heap->next = heap;
        /* interface init */
        heap->func.init = (cc_result (*)(void *heap,cc_int8 *name,void *address,cc_uint32 size))cc_heap_init;
        heap->func.detach = cc_heap_detach;
        heap->func.allocate = cc_heap_allocate;
        heap->func.free = cc_heap_free;
        heap->func.getInfo = cc_heap_getInfo;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_service_init()
****************************************************************************************************/
cc_result cc_heap_service_init(cc_service_struct *service)
{
    cc_result result = CC_E_OK;
    cc_int8 *name = "heap";
    cc_int8 *log = "heap service init";

    do
    {
        /* check parameter */
        CHECK_PTR(result,service);
        /* impletement */
        /* parent */
        service->parent = CC_NULL_PTR;
        /* object */
        service->object = &cc_heap_t.object;
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
        service->scheduler.init = CC_NULL_PTR;
        service->scheduler.mainfunction = cc_heap_mainfunction;
        /* signal */
        service->signal.mutex = 0;
        service->signal.event = 0;
        service->signal.semaphore = 0;
        service->signal.signal = 0;
        /* func */
        service->func.send = cc_service_send;
        service->func.recv = cc_heap_recv;
        /* state */
        service->info.state = CC_SERVICE_STATE_INIT;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_init()
****************************************************************************************************/
cc_result cc_heap_init(cc_heap_struct *heap,cc_int8 *name,void *address,cc_uint32 size)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,heap);
        CHECK_PTR(result,name);
        CHECK_PTR(result,address);
        CHECK_LOGIC(result,(cc_heap_initflag != CC_TRUE));

        /* init heap object */
        cc_heap_object_init(&cc_heap_t.object);
        /* register object */
        cc_object_register(&cc_heap_t.object);

        /* init heap */
        cc_heap_internalinit(&cc_heap_t,name,address,size);

        /* init service object */
        cc_heap_service_init(&cc_heap_t.service);
        /* register service */
        cc_service_register(&cc_heap_t.service);

        /* start service */
        cc_service_start(name);

        cc_heap_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_detach()
****************************************************************************************************/
cc_result cc_heap_detach(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_LOGIC(result,(cc_heap_initflag == CC_TRUE));

        /* stop service */
        cc_service_stop("heap");
        /* deregister object */
        cc_object_deregister("heap");
        /* deregister service */
        cc_service_deregister("heap");

        /* init flag */
        cc_heap_initflag = CC_FALSE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_allocate()
****************************************************************************************************/
cc_result cc_heap_allocate(cc_int8 *name,void **address,cc_uint32 size)
{
    cc_result result = CC_E_OK;
    cc_heap_struct *heap;
    cc_heap_item_struct *item;
    cc_heap_item_struct *nextitem;
    void *allocateadd;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,address);
        /* impletement */
        /*  item0          item             item0    item    nextitem
         *  ------   -----------------      ------   -----------------
         * | used | |   free          | => | used | | used |  free    |
         *  ------   -----------------      ------  -----------------
         */
        CHECK_FUNC(result,cc_heap_get(name,&heap));
        /* get free item */
        item = heap->freeheaplist;
        /* check item head info */
        CHECK_LOGIC(result,item->headflag == cc_heap_headflag);
        CHECK_LOGIC(result,item->size >= (size + sizeof(cc_heap_item_struct)));
        /* allocate */
        allocateadd = item->currentadd;
        /* add next item list */
        nextitem = (cc_heap_item_struct *)((cc_uint8 *)allocateadd + size);
        nextitem->headflag = cc_heap_headflag;
        nextitem->uniqueid = 0;
        nextitem->size = item->size - size - sizeof(cc_heap_item_struct);
        nextitem->currentadd = ((cc_uint8 *)allocateadd + size + sizeof(cc_heap_item_struct));
        /* update list */
        nextitem->prev = item;
        nextitem->next = item->next;
        nextitem->nextfree = (item->nextfree == item) ? nextitem : item->nextfree;
        nextitem->prevfree = (item->prevfree == item) ? nextitem : item->prevfree;
        nextitem->prevused = item;
        nextitem->nextused = item->nextused;
        /* prev & next */
        item->prev->next = item->prev->next;
        item->next->prev = nextitem;
        item->prevfree->nextfree = nextitem;
        item->prevused->nextused = item;
        item->nextfree->prevfree = nextitem;
        item->nextused->prevused = item;
        /* update item list */
        item->prev = item->prev;
        item->next = nextitem;
        item->nextfree = nextitem;
        item->prevfree = (item->prevfree == item) ? nextitem : item->prevfree;
        item->prevused = item->prevused;
        item->nextused = item->nextused;
        item->size = size;
        /* update heap */
        /* get free heap item */
        heap->freesize = heap->freesize - sizeof(cc_heap_item_struct) - size;
        heap->usedsize = heap->usedsize + sizeof(cc_heap_item_struct) + size;
        heap->freeheaplist = (heap->freeheaplist == item) ? nextitem : heap->freeheaplist;
        heap->usedheaplist = (heap->usedheaplist == CC_NULL_PTR) ? item : heap->usedheaplist;
        /* output */
        *address = allocateadd;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_free()
****************************************************************************************************/
cc_result cc_heap_free(cc_int8 *name,void *address)
{
    cc_result result = CC_E_OK;
    cc_heap_struct *heap;
    cc_heap_item_struct *item;

    do
    {
        /* check parameter */
        CHECK_PTR(result,name);
        CHECK_PTR(result,address);
        /* get heap info */
        CHECK_FUNC(result,cc_heap_get(name,&heap));
        /* get item */
        item = (cc_heap_item_struct *)((cc_uint8 *)address - sizeof(cc_heap_item_struct));
        /* check item head info */
        CHECK_LOGIC(result,item->headflag == cc_heap_headflag);
        /* impletement */
        /*  item0     item       item1         item0          item
         *  ------   ------   -----------      ------   -----------------
         * | used | | used | |   free    | => | used | |      free       |
         *  ------   ------   -----------      ------   -----------------
         */
        /* uptate item */
        item->prevused->nextused = (item->prevused->prevused == item) ? item->prevused : item->nextused;
        item->nextused->prevused = (item->nextused->nextused == item) ? item->nextused : item->prevused;
        /* merge free item */
        if((item->prevfree != item)&&(item->prev == item->prevfree))
        {
            /* before */
            item->prevfree->size = item->prevfree->size + sizeof(cc_heap_item_struct) + item->size;
            item->prev->next = item->next;
            item->next->prev = item->prev;
            item->prevfree->nextfree = item->nextfree;
            item->nextfree->prevfree = item->prevfree;
            heap->freeheaplist = (heap->freeheaplist == item) ? item->prevfree : heap->freeheaplist;
            heap->freesize = heap->freesize + sizeof(cc_heap_item_struct) + item->size;
            heap->usedsize = heap->usedsize - sizeof(cc_heap_item_struct) - item->size;
            item->size = 0;
            continue;
        }
        if((item->nextfree != item)&&(item->next == item->nextfree))
        {
            /* behind */
            item->size = item->size + sizeof(cc_heap_item_struct) + item->nextfree->size;
            item->next = item->next->next;
            item->next->next->prev = item;
            item->nextfree->nextfree->prevfree = item;
            heap->freeheaplist = (heap->freeheaplist == item->nextfree) ? item : heap->freeheaplist;
            heap->freesize = heap->freesize + sizeof(cc_heap_item_struct) + item->size;
            heap->usedsize = heap->usedsize - sizeof(cc_heap_item_struct) - item->size;
            item->size = 0;
            continue;
        }
        /* nothing to merge insert freeheaplist */
        item->prev->next = item->prev->next;
        item->next->prev = item->next->prev;
        item->prevfree = heap->freeheaplist;
        item->nextfree = heap->freeheaplist->nextfree;
        heap->freeheaplist->nextfree->prevfree = item;
        heap->freeheaplist->nextfree = item;
        heap->freesize = heap->freesize + sizeof(cc_heap_item_struct) + item->size;
        heap->usedsize = heap->usedsize - sizeof(cc_heap_item_struct) - item->size;
        item->size = 0;

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_getInfo()
****************************************************************************************************/
cc_result cc_heap_getInfo(cc_int8 *name)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_mainfunction()
****************************************************************************************************/
cc_result cc_heap_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_heap_recv()
****************************************************************************************************/
cc_result cc_heap_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type)
{
    cc_result result = CC_E_OK;

    do
    {


    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_heap.c End!
****************************************************************************************************/

