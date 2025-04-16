
/****************************************************************************************************
* File cc_com.h Start!
****************************************************************************************************/
#ifndef _CC_COM_H
#define _CC_COM_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
#include "cc_com_messagequeue.h"
#include "cc_com_event.h"
#include "cc_com_mailbox.h"
#include "cc_com_sharedmem.h"
#include "cc_com_pipe.h"
/* components */
#include "cc_service.h"

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* com type */
typedef enum
{
    CC_COM_TYPE_NULL = 0,
    CC_COM_TYPE_MQ,
    CC_COM_TYPE_EVENT,
    CC_COM_TYPE_MAILBOX,
    CC_COM_TYPE_SHAREDMEM,
    CC_COM_TYPE_PIPE,
    CC_COM_TYPE_SOCKET,
    CC_COM_TYPE_END
}cc_com_type_enum;

/* cc_com_func_struct */
typedef struct
{
    cc_result (*send)(cc_int8 *name,cc_uint8 *data,cc_uint16 length);
    cc_result (*revc)(cc_int8 *name,cc_uint8 *data,cc_uint16 length);
    cc_result (*release)(cc_int8 *name,cc_uint8 *data,cc_uint16 length);
}cc_com_func_struct;

/* cc_com_item_struct */
typedef struct
{
    cc_com_messagequeue_struct *messagequeue;
    cc_com_event_struct *event;
    cc_com_mailbox_struct *mailbox;
    cc_com_sharedmem_struct *sharedmem;
    cc_com_pipe_struct *pipe;
}cc_com_item_struct;

/* cc_com */
typedef struct
{
    /* inherit object */
    cc_object_struct object;
    /* service */
    cc_service_struct service;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* func */
    cc_com_func_struct func;
    /* item */
    cc_com_item_struct item;
}cc_com_struct;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

/* init */
cc_result cc_com_init(cc_void);
cc_result cc_com_getobject(cc_object_struct **object);
cc_result cc_com_mainfunction(cc_void);
/* sub module */
cc_result cc_com_mqinit(cc_void);
cc_result cc_com_eventinit(cc_void);
cc_result cc_com_mailboxinit(cc_void);
cc_result cc_com_sharedmeminit(cc_void);
cc_result cc_com_pipeinit(cc_void);
cc_result cc_com_socketinit(cc_void);

cc_result cc_com_send(cc_int8 *name,cc_uint8 *data,cc_uint16 length);
cc_result cc_com_revc(cc_int8 *name,cc_uint8 *data,cc_uint16 length);
cc_result cc_com_release(cc_int8 *name,cc_uint8 *data,cc_uint16 length);

#endif /* _CC_COM_H */
/****************************************************************************************************
* File cc_com.h End!
****************************************************************************************************/

