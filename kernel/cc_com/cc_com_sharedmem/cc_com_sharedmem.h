
/****************************************************************************************************
* File com_sharedmem.h Start!
****************************************************************************************************/

#ifndef _COM_SHAREDMEM_H
#define _COM_SHAREDMEM_H

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

/* cc_com_sharedmem */
typedef struct
{
    cc_uint8 id;
}cc_com_sharedmem_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_com_sharedmem_init(cc_void);
cc_result cc_com_sharedmem_mainfunction(cc_void);

#endif /* _COM_SHAREDMEM_H */
/****************************************************************************************************
* File com_sharedmem.h End!
****************************************************************************************************/

