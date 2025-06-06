
/****************************************************************************************************
* File cc_com_ringbuffer_cfg.h Start!
****************************************************************************************************/

#ifndef _CC_COM_RINGBUFFER_CFG_H
#define _CC_COM_RINGBUFFER_CFG_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
/* sub module */
/* components */

/* ui */
/* cpp */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type
****************************************************************************************************/

/* cc_com_ringbuffer_cfg */
typedef struct
{
    cc_uint8 id;
}cc_com_ringbuffer_cfg_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_com_ringbuffer_cfg_init(cc_void);
cc_result cc_com_ringbuffer_cfg_mainfunction(cc_void);

#endif /* _CC_COM_RINGBUFFER_CFG_H */
/****************************************************************************************************
* File cc_com_ringbuffer_cfg.h End!
****************************************************************************************************/

