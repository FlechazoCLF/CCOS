
/****************************************************************************************************
* File cc_algorithm_verify.c Start!
****************************************************************************************************/

/****************************************************************************************************
* Include
****************************************************************************************************/
#include "cc_algorithm_verify.h"
#include "cc_trace.h"

/****************************************************************************************************
* Define
****************************************************************************************************/

/* CRC8 polynomial */
#define CC_ALGORITHM_VERIFY_CRC_INITIAL_VALUE8 (0xFFu)
#define CC_ALGORITHM_VERIFY_CRC_POLYNOMIAL_8   (0x1Du)
#define CC_ALGORITHM_VERIFY_CRC_FINAL_XOR_CRC8 (0xFFu)

/****************************************************************************************************
* Type Define
****************************************************************************************************/

/****************************************************************************************************
* Global Variable
****************************************************************************************************/

/*!
 * The following CRC lookup table was generated automatically
 * by test script using the following model parameters:
 *
 *    Width                  : 8 bits
 *    Polynomial             : 0x1D
 *    Initial Register Value : 0xFF
 *    Reflect Input          : false
 *    Reflect Output         : false
 *    Value To XOR Output    : 0xFF
 *    check value            : 0x4B
 */
cc_uint8 cc_algorithm_verify_crc_table8[256] =
{
    0x00u, 0x1du, 0x3au, 0x27u, 0x74u, 0x69u, 0x4eu, 0x53u,
    0xe8u, 0xf5u, 0xd2u, 0xcfu, 0x9cu, 0x81u, 0xa6u, 0xbbu,
    0xcdu, 0xd0u, 0xf7u, 0xeau, 0xb9u, 0xa4u, 0x83u, 0x9eu,
    0x25u, 0x38u, 0x1fu, 0x02u, 0x51u, 0x4cu, 0x6bu, 0x76u,
    0x87u, 0x9au, 0xbdu, 0xa0u, 0xf3u, 0xeeu, 0xc9u, 0xd4u,
    0x6fu, 0x72u, 0x55u, 0x48u, 0x1bu, 0x06u, 0x21u, 0x3cu,
    0x4au, 0x57u, 0x70u, 0x6du, 0x3eu, 0x23u, 0x04u, 0x19u,
    0xa2u, 0xbfu, 0x98u, 0x85u, 0xd6u, 0xcbu, 0xecu, 0xf1u,
    0x13u, 0x0eu, 0x29u, 0x34u, 0x67u, 0x7au, 0x5du, 0x40u,
    0xfbu, 0xe6u, 0xc1u, 0xdcu, 0x8fu, 0x92u, 0xb5u, 0xa8u,
    0xdeu, 0xc3u, 0xe4u, 0xf9u, 0xaau, 0xb7u, 0x90u, 0x8du,
    0x36u, 0x2bu, 0x0cu, 0x11u, 0x42u, 0x5fu, 0x78u, 0x65u,
    0x94u, 0x89u, 0xaeu, 0xb3u, 0xe0u, 0xfdu, 0xdau, 0xc7u,
    0x7cu, 0x61u, 0x46u, 0x5bu, 0x08u, 0x15u, 0x32u, 0x2fu,
    0x59u, 0x44u, 0x63u, 0x7eu, 0x2du, 0x30u, 0x17u, 0x0au,
    0xb1u, 0xacu, 0x8bu, 0x96u, 0xc5u, 0xd8u, 0xffu, 0xe2u,
    0x26u, 0x3bu, 0x1cu, 0x01u, 0x52u, 0x4fu, 0x68u, 0x75u,
    0xceu, 0xd3u, 0xf4u, 0xe9u, 0xbau, 0xa7u, 0x80u, 0x9du,
    0xebu, 0xf6u, 0xd1u, 0xccu, 0x9fu, 0x82u, 0xa5u, 0xb8u,
    0x03u, 0x1eu, 0x39u, 0x24u, 0x77u, 0x6au, 0x4du, 0x50u,
    0xa1u, 0xbcu, 0x9bu, 0x86u, 0xd5u, 0xc8u, 0xefu, 0xf2u,
    0x49u, 0x54u, 0x73u, 0x6eu, 0x3du, 0x20u, 0x07u, 0x1au,
    0x6cu, 0x71u, 0x56u, 0x4bu, 0x18u, 0x05u, 0x22u, 0x3fu,
    0x84u, 0x99u, 0xbeu, 0xa3u, 0xf0u, 0xedu, 0xcau, 0xd7u,
    0x35u, 0x28u, 0x0fu, 0x12u, 0x41u, 0x5cu, 0x7bu, 0x66u,
    0xddu, 0xc0u, 0xe7u, 0xfau, 0xa9u, 0xb4u, 0x93u, 0x8eu,
    0xf8u, 0xe5u, 0xc2u, 0xdfu, 0x8cu, 0x91u, 0xb6u, 0xabu,
    0x10u, 0x0du, 0x2au, 0x37u, 0x64u, 0x79u, 0x5eu, 0x43u,
    0xb2u, 0xafu, 0x88u, 0x95u, 0xc6u, 0xdbu, 0xfcu, 0xe1u,
    0x5au, 0x47u, 0x60u, 0x7du, 0x2eu, 0x33u, 0x14u, 0x09u,
    0x7fu, 0x62u, 0x45u, 0x58u, 0x0bu, 0x16u, 0x31u, 0x2cu,
    0x97u, 0x8au, 0xadu, 0xb0u, 0xe3u, 0xfeu, 0xd9u, 0xc4u
};

