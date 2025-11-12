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
  MPLAB Harmony Application Temperature Monitor Screen Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_screen2_monitor.h

  Summary:
    This header file provides prototypes and definitions for the monitor screen of the demo.

  Description:
    This header file includes function prototypes and data type definitions for the monitor screen.
    They are mainly used internally by the application for maintaining the state machine of the monitor screen.
*******************************************************************************/

#ifndef _APP_SCREEN2_MONITOR_H
#define _APP_SCREEN2_MONITOR_H

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
    ML_MONITOR_INIT,
    ML_MONITOR_ANIM0,
    ML_MONITOR_ANIM1,    
    ML_MONITOR_ANIM_DONE,
    ML_MONITOR_TEMP_UPDATE,
    ML_MONITOR_TEMP1_SCREEN_WRITE,
    ML_MONITOR_TEMP2_SCREEN_WRITE,
    ML_MONITOR_WAIT,
    ML_SET_LIMIT,

} ML_MONITOR_SCREEN_STATE;

extern ML_MONITOR_SCREEN_STATE appScreenMLMonitorState;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

static void MLMonitorAnimTimer_Callback (uintptr_t context);
static void MLUpdateTimer_Callback (uintptr_t context);
static void MLMonitor_InitDeviceTable(void);
static void MLMonitor_UpdateStatusString(char * str,uint8_t node);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_SCREEN2_MONITOR_H */

/*******************************************************************************
 End of File
 */

