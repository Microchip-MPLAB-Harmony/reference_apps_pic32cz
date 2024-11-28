/*******************************************************************************
Copyright (C) 2024 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
/* ************************************************************************** */
/** MPLAB RNBD service management header file

  Company:
    Microchip Technology Inc.

  File Name:
    ble_helper.h

  Summary:
    This header file provides the declarations for RNBD BLE service and characteristic 
    management functions.

  Description:
    This header file declares the APIs for configuring and managing BLE services 
    and characteristics using the RNBD module. It includes declarations for setting 
    service characteristics, defining service UUIDs, and performing read/write 
    operations on local characteristics. Additionally, it declares utility functions 
    for resetting the RNBD module to factory settings and rebooting the module.

    These APIs are intended to be implemented in a corresponding source file and 
    provide a convenient interface for BLE service management within the application.
 *******************************************************************************/

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
 // *****************************************************************************
 // *****************************************************************************
 // Section: Interface Functions
 // *****************************************************************************
 // *****************************************************************************

bool RNBD_SetServiceCharacteristic(const char *service, uint8_t serviceLen);
bool RNBD_SetServiceUUID(const char *uuid, uint8_t uuidLen);
bool RNBD_ReadLocalCharacteristic(const char *handle, uint8_t handleLen, char *data, uint8_t dataLen);
bool RNBD_WriteLocalCharacteristic(const char *handle, uint8_t handleLen, const char *data, uint8_t dataLen);
bool RNBD_SF2_FactoryReset(void); 
bool RNBD_Reboot(void);
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

/* *****************************************************************************
 End of File
 */
