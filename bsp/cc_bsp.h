
/****************************************************************************************************
* File bsp.h Start!
****************************************************************************************************/

#ifndef _BSP_H
#define _BSP_H

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

/* cc_bsp */
typedef struct
{
    cc_uint8 id;
}cc_bsp_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_bsp_init(cc_void);
cc_result cc_bsp_mainfunction(cc_void);

#endif /* _BSP_H */
/****************************************************************************************************
* File bsp.h End!
****************************************************************************************************/

