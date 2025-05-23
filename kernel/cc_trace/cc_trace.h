
/****************************************************************************************************
* File cc_trace.h Start!
****************************************************************************************************/
#ifndef _CC_TRACE_H
#define _CC_TRACE_H

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

/* check variable */
#define CHECK_VAR(r,v) \
    {\
        if((v) == CC_NULL)\
        {\
            (r) = CC_E_NOT_OK_NULL_VAR;\
            continue;\
        }\
    }

/* check pointer */
#define CHECK_PTR(r,p) \
    {\
        if((p) == CC_NULL_PTR)\
        {\
            (r) = CC_E_NOT_OK_NULL_POINTER;\
            continue;\
        }\
    }

/* check result */
#define CHECK_FUNC(r,func) \
    {\
        (r) |= (func);\
        if(CC_E_OK != (r))\
        {\
            continue;\
        }\
    }

/* check logic */
#define CHECK_LOGIC(r,logic) \
    if(!(logic))\
    {\
        r |= CC_E_NOT_OK;\
        continue;\
    }

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_TRACE_H */
/****************************************************************************************************
* File cc_trace.h End!
****************************************************************************************************/

