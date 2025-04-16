
/****************************************************************************************************
* File cc_algorithm_kalman.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_algorithm_kalman.h"
/* log */
#include "cc_trace.h"
/* sub module */
/* components */

/****************************************************************************************************
* Define
****************************************************************************************************/

/****************************************************************************************************
* Type
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/* cc_algorithm_kalman */
cc_algorithm_kalman_struct cc_algorithm_kalman_t;
/* init flag */
cc_boolean cc_algorithm_kalman_initflag = CC_FALSE;

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_algorithm_kalman_init()
****************************************************************************************************/
cc_result cc_algorithm_kalman_init(cc_algorithm_kalman_struct *cfg_t)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,cfg_t);
        /* init */
        cc_algorithm_kalman_t.filter.x = 0.0;
        cc_algorithm_kalman_t.filter.P = 1.0;
        /* Predicting Noise */
        cc_algorithm_kalman_t.filter.Q = 0.1;
        /* sensor noise */
        cc_algorithm_kalman_t.filter.R = 0.1;
        cc_algorithm_kalman_t.filter.H = 1.0;
        cc_algorithm_kalman_t.filter.F = 1.0;
        /* Actual measurement value */
        cc_algorithm_kalman_t.filter.z = 0.0;

        /* func */
        cc_algorithm_kalman_t.func.predict_x = cfg_t->func.predict_x;
        cc_algorithm_kalman_initflag = CC_TRUE;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_get_x()
****************************************************************************************************/
cc_result cc_algorithm_kalman_get_x(cc_double *value)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,value);
        /* imoletement */
        *value = cc_algorithm_kalman_t.filter.x;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_get_Q()
****************************************************************************************************/
cc_result cc_algorithm_kalman_get_Q(cc_double *value)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,value);
        /* imoletement */
        *value = cc_algorithm_kalman_t.filter.Q;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_get_R()
****************************************************************************************************/
cc_result cc_algorithm_kalman_get_R(cc_double *value)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,value);
        /* imoletement */
        *value = cc_algorithm_kalman_t.filter.R;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_set_Q()
****************************************************************************************************/
cc_result cc_algorithm_kalman_set_Q(cc_double value)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_algorithm_kalman_initflag == CC_TRUE));
        /* imoletement */
        cc_algorithm_kalman_t.filter.Q = value;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_set_R()
****************************************************************************************************/
cc_result cc_algorithm_kalman_set_R(cc_double value)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_LOGIC(result,(cc_algorithm_kalman_initflag == CC_TRUE));
        /* imoletement */
        cc_algorithm_kalman_t.filter.R = value;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_predict_x()
****************************************************************************************************/
cc_result cc_algorithm_kalman_predict_x(cc_double *x_pred,cc_double x_prev)
{
    cc_result result = CC_E_OK;
    cc_algorithm_kalmanfilter_struct *filter;

    do
    {
        /* check */
        CHECK_PTR(result,x_pred);
        /* impletement */
        if (cc_algorithm_kalman_t.func.predict_x != CC_NULL_PTR)
        {
            /* user predict x */
            cc_algorithm_kalman_t.func.predict_x(x_pred,x_prev);
        }
        else
        {
            /* example */
            filter = &cc_algorithm_kalman_t.filter;
            *x_pred = filter->F * x_prev;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_predict_P()
****************************************************************************************************/
cc_result cc_algorithm_kalman_predict_P(cc_double *P_pred,cc_double P_prev)
{
    cc_result result = CC_E_OK;
    cc_algorithm_kalmanfilter_struct *filter;

    do
    {
        /* check */
        CHECK_PTR(result,P_pred);
        /* impletement */
        filter = &cc_algorithm_kalman_t.filter;
        *P_pred = filter->F * P_prev * filter->F + filter->Q;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_predict()
****************************************************************************************************/
cc_result cc_algorithm_kalman_predict(cc_algorithm_kalmanfilter_struct *kalmanfilter)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,kalmanfilter);
        CHECK_LOGIC(result,(cc_algorithm_kalman_initflag == CC_TRUE));
        /* impletement */
        cc_algorithm_kalman_predict_x(&kalmanfilter->x,kalmanfilter->x);
        cc_algorithm_kalman_predict_P(&kalmanfilter->P,kalmanfilter->P);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_update_K()
****************************************************************************************************/
cc_result cc_algorithm_kalman_update_K(cc_double *K,cc_algorithm_kalmanfilter_struct *kalmanfilter)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,K);
        CHECK_PTR(result,kalmanfilter);
        CHECK_LOGIC(result,(cc_algorithm_kalman_initflag == CC_TRUE));
        /* impletement */
        *K = (kalmanfilter->P * kalmanfilter->H) / (kalmanfilter->H * kalmanfilter->P * kalmanfilter->H + kalmanfilter->R);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_update_x()
****************************************************************************************************/
cc_result cc_algorithm_kalman_update_x(cc_algorithm_kalmanfilter_struct *kalmanfilter,cc_double measurementvalue,cc_double K)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,kalmanfilter);
        CHECK_LOGIC(result,(cc_algorithm_kalman_initflag == CC_TRUE));
        /* impletement */
        kalmanfilter->x = kalmanfilter->x + K * (measurementvalue - kalmanfilter->H * kalmanfilter->x);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_update_P()
****************************************************************************************************/
cc_result cc_algorithm_kalman_update_P(cc_algorithm_kalmanfilter_struct *kalmanfilter,cc_double K)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,kalmanfilter);
        CHECK_LOGIC(result,(cc_algorithm_kalman_initflag == CC_TRUE));
        /* impletement */
        kalmanfilter->P = (1 - K * kalmanfilter->H) * kalmanfilter->P;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_update()
****************************************************************************************************/
cc_result cc_algorithm_kalman_update(cc_algorithm_kalmanfilter_struct *kalmanfilter,cc_double measurementvalue)
{
    cc_result result = CC_E_OK;
    cc_double K;

    do
    {
        /* check */
        CHECK_PTR(result,kalmanfilter);
        CHECK_LOGIC(result,(cc_algorithm_kalman_initflag == CC_TRUE));
        /* impletement */
        cc_algorithm_kalman_update_K(&K,kalmanfilter);
        cc_algorithm_kalman_update_x(kalmanfilter,measurementvalue,K);
        cc_algorithm_kalman_update_P(kalmanfilter,K);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_mainfunction()
****************************************************************************************************/
cc_result cc_algorithm_kalman_calc(cc_double *value,cc_double measurementvalue)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check */
        CHECK_PTR(result,value);
        CHECK_LOGIC(result,(cc_algorithm_kalman_initflag == CC_TRUE));
        /* calc */
        cc_algorithm_kalman_predict(&cc_algorithm_kalman_t.filter);
        cc_algorithm_kalman_update(&cc_algorithm_kalman_t.filter,measurementvalue);
        /* output */
        cc_algorithm_kalman_get_x(value);
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_kalman_mainfunction()
****************************************************************************************************/
cc_result cc_algorithm_kalman_mainfunction(cc_void)
{
    cc_result result = CC_E_OK;

    do
    {

    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_algorithm_kalman.c End!
****************************************************************************************************/

