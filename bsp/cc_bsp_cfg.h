
/****************************************************************************************************
* File bsp_cfg.h Start!
****************************************************************************************************/

#ifndef _BSP_CFG_H
#define _BSP_CFG_H

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

/* cc_bsp_cfg */
typedef struct
{
    cc_uint8 id;
}cc_bsp_cfg_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_bsp_cfg_init(cc_void);
cc_result cc_bsp_cfg_mainfunction(cc_void);

#endif /* _BSP_CFG_H */
/****************************************************************************************************
* File bsp_cfg.h End!
****************************************************************************************************/

