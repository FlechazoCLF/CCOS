
/****************************************************************************************************
* File cc_mem_cfg.h Start!
****************************************************************************************************/
#ifndef _CC_MEM_CFG_H
#define _CC_MEM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_type.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* publish func table */
typedef struct
{
    cc_uint8 ctrlidx;
    cc_int8 funcname[CC_NAME_MAX_LEN];
    void *func;
    cc_int8 parameter[CC_PARAMETER_MAX_LEN];
    cc_int8 info[CC_INFO_MAX_LEN];
}cc_mem_cfg_functable_struct;

/* message type */
typedef struct
{
    cc_uint8 ctrlidx;
    cc_uint8 reserve[3];
}cc_mem_cfg_msgformatctrl_struct;

typedef struct
{
    cc_mem_cfg_msgformatctrl_struct ctrl;
    cc_uint32 parameter1;
    cc_uint32 parameter2;
    cc_uint32 parameter3;
}cc_mem_cfg_msgformat_struct;

typedef union
{
    cc_mem_cfg_msgformat_struct msg;
    cc_uint8 bytes[16];
}cc_mem_cfg_msgformat_union;

/* func pointer type */
typedef union
{
    cc_result (*func)(cc_void);
    /* init */
    cc_result (*init)(cc_void);
    /* detach */
    cc_result (*detach)(cc_void);
    /* memcpy */
    cc_result (*memcpy)(cc_void *,cc_void *,cc_uint32 );
    /* memset */
    cc_result (*memset)(cc_void *,cc_uint32 ,cc_uint32 );
    /* memcmp */
    cc_result (*memcmp)(cc_void *,cc_void *,cc_uint32 );
    /* strlen */
    cc_result (*strlen)(cc_int8 *,cc_uint32 *);
    /* strnlen */
    cc_result (*strnlen)(cc_int8 *,cc_uint32 *,cc_uint32 );
    /* strcpy */
    cc_result (*strcpy)(cc_int8 *,cc_int8 *);
    /* strncpy */
    cc_result (*strncpy)(cc_int8 *,cc_int8 *,cc_uint32 );
    /* strcmp */
    cc_result (*strcmp)(cc_int8 *,cc_int8 *);
    /* strncmp */
    cc_result (*strncmp)(cc_int8 *,cc_int8 *,cc_uint32 );
    /* strstr */
    cc_result (*strstr)(cc_int8 *,cc_int8 *,cc_int8 **);
}cc_mem_cfg_funcptr_union;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

cc_result cc_mem_cfg_servicecall(cc_uint8 *data,cc_uint16 len);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_MEM_CFG_H */
/****************************************************************************************************
* File cc_mem_cfg.h End!
****************************************************************************************************/

