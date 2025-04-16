
/****************************************************************************************************
* File cc_timer_cfg.h Start!
****************************************************************************************************/
#ifndef _CC_TIMER_CFG_H
#define _CC_TIMER_CFG_H

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
}cc_timer_cfg_functable_struct;

/* message type */
typedef struct
{
    cc_uint8 ctrlidx;
    cc_uint8 reserve[3];
}cc_timer_cfg_msgformatctrl_struct;

typedef struct
{
    cc_timer_cfg_msgformatctrl_struct ctrl;
    cc_uint32 parameter1;
    cc_uint32 parameter2;
    cc_uint32 parameter3;
}cc_timer_cfg_msgformat_struct;

typedef union
{
    cc_timer_cfg_msgformat_struct msg;
    cc_uint8 bytes[16];
}cc_timer_cfg_msgformat_union;

/* func pointer type */
typedef union
{
    cc_result (*func)(cc_void);
    /* init */
    cc_result (*init)(cc_void);
    /* detach */
    cc_result (*detach)(cc_void);
    /* memcpy */
    cc_result (*create)(cc_void *,cc_void *,cc_uint32 );
    /* memset */
    cc_result (*delete)(cc_void *,cc_uint32 ,cc_uint32 );
    /* memcmp */
    cc_result (*start)(cc_void *,cc_void *,cc_uint32 );
    /* strlen */
    cc_result (*stop)(cc_int8 *,cc_uint32 *);
    /* strnlen */
    cc_result (*getlocaltime)(cc_int8 *,cc_uint32 *,cc_uint32 );
}cc_timer_cfg_funcptr_union;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/
cc_result cc_timer_cfg_servicecall(cc_uint8 *data,cc_uint16 len);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_TIMER_CFG_H */
/****************************************************************************************************
* File cc_timer_cfg.h End!
****************************************************************************************************/

