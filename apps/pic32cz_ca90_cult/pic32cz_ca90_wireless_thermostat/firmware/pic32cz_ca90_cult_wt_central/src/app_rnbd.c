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
/** MPLAB Harmony RNBD Function source File

  @Company
    Microchip Technology Inc.

  @File Name
    app_rnbd.c

  @Summary
    This file contains the implementation of functions for the RNBD BLE module operations.

  @Description
    This file provides the implementation for interacting with the RNBD BLE module, 
    including functionality for GATT client configuration, remote characteristic read/write, 
    and BLE node connection management.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */


#include "rnbd/rnbd.h"
#include<string.h>
#include<stdio.h>
#include "rnbd/rnbd_interface.h"
#include "app_rnbd.h"
#include "app_ble.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
#define RESPONSE_TIMEOUT       1000

uint32_t ResponseTime=0; 
char dataReceived[400];
static char cmdBuf[MAX_BUFFER_SIZE];    
static char responseBuf[MAX_BUFFER_SIZE]={0};
extern char statusBuffer[];
extern APP_BLE_DEVICE multiLinkDemoDevices[MULTILINK_NUM_DEVICES];

/*Function that reads the remote characteristic from GATT client*/
bool RNBD_ReadremoteCharacteristic(uint8_t nodeIndex,const char *handle, uint8_t handleLen, char *data, uint8_t dataLen)
{
    char dataReceived[11];  
    uint8_t i=0;
    char *str;
    
    /*Initialize dataReceived with null terminator*/
    memset(dataReceived, 0, sizeof(dataReceived));
    
    /*Send Read Remote characteristic command*/
    sprintf(cmdBuf, "CHR,%s,%s\r", handle, multiLinkDemoDevices[nodeIndex].connHandleStr);
    RNBD_SendCmd(cmdBuf, strlen(cmdBuf));
    RNBD.DelayMs(600);    

    /*Read data*/
    while (RNBD.DataReady()){
        dataReceived[i] = RNBD.Read();
        i++;
        RNBD.DelayMs(20);
    }

    // Null-terminate the dataReceived
    dataReceived[i] = '\0';

    /* Search for the CMD> string*/
    str = strstr(dataReceived,"CMD>");
    
        if (i >= 2) {
            if(nodeIndex==NODE_1)
            {
                data[0]='T';
                data[1]='1';
            }
            else if(nodeIndex==NODE_2)
            {
                data[0]='T';
                data[1]='2';
            }
            data[2] = dataReceived[0];
            data[3] = dataReceived[1];
            
            return true;
        }
    
    return false;
}


/*Function that writes the remote characteristic to GATT client*/
bool RNBD_WriteremoteCharacteristic(uint8_t nodeIndex,const char *handle, uint8_t handleLen, char *data)
{
    const char cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};      
    sprintf(cmdBuf, "CHWM,%s,%s,%s\r", multiLinkDemoDevices[nodeIndex].connHandleStr,handle,data);
    RNBD_SendCmd(cmdBuf, strlen(cmdBuf));
    RNBD.DelayMs(600);   
    return RNBD_ReadMsg(cmdPrompt, (uint8_t)sizeof (cmdPrompt));
}
  
 /*Function that enables GATT client*/
bool RNBD_Set_GATTClient(uint8_t nodeIndex)
{
    const char cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
    sprintf((char *) cmdBuf, "CI,%s\r",multiLinkDemoDevices[nodeIndex].connHandleStr);
    RNBD_SendCmd(cmdBuf, strlen(cmdBuf));
    RNBD.DelayMs(300);
    return RNBD_ReadMsg(cmdPrompt, (uint8_t)sizeof (cmdPrompt));
    
}


