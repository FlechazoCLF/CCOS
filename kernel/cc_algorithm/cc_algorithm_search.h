
/****************************************************************************************************
* File algorithm_search.h Start!
****************************************************************************************************/

#ifndef _ALGORITHM_SEARCH_H
#define _ALGORITHM_SEARCH_H

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

/* cc_algorithm_search */
typedef struct
{
    cc_uint8 id;
}cc_algorithm_search_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_algorithm_search_init(cc_void);
cc_result cc_algorithm_search_mainfunction(cc_void);

/* Search */
/* Linear Search */
cc_result cc_algorithm_search_linear(cc_void);
/* Binary Search */
cc_result cc_algorithm_search_binary(cc_uint32 *pos,cc_uint8 *dst,cc_uint32 dstlen,cc_uint8 *value,cc_uint32 valuelen);
/* Hashing Search */

#endif /* _ALGORITHM_SEARCH_H */
/****************************************************************************************************
* File algorithm_search.h End!
****************************************************************************************************/

