//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END
/*******************************************************************************
  Application BLE Custom Service Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ble_custom_service.c

  Summary:
    This file contains the Application Transparent Server Role functions for this project.

  Description:
    This file contains the Application Transparent Server Role functions for this project.
    The implementation of demo mode is included in this file.
 *******************************************************************************/
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include "app.h"
#include "app_ble_handler.h"
#include "app_ble_custom_service.h"
#include "ble/service_ble/ble_cms/ble_thermostat_svc.h"
#include "bsp/bsp.h"
#include "system/console/sys_console.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

/**@brief BLE temperature Limit*/
char tempLimitRecv[5]={0};
uint8_t tempInCelsius;
// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

/*Function that converts Temperature from string to integer format*/
uint8_t stringToTemperatureInt(char* temperature)
{    
    tempInCelsius =((temperature[0]-'0')*10)+(temperature[1]-'0');
    return tempInCelsius;    
}

/* BLE Custom Service Temperature control through Central Node */
uint8_t  APP_CustomService_TempLimit_Handler(uint8_t *p_cmd)
{    
    tempLimitRecv[0]=p_cmd[0];
    tempLimitRecv[1]=p_cmd[1];
    tempLimitRecv[2]=p_cmd[2];
    tempLimitRecv[3]=p_cmd[3];   

    stringToTemperatureInt(tempLimitRecv);
    
    SYS_CONSOLE_PRINT("[BLE] Limit Set : %d C\r\n",tempInCelsius);
    
    if(Temperature>=tempInCelsius)
        RGB_LED_RED_On();
    else
        RGB_LED_RED_Off();
    return SUCCESS;
}

/* Callback for BLE Custom Service RGB LED on/off */
void APP_CustomService_TempCtrl_Callback(uint8_t * context)
{
    APP_Msg_T appMsg;
    appMsg.msgId = APP_MSG_BLE_LIMIT_SET_EVENT;
    memcpy(appMsg.msgData, context, 4);
    OSAL_QUEUE_Send(&appData.appQueue, &appMsg,0);
}








