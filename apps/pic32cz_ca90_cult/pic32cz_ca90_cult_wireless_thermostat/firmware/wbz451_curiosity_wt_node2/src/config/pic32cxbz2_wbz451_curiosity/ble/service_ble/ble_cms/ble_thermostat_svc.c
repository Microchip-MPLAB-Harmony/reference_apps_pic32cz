/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  BLE Thermostat Service Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ble_thermostat_svc.c

  Summary:
    This file contains the BLE Thermostat Service functions for application user.

  Description:
    This file contains the BLE Thermostat Service functions for application user.
 *******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stddef.h>
#include "gatt.h"
#include "ble_util/byte_stream.h"
#include "ble_cms/ble_thermostat_svc.h"


// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
/* Little Endian. */
#define UUID_THERMOSTAT_PRIMARY_SVC_LE         0xea, 0xce, 0xf4, 0xac, 0x1f, 0x88, 0xf8, 0xae, 0xd0, 0x42, 0x55, 0x52, 0x50, 0x48, 0x43, 0x4d    /* Service UUID */

#define UUID_THERMOSTAT_CHARACTERISTIC_0_LE         0xea, 0xce, 0xf4, 0xbc, 0x1f, 0x88, 0xf8, 0xae, 0xd0, 0x42, 0x55, 0x52, 0x50, 0x48, 0x43, 0x4d    /* Characteristic 0 UUID */
#define UUID_THERMOSTAT_CHARACTERISTIC_1_LE         0xea, 0xce, 0xf4, 0xcc, 0x1f, 0x88, 0xf8, 0xae, 0xd0, 0x42, 0x55, 0x52, 0x50, 0x48, 0x43, 0x4d    /* Characteristic 1 UUID */

// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

/* Primary Service Declaration */
static const uint8_t s_thermostatSvcUuid[] = {UUID_THERMOSTAT_PRIMARY_SVC_LE};
static const uint16_t s_thermostatSvcUuidLen = sizeof(s_thermostatSvcUuid);

/* Thermostat Characteristic 0 Characteristic */
static const uint8_t s_thermostatChar0[] = {ATT_PROP_READ|ATT_PROP_NOTIFY, UINT16_TO_BYTES(THERMOSTAT_HDL_CHARVAL_0), UUID_THERMOSTAT_CHARACTERISTIC_0_LE};    /* Read */ /* Notify */
static const uint16_t s_thermostatChar0Len = sizeof(s_thermostatChar0);

/* Thermostat Characteristic 0 Characteristic Value */
static const uint8_t s_thermostatUuidChar0[] = {UUID_THERMOSTAT_CHARACTERISTIC_0_LE};
static uint8_t s_thermostatChar0Val[] = {0x00, 0x00};    /* Default Value */
static uint16_t s_thermostatChar0ValLen = sizeof(s_thermostatChar0Val);

/* Thermostat Characteristic 0 Client Characteristic Configuration Descriptor */
static uint8_t s_thermostatCccChar0[] = {UINT16_TO_BYTES(0x0000)};
static const uint16_t s_thermostatCccChar0Len = sizeof(s_thermostatCccChar0);

/* Thermostat Characteristic 1 Characteristic */
static const uint8_t s_thermostatChar1[] = {ATT_PROP_READ|ATT_PROP_WRITE_CMD|ATT_PROP_WRITE_REQ, UINT16_TO_BYTES(THERMOSTAT_HDL_CHARVAL_1), UUID_THERMOSTAT_CHARACTERISTIC_1_LE};    /* Read */ /* Write without response */ /* Write with response */
static const uint16_t s_thermostatChar1Len = sizeof(s_thermostatChar1);

/* Thermostat Characteristic 1 Characteristic Value */
static const uint8_t s_thermostatUuidChar1[] = {UUID_THERMOSTAT_CHARACTERISTIC_1_LE};
static uint8_t s_thermostatChar1Val[2] = {0x00, 0x00};    /* Default Value */
static uint16_t s_thermostatChar1ValLen = sizeof(s_thermostatChar1Val);

/* Attribute list for Thermostat service */
static GATTS_Attribute_T s_thermostatList[] = {
    /* Service Declaration */
    {
        (uint8_t *) g_gattUuidPrimSvc,
        (uint8_t *) s_thermostatSvcUuid,
        (uint16_t *) & s_thermostatSvcUuidLen,
        sizeof (s_thermostatSvcUuid),
        0,
        PERMISSION_READ
    },
    /* Characteristic 0 Declaration */
    {
        (uint8_t *) g_gattUuidChar,
        (uint8_t *) s_thermostatChar0,
        (uint16_t *) & s_thermostatChar0Len,
        sizeof (s_thermostatChar0),
        0,
        PERMISSION_READ
    },
    /* Characteristic 0 Value */
    {
        (uint8_t *) s_thermostatUuidChar0,
        (uint8_t *) s_thermostatChar0Val,
        (uint16_t *) & s_thermostatChar0ValLen,
        sizeof(s_thermostatChar0Val),
        SETTING_MANUAL_READ_RSP|SETTING_UUID_16,    /* Manual Read Response */
        PERMISSION_READ    
    },
    /* Client Characteristic Configuration Descriptor */
    {
        (uint8_t *) g_descUuidCcc,
        (uint8_t *) s_thermostatCccChar0,
        (uint16_t *) & s_thermostatCccChar0Len,
        sizeof (s_thermostatCccChar0),
        SETTING_CCCD,    
        PERMISSION_READ|PERMISSION_WRITE    
    },
    /* Characteristic 1 Declaration */
    {
        (uint8_t *) g_gattUuidChar,
        (uint8_t *) s_thermostatChar1,
        (uint16_t *) & s_thermostatChar1Len,
        sizeof (s_thermostatChar1),
        0,
        PERMISSION_READ
    },
    /* Characteristic 1 Value */
    {
        (uint8_t *) s_thermostatUuidChar1,
        (uint8_t *) s_thermostatChar1Val,
        (uint16_t *) & s_thermostatChar1ValLen,
        sizeof(s_thermostatChar1Val),
        SETTING_MANUAL_READ_RSP|SETTING_MANUAL_WRITE_RSP|SETTING_UUID_16,    /* Manual Read Response */ /* Manual Write Response */
        PERMISSION_READ|PERMISSION_WRITE    
    },
};

static const GATTS_CccdSetting_T s_thermostatCccdSetting[] = 
{
    {THERMOSTAT_HDL_CCCD_0, NOTIFICATION},
};

/* Thermostat Service structure */
static GATTS_Service_T s_thermostatSvc = 
{
    NULL,
    (GATTS_Attribute_T *) s_thermostatList,
    (GATTS_CccdSetting_T const *)s_thermostatCccdSetting,
    THERMOSTAT_START_HDL,
    THERMOSTAT_END_HDL,
    1
};

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

uint16_t BLE_THERMOSTAT_Add(void)
{
    return GATTS_AddService(&s_thermostatSvc, (THERMOSTAT_END_HDL - THERMOSTAT_START_HDL + 1));
}
