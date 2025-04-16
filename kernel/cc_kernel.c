
/****************************************************************************************************
* File cc_kernel.c Start!
****************************************************************************************************/
/*
 *                               ___   ___   ___     ___
 *                              / __| / __| /   \  / ___)
 *                             | /   | /   |  /\ |( (___
 *                             | \__ | \__ |  \/ | \___ )
 *                              \___| \___| \___/ (____/
 * 
 */
/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_kernel.h"
#include "cc_trace.h"
#include "cc_timer.h"
#include "cc_thread.h"
#include "cc_scheduler.h"
#include "cc_kernel_cfg.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* kernel */
cc_kernel_struct cc_kernel_t;
/* init flag */
cc_boolean cc_kernel_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_kernel_startup()
****************************************************************************************************/
cc_result cc_kernel_startup(void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* object init */
        CHECK_FUNC(result,cc_object_init());

        /* timer init */
        CHECK_FUNC(result,cc_timer_init());

        /* thread init */
        CHECK_FUNC(result,cc_thread_init());

        /* scheduler init */
        CHECK_FUNC(result,cc_scheduler_init());

        /* scheduler startup */
        CHECK_FUNC(result,cc_scheduler_start());

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_kernel_showinfo()
****************************************************************************************************/
cc_result cc_kernel_showinfo(void)
{
    cc_result result = CC_E_OK;
    cc_int8 *info = "\n\
*\n\
*    ___   ___   ___     ___\n\
*   / __| / __| /   \\  / ___)\n\
*  | /   | /   |  /\\ |( (___\n\
*  | \\__ | \\__ |  \\/ | \\___ )\n\
*   \\___| \\___| \\___/ (____/\n\
*\n\
";

    do
    {
        /* show info */
        if(info != CC_NULL_PTR)
        {
            ____________________________TO_DO__________________________
        }

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_kernel_init()
****************************************************************************************************/
cc_result cc_kernel_init(void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* hw init */
        KERNEL_HW_BOARD_INIT();

        /* show info */
        CHECK_FUNC(result,cc_kernel_showinfo());

        /* start up kernel */
        CHECK_FUNC(result,cc_kernel_startup());

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_kernel_entry()
****************************************************************************************************/
cc_result cc_kernel_entry(void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* kernel init */
        CHECK_FUNC(result,cc_kernel_init());

    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_main_kernel_entry()
* main()
****************************************************************************************************/
cc_result cc_main_kernel_entry(void)
{
    cc_result result = CC_E_OK;

    do
    {
        /* kernel entry */
        CHECK_FUNC(result,cc_kernel_entry());

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_kernel.c End!
****************************************************************************************************/
