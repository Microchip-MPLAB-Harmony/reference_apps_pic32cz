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
/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ble.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_BLE_Initialize" and "APP_BLE_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_BLE_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_BLE_H
#define _APP_BLE_H

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
#define MAX_BUFFER_SIZE                 (100)
#define MULTILINK_NUM_DEVICES 2    
#define DEVICE_ADDR_SIZE 12
#define DEVICE_NAME_SIZE 31
#define DEFAULT_DEVICE_TEMP_VALUE_C 40
#define DEFAULT_DEVICE_TEMP_VALUE_F 104
#define NODE_1 0
#define NODE_2 1

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
    APP_BLE_STATE_INIT=0,
    APP_BLE_STATE_SERVICE_TASKS,
    APP_BLE_STATE_INIT_CONNCTION,
    APP_BLE_STATE_SCANNING,
    APP_BLE_STATE_NODE1_GATT_CLI_ENABLE,
    APP_BLE_STATE_NODE2_GATT_CLI_ENABLE,    
    APP_BLE_STATE_START_CONNECTION_NODE1,
    APP_BLE_STATE_START_CONNECTION_NODE2,    
    APP_BLE_STATE_FETCH_NODE1_TEMP,
    APP_BLE_STATE_FETCH_NODE2_TEMP,
    APP_BLE_STATE_SEND_TEMP_LIMIT_N1,
    APP_BLE_STATE_SEND_TEMP_LIMIT_N2,    
    APP_BLE_STATE_COMPLETE,
    APP_BLE_STATE_DISCONNECT,
    APP_BLE_STATE_ERROR,
    APP_BLE_STATE_WAIT,
    /* TODO: Define states used by the application state machine. */

} APP_BLE_STATES;



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
    APP_BLE_STATES state;

    /* TODO: Define any additional data used by the application. */

} APP_BLE_DATA;


typedef struct
{
    bool valid;
    char deviceAddress[DEVICE_ADDR_SIZE + 1];
    char deviceName[DEVICE_NAME_SIZE + 1];  
    uint8_t deviceName_hex_length;
    bool active;
    bool connected;
    char connHandleStr[5];
    char ctrlHandleStr[5];
    uint32_t tempSensorValue;
} APP_BLE_DEVICE;

typedef enum
{
    DEV1 = 0,
    DEV2 = 1,    
    DEVMAX,
} APP_BLE_DEVICE_ID;

extern APP_BLE_DATA app_bleData;
extern char statusBuffer[MAX_BUFFER_SIZE];
extern char sensorTemp1[5];
extern char sensorTemp2[5];
extern char temperatureSTRING[4];

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_BLE_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_BLE_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_BLE_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_BLE_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_BLE_Tasks ( void )

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
    APP_BLE_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_BLE_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_BLE_H */

/*******************************************************************************
 End of File
 */

