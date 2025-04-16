
/****************************************************************************************************
* File components.h Start!
****************************************************************************************************/

#ifndef _COMPONENTS_H
#define _COMPONENTS_H

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

/* cc_components */
typedef struct
{
    /* inherit object */
    cc_object_struct object;

}cc_components_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_components_init(cc_void);
cc_result cc_components_getobject(cc_object_struct **object);
cc_result cc_components_mainfunction(cc_void);

#endif /* _COMPONENTS_H */
/****************************************************************************************************
* File components.h End!
****************************************************************************************************/

