
/****************************************************************************************************
* File ultrasonic.h Start!
****************************************************************************************************/

#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

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

/* cc_ultrasonic */
typedef struct
{
    cc_uint8 id;
}cc_ultrasonic_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_ultrasonic_init(cc_void);
cc_result cc_ultrasonic_mainfunction(cc_void);

#endif /* _ULTRASONIC_H */
/****************************************************************************************************
* File ultrasonic.h End!
****************************************************************************************************/

