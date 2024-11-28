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
    ble_helper.c

  Summary:
    This file contains the implementation of RNBD BLE service and characteristic 
    management functions.

  Description:
    This source file provides the implementation for configuring and managing 
    BLE services and characteristics using the RNBD module. It includes functions 
    for setting service characteristics, defining service UUIDs, and performing 
    read/write operations on local characteristics. Additionally, utility functions 
    for resetting the RNBD module to factory settings and rebooting the module are 
    implemented here.

    These functions interact with the RNBD module at a low level to facilitate 
    BLE service management within the application. They enable the configuration 
    of service characteristics, communication with the BLE module, and provide 
    critical operations for module management.
 *******************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "rnbd/rnbd.h"
#include "rnbd/rnbd_interface.h"
#include "definitions.h" 
#include "ble_helper.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

static char cmdBuf[64];

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*Function used to set the Custom Service Characteristic for temperature*/
bool RNBD_SetServiceCharacteristic(const char *service, uint8_t serviceLen)
{
	const char cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
    uint8_t index;
            
    cmdBuf[0] = 'P';
    cmdBuf[1] = 'C';
    cmdBuf[2] = ',';
        
    for (index = 0; index < serviceLen; index++)
    {
        cmdBuf[3U + index] = service[index];
    }
    index = index + 3U;
    cmdBuf[index++] = '\r';
    cmdBuf[index] = '\n';
    
    RNBD_SendCmd(cmdBuf, index);
    RNBD.DelayMs(1000);
    return RNBD_ReadMsg(cmdPrompt, (uint8_t)sizeof (cmdPrompt));	
}

/*Function used to set the Custom Service UUID for temperature*/
bool RNBD_SetServiceUUID(const char *uuid, uint8_t uuidLen)
{
	const char cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
    uint8_t index;
            
    cmdBuf[0] = 'P';
    cmdBuf[1] = 'S';
    cmdBuf[2] = ',';
        
    for (index = 0; index < uuidLen; index++)
    {
        cmdBuf[3U + index] = uuid[index];
    }
    index = index + 3U;
    cmdBuf[index++] = '\r';
    cmdBuf[index] = '\n';
    RNBD_SendCmd(cmdBuf, index);
    RNBD.DelayMs(1000);
    return RNBD_ReadMsg(cmdPrompt, (uint8_t)sizeof (cmdPrompt));	
}

/*Function used to read the local characteristic value of a GATT sever*/
bool RNBD_ReadLocalCharacteristic(const char *handle, uint8_t handleLen, char *data, uint8_t dataLen)
{	
    uint8_t index;
    uint8_t i=0;
    
    cmdBuf[0] = 'S';
    cmdBuf[1] = 'H';
    cmdBuf[2] = 'R';
    cmdBuf[3] = ',';
        
    for (i= 0; i< handleLen; i++)
    {
        cmdBuf[4U+ i] = handle[i];
    }
    
    index = handleLen + 4U;  
    cmdBuf[index] = '\r';    
    RNBD_SendCmd(cmdBuf, index+1);
    RNBD.DelayMs(300); 
    i=0;
    while(RNBD.DataReady())
    {       
        data[i]=RNBD.Read();            
        i++;         
    }   
    return true;
}

/*Function used to write the local characteristic value of a GATT sever*/
bool RNBD_WriteLocalCharacteristic(const char *handle, uint8_t handleLen, const char *data, uint8_t dataLen)
{
	const char cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
    uint8_t index;
    uint8_t i=0;
            
    cmdBuf[0] = 'S';
    cmdBuf[1] = 'H';
    cmdBuf[2] = 'W';
    cmdBuf[3] = ',';
    
    for (i= 0; i< handleLen; i++)
    {
        cmdBuf[4U+ i] = handle[i];
    }
    index = handleLen + 4U;
    
    if (dataLen != 0)
    {
        cmdBuf[index++] = ',';  
        for (i = 0; i < dataLen; i++)
        {
            cmdBuf[i + index ] = data[i];
        } 
        
    }
    index= dataLen + index;
    cmdBuf[index] = '\r';    
    RNBD_SendCmd(cmdBuf, index+1);
    RNBD.DelayMs(500);
    return RNBD_ReadMsg(cmdPrompt, (uint8_t)sizeof (cmdPrompt));
}	


bool RNBD_SF2_FactoryReset()
{
	bool FactoryResetStatus = false;
    const char reboot[] = {'R', 'e', 'b', 'o', 'o', 't', ' ', 'a', 'f', 't', 'e', 'r', ' ', 'F', 'a', 'c', 't', 'o', 'r', 'y', ' ', 'R', 'e', 's', 'e', 't', '\r', '\n'};
    cmdBuf[0] = 'S';
    cmdBuf[1] = 'F';
    cmdBuf[2] = ',';
    cmdBuf[3] = '2';
    cmdBuf[4] = '\r';
    cmdBuf[5] = '\n';
    FactoryResetStatus = RNBD_SendCommand_ReceiveResponse(cmdBuf, 6U, reboot, 28U);

	RNBD.DelayMs(250);

	return FactoryResetStatus;
}


bool RNBD_Reboot(void)
{
	bool RebootStatus = false;
    const char rebootResponse[] = {'R', 'e', 'b', 'o', 'o', 't', 'i', 'n', 'g', '\r', '\n'};
	cmdBuf[0] = 'R';
    cmdBuf[1] = ',';
    cmdBuf[2] = '1';
    cmdBuf[3] = '\r';
    cmdBuf[4] = '\n';

    RebootStatus = RNBD_SendCommand_ReceiveResponse(cmdBuf, 5U, rebootResponse, 11U);

	RNBD.DelayMs(250);

	return RebootStatus;
}

/* *****************************************************************************
 End of File
 */
