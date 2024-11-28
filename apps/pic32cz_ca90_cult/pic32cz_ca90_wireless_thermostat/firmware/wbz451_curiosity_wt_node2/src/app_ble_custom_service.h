// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END
/*******************************************************************************
  Application BLE Sensor Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ble_custom_service.h

  Summary:
    This header file contains the Application ble custom service data type definitions 
    and prototypes for this project.

  Description:
    This file contains the Application ble custom Service prototypes and data types
    for this project.The implementation of demo mode is included in this file.
 *******************************************************************************/

#ifndef APP_BLE_CS_H
#define APP_BLE_CS_H

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
enum APP_CUSTOM_SERVICE_STATUS_CODE_T
{
    SUCCESS = 0x00,    
    INVALID_PARAMETER = 0x02,
    OPERATION_FAILED = 0x03
};

enum APP_RGB_LED_STATUS_T
{
    LED_OFF = 0x00,
    LED_ON = 0x01,
};

extern uint16_t G_ConnHandle;
extern uint8_t tempInCelsius;
// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

uint8_t APP_CustomService_TempLimit_Handler(uint8_t *);
void APP_CustomService_TempCtrl_Callback(uint8_t * context);

#endif
