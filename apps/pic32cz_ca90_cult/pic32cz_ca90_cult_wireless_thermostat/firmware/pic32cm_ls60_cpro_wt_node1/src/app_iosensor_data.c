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
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_sensor_read.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdio.h>
#include "app_iosensor_data.h"
#include "definitions.h"
#include "app_ble.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
#define TEMP_SENSOR_SLAVE_ADDR                  0x004F
#define TEMP_SENSOR_REG_ADDR                    0x00

static volatile bool isI2CFree = true;
static volatile bool isTemperatureRead = false;
uint8_t temperatureVal=0;
uint8_t temperaturePrevVal=0;
volatile bool temperatureStatus = false;
static uint8_t i2cAddress;
static uint8_t i2cWrData = TEMP_SENSOR_REG_ADDR;
static uint8_t i2cRdData[2] = {0};
uint8_t counter;
uint16_t adc_val;
extern APP_BLE_DATA app_bleData;
unsigned int error_status;
extern volatile bool cmdMode;

void ReadSensorValue(void);
static uint8_t getTemperature(uint8_t* rawTempValue);
static void i2cEventHandler(uintptr_t contextHandle);
static uint8_t getTemperature(uint8_t* rawTempValue);

/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_SENSOR_READ_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_IOSENSOR_DATA_DATA app_sensor_readData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/
void APP_Tasks_CB (uintptr_t context)
{
    ReadSensorValue();
}

static void i2cEventHandler(uintptr_t contextHandle)
{
    if ((error_status = SERCOM5_I2C_ErrorGet()) == SERCOM_I2C_ERROR_NONE)
    {
        if(i2cAddress == TEMP_SENSOR_SLAVE_ADDR)
        {
            isTemperatureRead       = true;
        }
        
        isI2CFree                   = true;
    }
    
    else
        printf("\r\nError :0x%x",error_status);
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/
static uint8_t getTemperature(uint8_t* rawTempValue)
{
    int16_t temp;
    // Convert the temperature value read from sensor to readable format (Degree Celsius)
    // For demonstration purpose, temperature value is assumed to be positive.
    // The maximum positive temperature measured by sensor is +125 C
    temp = (rawTempValue[0] << 8) | rawTempValue[1];
    temp = (temp >> 7) * 0.5;
    temp = (temp * 9/5) + 32;
    return (uint8_t)temp;
}

void ReadSensorValue(void)
{
    /*Temperature Reading from Sensor*/
    if ((isI2CFree == true))   
    {
        isI2CFree = false;
        i2cAddress = TEMP_SENSOR_SLAVE_ADDR;
        SERCOM5_I2C_Read(TEMP_SENSOR_SLAVE_ADDR, i2cRdData, 2);
        temperatureVal = getTemperature(i2cRdData);        
        temperatureStatus = true;
    }   
    
    /*Light sensor value from ADC*/
    adc_val = ADC_ConversionResultGet();
 
    
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_SENSOR_READ_Initialize ( void )

  Remarks:
    See prototype in app_sensor_read.h.
 */

void APP_IOSENSOR_DATA_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_sensor_readData.state = APP_IOSENSOR_DATA_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_SENSOR_READ_Tasks ( void )

  Remarks:
    See prototype in app_sensor_read.h.
 */

void APP_IOSENSOR_DATA_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_sensor_readData.state )
    {
        /* Application's initial state. */
        case APP_IOSENSOR_DATA_STATE_INIT:
        {
            bool appInitialized = true;

            if (appInitialized)
            {
                SERCOM5_I2C_CallbackRegister(i2cEventHandler, 0);
                
                SERCOM5_I2C_WriteRead(TEMP_SENSOR_SLAVE_ADDR, &i2cWrData, 1, i2cRdData, 2);               
                
                SYS_TIME_CallbackRegisterMS (APP_Tasks_CB, 0, 3000, SYS_TIME_PERIODIC );
                
                ADC_Enable();
                
                ADC_ConversionStart();               
                
                app_sensor_readData.state = APP_IOSENSOR_DATA_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_IOSENSOR_DATA_STATE_SERVICE_TASKS:
        {
            if(cmdMode==true)
            {
                if(temperaturePrevVal!=temperatureVal)
                {
                    temperaturePrevVal=temperatureVal;
                    app_bleData.state = APP_BLE_STATE_TEMP_LOCAL_UPDATE;
                }
                
                else
                    app_bleData.state = APP_BLE_STATE_THRESHOLD_CHANGE;
            }
            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
