
/****************************************************************************************************
* File motor.h Start!
****************************************************************************************************/

#ifndef _MOTOR_H
#define _MOTOR_H

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

/* cc_motor */
typedef struct
{
    cc_uint8 id;
}cc_motor_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_motor_init(cc_void);
cc_result cc_motor_mainfunction(cc_void);

#endif /* _MOTOR_H */
/****************************************************************************************************
* File motor.h End!
****************************************************************************************************/

