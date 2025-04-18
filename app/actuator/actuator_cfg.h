
/****************************************************************************************************
* File actuator_cfg.h Start!
****************************************************************************************************/

#ifndef _ACTUATOR_CFG_H
#define _ACTUATOR_CFG_H

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

/* cc_actuator_cfg */
typedef struct
{
    cc_uint8 id;
}cc_actuator_cfg_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_actuator_cfg_init(cc_void);
cc_result cc_actuator_cfg_mainfunction(cc_void);

#endif /* _ACTUATOR_CFG_H */
/****************************************************************************************************
* File actuator_cfg.h End!
****************************************************************************************************/

