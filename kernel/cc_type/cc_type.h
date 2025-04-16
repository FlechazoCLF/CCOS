
/****************************************************************************************************
* File cc_type.h Start!
****************************************************************************************************/
#ifndef _CC_TYPE_H
#define _CC_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/****************************************************************************************************
* Include
****************************************************************************************************/

/****************************************************************************************************
* Define
****************************************************************************************************/

/* to do list */
#define _CC_TO_DO_
#define ____________________________TO_DO__________________________ _CC_TO_DO_

/* true & false */
#define CC_TRUE (1u)
#define CC_FALSE (0u)
/* on & off */
#define CC_ON (CC_TRUE)
#define CC_OFF (CC_FALSE)
/* null & null_ptr */
#define CC_NULL (0u)
#define CC_NULL_PTR ((void *)0u)
/* len of name & log */
#define CC_NAME_MAX_LEN (16)
#define CC_LOG_MAX_LEN (32)
#define CC_PARAMETER_MAX_LEN (48)
#define CC_INFO_MAX_LEN (48)

/* reflect struct                                                    ptr    -   (&member - 0) */
#define CC_REFLECT_STRUCT(ptr,type,member) ( (type *)( ( (cc_int8 *)(ptr) ) - ( (cc_uint32)(&((type *)0)->member) ) ) )

/****************************************************************************************************
* Object
****************************************************************************************************/
/* object type & authority */
#define CC_OBJECT_TYPE(c) CC_OBJECT_TYPE_##c
#define CC_OBJECT_AUTHORITY(c) CC_OBJECT_AUTHORITY_##c
/* object reflect list */
#define CC_OBJECT_REFLECT_LIST(ptr,type,member) CC_REFLECT_STRUCT(ptr,type,member)

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/* typedef base type of data */
typedef void cc_void;
typedef unsigned char cc_boolean;
typedef unsigned char cc_uint8;
typedef unsigned short cc_uint16;
typedef unsigned int cc_uint32;
typedef unsigned long long cc_uint64;
typedef char cc_int8;
typedef short cc_int16;
typedef int cc_int32;
typedef long long cc_int64;
typedef float cc_float;
typedef double cc_double;
typedef long double cc_double128;

/* type of return value */
typedef enum
{
    CC_E_OK = 0,
    CC_E_NOT_OK,
    CC_E_NOT_OK_UNINIT,
    CC_E_NOT_OK_NULL_VAR,
    CC_E_NOT_OK_NULL_POINTER,
    CC_E_NOT_OK_NOT_FIND,
    /* strcmp */
    CC_E_NOT_OK_SMALLER,
    CC_E_NOT_OK_BIGGER,
    CC_E_END
}cc_result;

/* object state */
typedef enum
{
    CC_OBJECT_STATE_UNINIT = 0,
    CC_OBJECT_STATE_INIT,
    CC_OBJECT_STATE_REGISTER,
    CC_OBJECT_STATE_END
}cc_object_state_enum;

/* object base type */
typedef enum
{
    CC_USER = 0,
    CC_TASK,
    CC_SERVICE,
    CC_THREAD,
    CC_KERNEL,
    CC_END
}cc_object_basetype_enum;

/* object type */
typedef enum
{
    CC_OBJECT_TYPE(CC_USER) = 0,
    CC_OBJECT_TYPE(CC_TASK),
    CC_OBJECT_TYPE(CC_SERVICE),
    CC_OBJECT_TYPE(CC_THREAD),
    CC_OBJECT_TYPE(CC_KERNEL),
    CC_OBJECT_TYPE(CC_END)
}cc_object_type_enum;

/* object flag */
typedef enum
{
    CC_OBJECT_FLAG_FREE = 0,
    CC_OBJECT_FLAG_LOCK,
    CC_OBJECT_FLAG_END
}cc_object_flag_enum;

/* object info */
typedef struct
{
    cc_int8 log[CC_LOG_MAX_LEN];
}cc_object_info_struct;

/* object authority */
typedef enum
{
    CC_OBJECT_AUTHORITY(CC_USER) = 0,
    CC_OBJECT_AUTHORITY(CC_TASK),
    CC_OBJECT_AUTHORITY(CC_SERVICE),
    CC_OBJECT_AUTHORITY(CC_THREAD),
    CC_OBJECT_AUTHORITY(CC_KERNEL),
    CC_OBJECT_AUTHORITY(CC_END)
}cc_object_authority_enum;

/* list */
typedef struct cc_list_struct_tag
{
    struct cc_list_struct_tag *prev;
    struct cc_list_struct_tag *next;
}cc_list_struct;

/* object */
typedef struct cc_object_struct_tag
{
    /* parent */
    struct cc_object_struct_tag *parent;
    /* object name */
    cc_int8 name[CC_NAME_MAX_LEN];
    /* object id */
    cc_uint32 id;
    /* object state */
    cc_object_state_enum state;
    /* object type */
    cc_object_type_enum type;
    /* object flag */
    cc_object_flag_enum flag;
    /* object info */
    cc_object_info_struct info;
    /* object authority */
    cc_object_authority_enum authority;
    /* object list */
    cc_list_struct list;
}cc_object_struct;

/****************************************************************************************************
* Function Interface
****************************************************************************************************/

cc_result cc_object_init(cc_void);
cc_result cc_object_detach(cc_void);
cc_result cc_object_create(cc_object_type_enum type,cc_object_struct *object);
cc_result cc_object_delete(cc_void);
cc_result cc_object_register(cc_object_struct *object);
cc_result cc_object_deregister(cc_int8 *name);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CC_TYPE_H */
/****************************************************************************************************
* File cc_type.h End!
****************************************************************************************************/
