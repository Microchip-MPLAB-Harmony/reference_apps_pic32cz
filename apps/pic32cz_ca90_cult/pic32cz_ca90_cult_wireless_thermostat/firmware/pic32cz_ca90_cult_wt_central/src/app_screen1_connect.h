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
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_screen1_connect.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_SCREEN1_CONNECT_Initialize" and "APP_SCREEN1_CONNECT_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_SCREEN1_CONNECT_STATES" definition).  Both
    are defined here for convenience.
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
    /* Application's state machine's initial state. */
    APP_SCREEN1_CONNECT_STATE_INIT=0,
    APP_SCREEN1_CONNECT_STATE_SERVICE_TASKS,
    /* TODO: Define states used by the application state machine. */

} APP_SCREEN1_CONNECT_STATES;

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

ML_CONNECT_SCREEN_STATE appScreenMLConnectState;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_SCREEN1_CONNECT_STATES state;

    /* TODO: Define any additional data used by the application. */

} APP_SCREEN1_CONNECT_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_SCREEN1_CONNECT_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_SCREEN1_CONNECT_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_SCREEN1_CONNECT_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_SCREEN1_CONNECT_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_SCREEN1_CONNECT_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_SCREEN1_CONNECT_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_SCREEN1_CONNECT_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_SCREEN1_CONNECT_H */

/*******************************************************************************
 End of File
 */

