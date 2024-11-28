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
    app_ble.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's BLE state machine and it may call
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
#include <string.h>
#include "definitions.h"
#include "app_ble.h"
#include "rnbd/rnbd_interface.h"
#include "rnbd/rnbd.h"
#include "ble_helper.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

#define MAX_BUFFER_SIZE                 (80)
#define MAX_DEV_NAME_SIZE               (25)
#define RESPONSE_TIMEOUT 1000 

uint32_t ResponseTime=0;
char *str;
volatile bool cmdStat=false;
volatile bool cmdMode=false;
uint8_t dummyread;
char connHandleStr[5];

char responseBuf[130]={0};
static uint8_t responseBufcount=0;
static uint8_t statusBuffercount=0; 

/**< Status Buffer instance passed to RNBD drive used for Asynchronous Message Handling (see *asyncBuffer in rnbd.c) */
char statusBuffer[MAX_BUFFER_SIZE];   

char temperatureString[3];
char temperatureThreshold[10]={0};
uint8_t tempLimit=0;
volatile bool status;
int temperatureCel;     
char BleDevName[MAX_DEV_NAME_SIZE]="N1";
char tempBuf[2];


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_BLE_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */
/** MACRO used to configure the application used buffer sizes.
 *  This is used by the application for communication buffers.
 */
APP_BLE_DATA app_bleData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/*Function to convert Temperature in (F) to character bytes*/
void temperature_conversion(uint8_t temperatureVal,char* temperatureString){
    if(temperatureVal>99)
    {
        printf("\r\nInvalid Temperature\r\n"); 
        return;
    }
    temperatureCel= (int)((5.0/9.0)*(temperatureVal-32));
    temperatureString[0]=temperatureCel/10+'0';
    temperatureString[1]=temperatureCel%10+'0';  
    printf("\r\nTemp :%d C",temperatureCel);
    return;
}

