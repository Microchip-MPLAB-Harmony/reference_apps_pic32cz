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
  MPLAB Harmony Application Set limit Screen Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_screen3_setlimit.h

  Summary:
    This header file provides prototypes and definitions of the set limit screen of the demo.

  Description:
    This header file includes function prototypes and data type definitions for the set limit screen.
    They are mainly used internally by the application for maintaining the state machine of the set limit screen.
*******************************************************************************/

#ifndef _APP_SCREEN3_SETLIMIT_H
#define _APP_SCREEN3_SETLIMIT_H

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
    ML_SETLIMIT_INIT,
    ML_SETLIMIT_ANIM0,
    ML_SETLIMIT_ANIM1,    
    ML_SETLIMIT_ANIM_DONE,
    ML_SETLIMIT_TEMP_UPDATE,
    ML_SETLIMIT_TEMP1_SCREEN_WRITE,
    ML_SETLIMIT_TEMP2_SCREEN_WRITE,
    ML_SETLIMIT_FEEDBACK_NODE1,
    ML_SETLIMIT_FEEDBACK_NODE2,
    ML_SETLIMIT_WAIT,    
} ML_SETLIMIT_SCREEN_STATE;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

void getLimit(uint8_t * CutOff,uint8_t nodeidx);
static void MLSetlimitAnimTimer_Callback (uintptr_t context);
static void MLSetLimit_InitDeviceTable(void);
static void MLSetLimit_UpdateTemperature(uint8_t val,uint8_t node);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_SCREEN3_SETLIMIT_H */

/*******************************************************************************
 End of File
 */

