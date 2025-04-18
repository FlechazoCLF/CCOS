
/****************************************************************************************************
* File cc_network_eth_arp.h Start!
****************************************************************************************************/

#ifndef _CC_NETWORK_ETH_ARP_H
#define _CC_NETWORK_ETH_ARP_H

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

/* cc_network_eth_arp */
typedef struct
{
    cc_uint8 id;
}cc_network_eth_arp_struct;

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/****************************************************************************************************
* Function
****************************************************************************************************/

cc_result cc_network_eth_arp_init(cc_void);
cc_result cc_network_eth_arp_mainfunction(cc_void);

#endif /* _CC_NETWORK_ETH_ARP_H */
/****************************************************************************************************
* File cc_network_eth_arp.h End!
****************************************************************************************************/

