
/****************************************************************************************************
* File com_mailbox.h Start!
****************************************************************************************************/

#ifndef _COM_MAILBOX_H
#define _COM_MAILBOX_H

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

/* cc_com_mailbox */
typedef struct
{
    cc_uint8 id;
}cc_com_mailbox_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_com_mailbox_init(cc_void);
cc_result cc_com_mailbox_mainfunction(cc_void);

#endif /* _COM_MAILBOX_H */
/****************************************************************************************************
* File com_mailbox.h End!
****************************************************************************************************/