/*Function to convert character bytes into integer*/
void char_to_int(char *temperatureThreshold,uint8_t *tempLimit)
{   
    tempBuf[0]=((temperatureThreshold[0]-'0')<<4)|(temperatureThreshold[1]-'0');
    tempBuf[1]=((temperatureThreshold[2]-'0')<<4)|(temperatureThreshold[3]-'0');
    *tempLimit= (((uint8_t)(tempBuf[0]-'0')*10) + ((uint8_t)(tempBuf[1]-'0')));
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_BLE_Initialize ( void )

  Remarks:
    See prototype in app_ble.h.
 */
void APP_BLE_Initialize(void) {
    /* Place the App state machine in its initial state. */
    app_bleData.state = APP_BLE_STATE_INIT;
    
}

/******************************************************************************
  Function:
    void APP_BLE_Tasks ( void )

  Remarks:
    See prototype in app_ble.h.
 */
/* TODO: implement your application state machine.*/

void APP_BLE_Tasks(void) {   
   
    /* Check the application's current state. */
    switch (app_bleData.state) {
        /* Application's initial state. */
        case APP_BLE_STATE_INIT:
        {
            bool appInitialized = true;           

            RNBD_Init();
            
            printf("\r\n\nRNBD451 BLE is Initialized\r\n");
            
            RNBD_SetAsyncMessageHandler(statusBuffer, (uint8_t)sizeof(statusBuffer));              

            if (appInitialized) {

                app_bleData.state = APP_BLE_STATE_FACTORY_RESET;
            }
            break;
        }       
        
        
        case APP_BLE_STATE_FACTORY_RESET:
        {
            cmdStat=RNBD_EnterCmdMode();
            
            /*Condition Checking for successful command mode entry*/
            if(cmdStat) 
            {
                printf("Device entered CMD Mode\r\n"); 
                cmdStat=false;    
                 
            }
           
            if(RNBD_SF2_FactoryReset()) 
            {                               
                printf("\r\nEntered Factory reset Mode\r\n");   
                while (RNBD.DataReady())
                {
                    dummyread=RNBD.Read();
                    printf("%c",dummyread); /*Flush any unwanted data,"REBOOT"*/
                }
                app_bleData.state = APP_BLE_STATE_GATT_SERV_INIT;
                
            }
            break;
        }
        
        case APP_BLE_STATE_GATT_SERV_INIT:
        {
            char PS[]="49535343FE7D4AE58FA99FAFD205E455";
            char PC_TX[]="495353431E4D4BD9BA6123C647249616,02,05"; //(Allows Read)
            char PC_RX[]="49535343884143F4A8D4ECBE34729BB3,0E,02";//(Allows Write with ACK)
            cmdStat=RNBD_EnterCmdMode();
            if(cmdStat)
            {
                printf("\r\nEntered CMD Mode\r\n");
                cmdStat=false;           
                              
            }
            
            cmdStat=RNBD_SetServiceUUID(PS,strlen(PS));
            if(cmdStat)
            {
                printf("Service UUID Set\r\n");
                cmdStat=false;                
                             
            }
            
            cmdStat=RNBD_SetServiceCharacteristic(PC_TX,strlen(PC_TX));
            if(cmdStat)
            {
                cmdStat=false;                
                printf("Service TX Temperature Characteristic Set\r\n");                 
            }
            
            cmdStat=RNBD_SetServiceCharacteristic(PC_RX,strlen(PC_RX));
            if(cmdStat)
            {
                cmdStat=false;                
                printf("Service RX Temperature Characteristic Set\r\n");
                
            }
            
            cmdStat=RNBD_SetName(BleDevName,strlen(BleDevName));
            if(cmdStat)
            {
                cmdStat=false;                
                printf("Device name set : %s\r\n",BleDevName);
                app_bleData.state = APP_BLE_STATE_REBOOT; 
            }
          break;  
            
        }        
        
        
        case APP_BLE_STATE_REBOOT:
        {
            cmdStat=RNBD_Reboot();
            if(cmdStat)
            {
                cmdStat=false;                
                printf("Reboot Completed\r\n");
                
            }
            /*Check for %REBOOT% response after RNBD451 reboot*/
            while (RNBD.DataReady())
             {
                dummyread=RNBD.Read();                
                printf("%c",dummyread);
             }
            
            app_bleData.state = APP_BLE_STATE_ADVERTISEMENT;            

            break;
        }

        case APP_BLE_STATE_ADVERTISEMENT:
        {
            app_bleData.state = APP_BLE_STATE_CHECK_CONNECTION;
            printf("\r\n\n");
            break;
        }        
        

        case APP_BLE_STATE_CHECK_CONNECTION:
        {   
            printf("\r\nConnecting...\r\n");            
            
            while(!RNBD.DataReady()) 
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
                RNBD.DelayMs(10);
            } 
                      
            str=strstr(responseBuf,"PHY_UPDATED");
            strncpy(connHandleStr,&str[12],4);  
            LED0_On();
            printf("\r\nConnected !!\r\n");
            printf("\r\nConnection handle:%s",connHandleStr);        
            responseBufcount=0;
            statusBuffercount=0;
            app_bleData.state = APP_BLE_STATE_COMMAND;
            break; 
        }
        
        case APP_BLE_STATE_COMMAND:
        {
            cmdStat=RNBD_EnterCmdMode();
            if(cmdStat)
            {
                cmdMode=true;
                cmdStat=false;                
                printf("\r\nEntered CMD Mode\r\n");
                app_bleData.state = APP_BLE_STATE_WAIT;
            }
            break;
        }
        
        case APP_BLE_STATE_TEMP_LOCAL_UPDATE:
        {            
            char tx_handle[]="1002";           
           
            temperature_conversion(temperatureVal,temperatureString);            
            
            status=RNBD_WriteLocalCharacteristic(tx_handle,strlen(tx_handle),temperatureString,2);
            if(status!=0)
            {
                 printf("\r\nTemperature Updated locally\r\n");
            }
            else 
                printf("\r\nNo local temperature update\r\n");
            
            app_bleData.state = APP_BLE_STATE_THRESHOLD_CHANGE;
         }
            
            break;             

         
        case APP_BLE_STATE_THRESHOLD_CHANGE:
        {
            char rx_handle[5]="1004";            
            if (RNBD.DataReady())
            {
                RNBD.DelayMs(200);
                while(RNBD.DataReady())
                {
                   dummyread=RNBD.Read();
                   printf("%c",dummyread); /*Flush any unwanted data,"%wv,0071,1004%"*/
                }
            status=RNBD_ReadLocalCharacteristic(rx_handle,strlen(rx_handle),temperatureThreshold,1);
            char_to_int(temperatureThreshold,&tempLimit);
            printf("\r\n\nTemperature Threshold : %d C",tempLimit);
            if(status!=0)
            {
                 printf("\r\nTemp. Limit received from central\r\n");
            }
            else 
                printf("\r\nTemp. Limit not received\r\n");
            if((temperatureCel>=tempLimit)&&(temperatureVal!=0)&&(tempLimit!=0))
            {
                LED1_On();
            }
            else
                LED1_Off();
            } 
           app_bleData.state =  APP_BLE_STATE_WAIT;
            
        }
        break;
                      
        case APP_BLE_STATE_WAIT:
        {            
            break;
        }
        case APP_BLE_STATE_COMPLETE:
            break;
            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }

    }
    
}