
/****************************************************************************************************
* File cc_service.h Start!
****************************************************************************************************/
#ifndef _CC_SERVICE_H
#define _CC_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"
#include "cc_thread.h"
#include "cc_type_cfg.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/* service msg data max len */
#define CC_SERVICE_CFG_MSGDATA_MAX_LEN (64u)
#define CC_SERVICE_CFG_MSG_MAX_LEN (12 + CC_NAME_MAX_LEN + CC_NAME_MAX_LEN + CC_SERVICE_CFG_MSGDATA_MAX_LEN)

/* service reflect list */
#define CC_SERVICE_REFLECT_LIST(ptr) CC_REFLECT_STRUCT(ptr,cc_service_struct,list)

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* level */
typedef enum
{
    CC_SERVICE_LEVEL_USER = 0,
    CC_SERVICE_LEVEL_COMPONENTS,
    CC_SERVICE_LEVEL_KERNEL,
    CC_SERVICE_LEVEL_END
}cc_service_level_enum;

/* type */
typedef enum
{
    CC_SERVICE_TYPE_USER = 0,
    CC_SERVICE_TYPE_INPUT,
    CC_SERVICE_TYPE_OUTPUT,
    CC_SERVICE_TYPE_COM,
    CC_SERVICE_TYPE_MEMORY,
    CC_SERVICE_TYPE_ALGORITHM,
    CC_SERVICE_TYPE_TIMER,
    CC_SERVICE_TYPE_LOCK,
    CC_SERVICE_TYPE_TRACE,
    CC_SERVICE_TYPE_KERNEL,
    CC_SERVICE_TYPE_END
}cc_service_type_enum;

/* method */
typedef enum
{
    CC_SERVICE_METHOD_LOCAL = 0,
    CC_SERVICE_METHOD_REMOTE,
    CC_SERVICE_METHOD_END
}cc_service_method_enum;

/* state */
typedef enum
{
    CC_SERVICE_STATE_UNINIT = 0,
    CC_SERVICE_STATE_INIT,
    CC_SERVICE_STATE_READY,
    CC_SERVICE_STATE_RUNNING,
    CC_SERVICE_STATE_BLOCK,
    CC_SERVICE_STATE_WAIT,
    CC_SERVICE_STATE_STOP,
    CC_SERVICE_STATE_ALIVE,
    CC_SERVICE_STATE_DEAD,
    CC_SERVICE_STATE_END
}cc_service_state_enum;

/* service msg type */
typedef enum
{
    CC_SERVICE_MSGTYPE_USER = 0x00000000,
    /* insert your type */
    CC_SERVICE_MSGTYPE_TASK = 0x00001000,
    /* insert your type */
    CC_SERVICE_MSGTYPE_SERVICE = 0x00002000,
    CC_SERVICE_MSGTYPE_SERVICE_ALIVE = 0x00002001,
    /* insert your type */
    CC_SERVICE_MSGTYPE_THREAD = 0x00004000,
    /* insert your type */
    CC_SERVICE_MSGTYPE_KERNEL = 0x00008000,
    /* insert your type */
    CC_SERVICE_MSGTYPE_IPC = 0x00010000,
    /* insert your type */
    CC_SERVICE_MSGTYPE_END
}cc_service_msgtype_enum;

/* service info */
typedef struct
{
    /* ctrlidx */
    cc_uint32 id;
    /* state */
    cc_service_state_enum state;
    /* flag */
    ____________________________TO_DO__________________________
    /* error */
    ____________________________TO_DO__________________________
    /* time */
    cc_uint32 inittime;
    cc_uint32 starttime;
    cc_uint32 stoptime;
    /* version */
    cc_uint32 version;
    /* log */
    cc_int8 log[CC_LOG_MAX_LEN];
}cc_service_info_struct;

/* service scheduler */
typedef struct
{
    /* init */
    cc_result (*init)(cc_void);
    /* mainfunction */
    cc_result (*mainfunction)(cc_void);
}cc_service_scheduler_struct;

/* service signal */
typedef struct
{
    /* mutex */
    cc_uint32 mutex;
    /* event */
    cc_uint32 event;
    /* semaphore */
    cc_uint32 semaphore;
    /* signal */
    cc_uint32 signal;
}cc_service_signal_struct;

/* service func */
typedef struct
{
    /* send */
    cc_result (*send)(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);
    /* recv */
    cc_result (*recv)(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);
}cc_service_func_struct;

/* service */
typedef struct
{
    /* parent */
    cc_thread_struct *parent;
    /* service inherit object */
    cc_object_struct *object;
    /* service name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* service method */
    cc_service_method_enum method;
    /* service level */
    cc_service_level_enum level;
    /* service type */
    cc_service_type_enum type;
    /* list */
    cc_list_struct list;
    /* info */
    cc_service_info_struct info;
    /* scheduler */
    cc_service_scheduler_struct scheduler;
    /* signal */
    cc_service_signal_struct signal;
    /* func */
    cc_service_func_struct func;
}cc_service_struct;

/* msg format */
typedef struct
{
    /* 2 byte * 4 */
    cc_type_uint16_union head;
    cc_type_uint16_union crc;
    cc_type_uint16_union len;
    cc_type_uint16_union user;
    /* 4 byte */
    cc_service_msgtype_enum type;
    /* src service name */
    cc_int8 srcname[CC_NAME_MAX_LEN];
    /* dst service name */
    cc_int8 dstname[CC_NAME_MAX_LEN];
    /* data */
    cc_uint8 data[CC_SERVICE_CFG_MSGDATA_MAX_LEN];
}cc_service_cfg_msgformat_struct;

typedef union
{
    cc_service_cfg_msgformat_struct msg;
    cc_uint8 bytes[CC_SERVICE_CFG_MSG_MAX_LEN];
}cc_service_cfg_msgformat_union;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

cc_result cc_service_init(cc_void);
cc_result cc_service_detach(cc_void);
cc_result cc_service_create(cc_int8 *name);
cc_result cc_service_delete(cc_int8 *name);
cc_result cc_service_register(cc_service_struct *service);
cc_result cc_service_deregister(cc_int8 *name);
cc_result cc_service_find(cc_int8 *name,cc_service_struct **service);
cc_result cc_service_start(cc_int8 *name);
cc_result cc_service_stop(cc_int8 *name);
cc_result cc_service_mainfunction(cc_void);
cc_result cc_service_discover(cc_void);

/* send data to other service service send interface */
cc_result cc_service_send(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);
/* recv data from other service */
cc_result cc_service_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_SERVICE_H */
/****************************************************************************************************
* File cc_service.h End!
****************************************************************************************************/

