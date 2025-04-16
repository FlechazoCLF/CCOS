
/****************************************************************************************************
* File cc_service_cfg.h Start!
****************************************************************************************************/
#ifndef _CC_SERVICE_CFG_H
#define _CC_SERVICE_CFG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"
#include "cc_thread.h"
#include "cc_service.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/* number of service */
#define CC_SERVICE_CFG_NUMBER (16u)

/* service aging time */
#define CC_SERVICE_CFG_AGINGTIME (1*60*1000)

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* service func info */
typedef struct
{
    /* service name */
    cc_int8 *name;
    /* service func number */
    cc_uint32 funcnum;
    /* service func interface */
    cc_int8 *func;
    /* service parameter info */

}cc_service_cfg_funcinfo_struct;

/* service */
typedef struct
{
    /* ctrlidx */
    cc_uint32 ctrlidx;
    /* name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* service pointer */
    cc_service_struct *service;
    /* service level */
    cc_service_level_enum level;
    /* service method */
    cc_service_method_enum method;
    /* service type */
    cc_service_type_enum type;
    /* state */
    cc_service_state_enum state;
    /* version */
    cc_uint32 version;
    /* func */
    cc_service_func_struct *func;
    /* parent */
    cc_thread_struct *parent;
    /* list */
    cc_list_struct *list;
    /* log */
    cc_int8 log[CC_LOG_MAX_LEN];
    /* time */
    cc_uint32 inittime;
    cc_uint32 starttime;
    cc_uint32 stoptime;
    cc_uint32 agingtime;
}cc_service_table_struct;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

cc_service_table_struct *cc_service_cfg_gettable(cc_void);
cc_result cc_service_cfg_recv(cc_int8 *dstname,cc_int8 *srcname,cc_uint8 *data,cc_uint16 len,cc_service_msgtype_enum type);

#ifdef __cplusplus
}
#endif /* _SERVICE_CFG_H */

#endif /* _CLOCK_H */
/****************************************************************************************************
* File cc_service_cfg.h End!
****************************************************************************************************/