/*Function that scans for BLE nodes based on device name filtering*/
bool scan_Node1(char * devAdd,char * devName)
{
    const char cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '}; 
    
    static uint8_t i=0,j=0;
    char *str;    
    sprintf(cmdBuf,"FE,01E0,FFFF,01,01,%s\r",devName);
    RNBD_SendCmd(cmdBuf, strlen(cmdBuf));
    RNBD.DelayMs(2000);
       
    /*Read data*/
    while (RNBD.DataReady()){
        dataReceived[i] = RNBD.Read();
        i++;
    }        
    for(i=0;dataReceived[i]!='%';i++)
    {
    }
    for(i=i+1;dataReceived[i]!=',';i++,j++)
    {
       devAdd[j]=dataReceived[i];
    }
    
    sprintf(cmdBuf,"X\r");
    RNBD_SendCmd(cmdBuf, strlen(cmdBuf));
    RNBD.DelayMs(500);
    return RNBD_ReadMsg(cmdPrompt, (uint8_t)sizeof (cmdPrompt));    
}

/*Function that connects to BLE node 1*/
void Connect_Node1(char* devAddr)
{   
    static uint8_t responseBufcount=0;
    static uint8_t statusBuffercount=0;    
    char *str;     
    
    sprintf(cmdBuf,"C,0,%s\r",devAddr);
    
    RNBD_SendCmd(cmdBuf, 17U);
    
    //Wait for the response time
    while(!RNBD.DataReady() || ResponseTime<=RESPONSE_TIMEOUT)
    {
        RNBD.DelayMs(1);
        ResponseTime++;
    }    
    
    ResponseTime=0;   
    
    while(!RNBD_IsStreamopen()){  //Check if stream is open
        while(RNBD.DataReady()){
            RNBD_DataReady(); //Read the Connect response into a local buffer
            if(statusBuffer[statusBuffercount]=='\0')
            {
                statusBuffercount=0;
                for(int i=0;i<=statusBuffercount;i++)
                    statusBuffer[i]='\0';
            }
            else if(statusBuffer[statusBuffercount]!='\0')
            {
                memcpy(&responseBuf[responseBufcount],&statusBuffer[statusBuffercount],1);  
                responseBufcount++;
                statusBuffercount++;
            }        
        }          
    }
    
    str=strstr(responseBuf,"PHY_UPDATED");
    strncpy(multiLinkDemoDevices[NODE_1].connHandleStr,&str[12],4);
    str=strstr(str,"NOTI");
    strncpy(multiLinkDemoDevices[NODE_1].ctrlHandleStr,&str[5],4);
    memcpy(responseBuf,0,sizeof(responseBuf));
    RNBD.DelayMs(1);             
}

/*Function that helps to connect multi-links*/
void Connect_Node2(char* devAddr)
{
    static uint8_t responseBufcount=0;
    static uint8_t statusBuffercount=0;    
    char *str;
    
    sprintf(cmdBuf,"C,0,%s\r",devAddr);    

    RNBD_SendCmd(cmdBuf, 17U);
    
    while(!RNBD.DataReady() || ResponseTime<=RESPONSE_TIMEOUT)
    {
        RNBD.DelayMs(1);
        ResponseTime++;
    } 
    
    ResponseTime=0;   
    
    while(RNBD.DataReady()){        
        RNBD_DataReady(); //Read the Connect response into a local buffer
        if(statusBuffer[statusBuffercount]=='\0')
        {
            for(int i=0;i<=statusBuffercount;i++)
                    statusBuffer[i]='\0';
            statusBuffercount=0;
                    
        }
        else if(statusBuffer[statusBuffercount]!='\0')
        {
            memcpy(&responseBuf[responseBufcount],&statusBuffer[statusBuffercount],1);  
            responseBufcount++;
            statusBuffercount++;
        }        
    }          
    str=strstr(responseBuf,"PHY_UPDATED");
    strncpy(multiLinkDemoDevices[NODE_2].connHandleStr,&str[12],4);
    str=strstr(str,"NOTI");    
    strncpy(multiLinkDemoDevices[NODE_2].ctrlHandleStr,&str[5],4);
    RNBD.DelayMs(1);     
    
}

/* *****************************************************************************
 End of File
 */