/****************************************************************************************************
* Function Impletement
****************************************************************************************************/

/****************************************************************************************************
* cc_algorithm_verify_crc_calc8()
****************************************************************************************************/
cc_result cc_algorithm_verify_crc_calc8(cc_uint8 *crc_value,cc_uint8 *data,cc_uint32 len,cc_uint8 startvalue,cc_boolean firstcall)
{
    cc_result result = CC_E_OK;
    cc_uint8 value;
    cc_uint32 i;

    do
    {
        /* check pointer */
        CHECK_PTR(result,crc_value);
        CHECK_PTR(result,data);
        CHECK_LOGIC(result,(len > 0));
        /* impletement */
        if(firstcall == CC_TRUE)
        {
            value = CC_ALGORITHM_VERIFY_CRC_INITIAL_VALUE8;
        }
        else
        {
            value = (CC_ALGORITHM_VERIFY_CRC_FINAL_XOR_CRC8 ^ startvalue);
        }
        for(i = 0;i < len;i++)
        {
            value = cc_algorithm_verify_crc_table8[value ^ data[i]];
        }
        /* output */
        *crc_value = value ^ CC_ALGORITHM_VERIFY_CRC_FINAL_XOR_CRC8;
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_verify_sum()
****************************************************************************************************/
cc_result cc_algorithm_verify_sum(cc_uint8 *value,cc_uint8 *data,cc_uint32 len)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,value);
        CHECK_PTR(result,data);
        CHECK_LOGIC(result,(len > 0));
        /* impletement */
        *value = 0;
        while(len--)
        {
            *value += *data++;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* cc_algorithm_verify_xor()
****************************************************************************************************/
cc_result cc_algorithm_verify_xor(cc_uint8 *value,cc_uint8 *data,cc_uint32 len)
{
    cc_result result = CC_E_OK;

    do
    {
        /* check pointer */
        CHECK_PTR(result,value);
        CHECK_PTR(result,data);
        CHECK_LOGIC(result,(len > 0));
        /* impletement */
        *value = 0;
        while(len--)
        {
            *value ^= *data++;
        }
    }while(0u);

    return result;
}

/****************************************************************************************************
* File cc_algorithm_verify.c End!
****************************************************************************************************/
