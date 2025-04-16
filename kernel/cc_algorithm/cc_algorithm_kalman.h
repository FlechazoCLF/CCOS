
/****************************************************************************************************
* File cc_algorithm_kalman.h Start!
****************************************************************************************************/

#ifndef _CC_ALGORITHM_KALMAN_H
#define _CC_ALGORITHM_KALMAN_H

/****************************************************************************************************
* Include
****************************************************************************************************/
/* type */
#include "cc_type.h"
/* log */
#include "cc_trace.h"
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

/* cc_algorithm_kalmanfilter */
/*
* [predict] : 1、(^x_k^-) = F_k * ^x_(k-1) + B_k * u_k
*             2、(P_k^-) = F_k * P_(k-1) * F_k^T + Q_k
* (^x_k^-):The Prior estimated value of time k
* F_k:Transition matrix
* B_k u_k:Control input items
* (P_k^-):Prior covariance matrix
* Q_k:Process noise covariance matrix
*
* [update] : 1、K_k = (P_k^- * H_k^T) / (H_k * P_k^- * H_k^T + R_k)
*            2、(^x_k) = ^x_k^- + K_k(z_k - H_k * ^x_k^-)
*            3、P_k = (I - K_k * H_k) * P_k^-
* K_k:Kalman gain
* H_k:observation matrix
* R_k:Measure the covariance matrix of noise
* z_k:Actual measurement value
* (^x_k):Posterior state estimation
* P_k:Posterior covariance matrix
* I:Identity matrix
*
* [logic] : (^x_k) = ^x_k^- + K_k(z_k - H_k * ^x_k^-)
*              |       |       |   |     |
*              V       |       |   |     V                        example: [pos,speed]
*            value     |       |   V    H_k = 1(one-dimensional) /example: [1,0]
*                      |       |  Measurement value
*                      |       V
*                      |      K_k = (P_k^- * H_k^T) / (H_k * P_k^- * H_k^T + R_k)
*                      |          = P_k^- / P_k^- + R_k
*                      |          = (F_k * P_(k-1) * F_k^T + Q_k) / (F_k * P_(k-1) * F_k^T + Q_k + R_k)
*                      |          = (P_(k-1) + Q) / (P_(k-1) + Q + R)
*                      V
*                   (^x_k^-) = F_k * ^x_(k-1) + B_k * u_k
*/
typedef struct
{
    cc_double x;
    cc_double P;
    cc_double Q;
    cc_double R;
    cc_double H;
    cc_double F;
    /* Actual measurement value */
    cc_double z;
}cc_algorithm_kalmanfilter_struct;

/* cc_algorithm_kalmanfilter_func_struct */
typedef struct
{
    cc_result (*predict_x)(cc_double *x_pred,cc_double x_prev);
}cc_algorithm_kalmanfilter_func_struct;

/* cc_algorithm_kalman */
typedef struct
{
    cc_algorithm_kalmanfilter_struct filter;
    cc_algorithm_kalmanfilter_func_struct func;
}cc_algorithm_kalman_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/
/* init */
cc_result cc_algorithm_kalman_init(cc_algorithm_kalman_struct *cfg_t);
/* calc */
cc_result cc_algorithm_kalman_calc(cc_double *value,cc_double measurementvalue);
/* get & set */
cc_result cc_algorithm_kalman_get_x(cc_double *value);
cc_result cc_algorithm_kalman_get_Q(cc_double *value);
cc_result cc_algorithm_kalman_get_R(cc_double *value);
cc_result cc_algorithm_kalman_set_Q(cc_double value);
cc_result cc_algorithm_kalman_set_R(cc_double value);
/* mainfuntion */
cc_result cc_algorithm_kalman_mainfunction(cc_void);

#endif /* _CC_ALGORITHM_KALMAN_H */
/****************************************************************************************************
* File cc_algorithm_kalman.h End!
****************************************************************************************************/

