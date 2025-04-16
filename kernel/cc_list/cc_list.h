
/****************************************************************************************************
* File cc_list.h Start!
****************************************************************************************************/
#ifndef _CC_LIST_H
#define _CC_LIST_H

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

/* get entry by list */
#define CC_LIST_GETENTRY

/* list init */
#define CC_LIST_INIT(list) \
    do\
    {\
        list->prev = list;\
        list->next = list;\
    } while (0u);
/* list detach */
#define CC_LIST_DETACH(list) \
    do\
    {\
        list->prev = CC_NULL_PTR;\
        list->next = CC_NULL_PTR;\
    } while (0u);
/* list insert before */
#define CC_LIST_INSERT_BEFORE(list,newlist) \
    do\
    {\
        newlist->next = list;\
        newlist->prev = list->prev;\
        list->prev->next = newlist;\
        list->prev = newlist;\
    } while (0u);
/* list insert after */
#define CC_LIST_INSERT_AFTER(list,newlist) \
    do\
    {\
        newlist->prev = list;\
        newlist->next = list->next;\
        list->next->prev = newlist;\
        list->next = newlist;\
    } while (0u);
/* list remove */
#define CC_LIST_REMOVE(list) \
    do\
    {\
        list->next->prev = list->prev;\
        list->prev->next = list->next;\
        list->prev = list;\
        list->next = list;\
    } while (0u);

/****************************************************************************************************
* Type Define
****************************************************************************************************/

typedef enum
{
    CC_LIST_INSERT_DIRECT_AFTER = 0,
    CC_LIST_INSERT_DIRECT_BEFORE,
    CC_LIST_INSERT_DIRECT_END
}cc_list_insert_direct_enum;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/
cc_result cc_list_init(cc_list_struct *list);
cc_result cc_list_detach(cc_list_struct *list);
cc_result cc_list_insert(cc_list_insert_direct_enum direct,cc_list_struct *list,cc_list_struct *newlist);
cc_result cc_list_insert_before(cc_list_struct *list,cc_list_struct *newlist);
cc_result cc_list_insert_after(cc_list_struct *list,cc_list_struct *newlist);
cc_result cc_list_remove(cc_list_struct *list);
cc_result cc_list_getlen(cc_list_struct *list,cc_uint32 *len);
cc_result cc_list_checknull(cc_list_struct *list);
cc_result cc_list_search(cc_list_struct *dstlist,cc_list_struct *srclist);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_LIST_H */
/****************************************************************************************************
* File cc_list.h End!
****************************************************************************************************/
