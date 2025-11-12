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
/*******************************************************************************
  MPLAB Harmony Application Connect Screen Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_screen1_connect.h

  Summary:
    This header file provides prototypes and definitions for the connect screen of the demo.

  Description:
    This header file includes function prototypes and data type definitions for the connect screen.
    They are mainly used internally by the application for maintaining the state machine of the connect screen.
     
*******************************************************************************/

#ifndef _APP_SCREEN1_CONNECT_H
#define _APP_SCREEN1_CONNECT_H

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
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    ML_CONNECT_INIT,
    ML_CONNECT_ANIM0,
    ML_CONNECT_ANIM1,    
    ML_CONNECT_ANIM_DONE,
    ML_CONNECT_START_SCANNING,
    ML_CONNECT_START_CONNECT,
    ML_CONNECT_CONNECTING,
    ML_CONNECT_DEVICE_CONNECTED,
    ML_CONNECT_DEVICE_INACTIVE,
    ML_CONNECT_DEVICE_FAILED,
    ML_CONNECT_FAILED,
    ML_CONNECT_CONNECTED_INIT,
    ML_CONNECT_CONNECTED_INIT_DONE,
    ML_CONNECT_CONNECTED_READY,
    ML_CONNECT_CONNECTED_EXIT,
    ML_CONNECT_MAX_STATES,
    ML_CONNECT_WAIT,
} ML_CONNECT_SCREEN_STATE;

extern ML_CONNECT_SCREEN_STATE appScreenMLConnectState;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************
static void MLConnectAnimTimer_Callback (uintptr_t context);
static void MLConnectProgressTimer_Callback (uintptr_t context);
static void MLConnect_InitDeviceTable(void);
static void MLConnect_UpdateStatusString(char * str);


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_SCREEN1_CONNECT_H */

/*******************************************************************************
 End of File
 */

