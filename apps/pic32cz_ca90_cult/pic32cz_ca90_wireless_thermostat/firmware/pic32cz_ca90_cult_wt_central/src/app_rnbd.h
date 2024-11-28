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
/** MPLAB Harmony RNBD Function Header File

  @Company
    Microchip Technology Inc.

  @File Name
    app_rnbd.h

  @Summary
    This header file contains function declarations for RNBD BLE module operations.

  @Description
    This file provides the interface for interacting with the RNBD BLE module, including 
    functionality for GATT client configuration, remote characteristic read/write, 
    and BLE node connection management.
 */
/* ************************************************************************** */

#ifndef _APP_RNBD_H
#define _APP_RNBD_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END
    
// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

bool RNBD_ReadremoteCharacteristic(uint8_t nodeIndex,const char *handle, uint8_t handleLen, char *data, uint8_t dataLen);

bool RNBD_WriteremoteCharacteristic(uint8_t nodeIndex,const char *handle, uint8_t handleLen, char *data);
  
bool RNBD_Set_GATTClient(uint8_t nodeIndex);

bool scan_Node1(char * devAdd,char * devName);

void Connect_Node1(char* devAddr);

void Connect_Node2(char* devAddr);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_RNBD_H */

/*******************************************************************************
 End of File
 */

