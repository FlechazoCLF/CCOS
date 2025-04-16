
/****************************************************************************************************
* File cc_network_eth_igmp_cfg.h Start!
****************************************************************************************************/

#ifndef _CC_NETWORK_ETH_IGMP_CFG_H
#define _CC_NETWORK_ETH_IGMP_CFG_H

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

/* cc_network_eth_igmp_cfg */
typedef struct
{
    cc_uint8 id;
}cc_network_eth_igmp_cfg_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_network_eth_igmp_cfg_init(cc_void);
cc_result cc_network_eth_igmp_cfg_mainfunction(cc_void);

#endif /* _CC_NETWORK_ETH_IGMP_CFG_H */
/****************************************************************************************************
* File cc_network_eth_igmp_cfg.h End!
****************************************************************************************************/

