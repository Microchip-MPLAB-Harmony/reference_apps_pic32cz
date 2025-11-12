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
  MPLAB Harmony BLE Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ble.c

  Summary:
    This file contains the source code for the MPLAB Harmony BLE application.

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
#include "app_ble.h"
#include "definitions.h"
#include "app_screen1_connect.h"
#include "app_screen2_monitor.h"
#include "app_screen3_setlimit.h"
#include "rnbd/rnbd.h"
#include "rnbd/rnbd_interface.h"
#include "string.h"
#include <ctype.h>
#include "app_rnbd.h"
#include "stdio.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

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

/*** LED Macros for LED0 ***/

#define LED0_On()         (PORT_REGS->GROUP[1].PORT_OUTCLR = 1UL << 21)
#define LED0_Off()        (PORT_REGS->GROUP[1].PORT_OUTSET = 1UL << 21)

/*** LED Macros for LED1 ***/
#define LED1_On()         (PORT_REGS->GROUP[1].PORT_OUTCLR = 1UL << 22)
#define LED1_Off()        (PORT_REGS->GROUP[1].PORT_OUTSET = 1UL << 22)

APP_BLE_DEVICE multiLinkDemoDevices[MULTILINK_NUM_DEVICES] = 
{
    {.valid = true, .active = true, .deviceAddress = "9C956E406AEB", .deviceName = "N1"},   
    {.valid = true, .active = true, .deviceAddress = "A6A5A4A3A2A1", .deviceName = "N2"},
      
};
APP_BLE_DATA app_bleData = {0};
char statusBuffer[MAX_BUFFER_SIZE] = {0};
ML_MONITOR_SCREEN_STATE appScreenMLMonitorState = ML_MONITOR_INIT;
ML_CONNECT_SCREEN_STATE appScreenMLConnectState = ML_CONNECT_INIT;
extern SYS_TIME_HANDLE mlConnectProgressTimer;
static volatile bool status = false;

char sensorTemp1[5]={0};
char sensorTemp2[5]={0};
char temperatureSTRING[4]={0};
uint8_t TemperatureVal=0;
uint8_t Calc_tempString(char *tempVal);
uint8_t CutOff=0;
char tempConv[5]={0};
char deviceName_hexString[50]={0};
char deviceName_hexString_length[50]={0};


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


uint8_t Calc_tempString(char *tempVal)
{        
    if ('0' <= *tempVal && *tempVal <= '9') {
        TemperatureVal = (uint8_t)(*tempVal - '0'); 
    } else if ('A' <= *tempVal && *tempVal <= 'F') {
        TemperatureVal = (uint8_t)(*tempVal - 'A' + 10); 
    } else {        
        return 0xFF; 
    }
    tempVal++;     
    if ('0' <= *tempVal && *tempVal <= '9') {
        TemperatureVal = (uint8_t)((TemperatureVal << 4) | (*tempVal - '0')); // Combine digits
    } else if ('A' <= *tempVal && *tempVal <= 'F') {
        TemperatureVal = (uint8_t)((TemperatureVal << 4) | (*tempVal - 'A' + 10)); // Combine digits
    } else {        
        return 0xFF; 
    }
    sprintf(temperatureSTRING,"%d",TemperatureVal);
}

void Calc_limitString(uint8_t CutOff, char *tempConv) {
    
    char tempBuf[3];
    tempConv[0] = '0';
    tempConv[1] = '0';
    tempConv[2] = '\0';
    tempConv[3] = '\0';

    if (CutOff < 100) {
        /*Handle values less than 100*/
        tempBuf[0] = (CutOff / 10) + '0'; 
        tempBuf[1] = (CutOff % 10) + '0'; 
        tempConv[0]=((tempBuf[1]>>4)&0x0F)+'0';
        tempConv[1]=(tempBuf[1]&0x0F)+'0';
        tempConv[2]=((tempBuf[0]>>4)&0x0F)+'0';
        tempConv[3]=(tempBuf[0]&0x0F)+'0';
    } else {
        /* Handle values greater than or equal to 100*/
        tempConv[0] = '1'; // Hundreds place
        tempConv[1] = (CutOff % 100 / 10) + '0'; 
        tempConv[2] = (CutOff % 10) + '0'; 
    } 
        
}

void convertToHexString(const char *input, char *output) {
    while (*input) {
        /*Convert each character to hexadecimal format and store in output*/
        sprintf(output, "%02X", (unsigned char)*input);
        output += 2; /* Move the output pointer forward by 2 for the next hex value*/
        input++; /*Move to the next character in the input*/
    }
    *output = '\0'; // Null-terminate the output string
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

  /* TODO: Initialize your application's state machine and other
     * parameters.
     */
void APP_BLE_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_bleData.state = APP_BLE_STATE_INIT;   
}

/******************************************************************************
  Function:
    void APP_BLE_Tasks ( void )

  Remarks:
    See prototype in app_ble.h.
 */

void APP_BLE_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( app_bleData.state )
    {
        /* Application's initial state. */
        case APP_BLE_STATE_INIT:
        {            
            bool appInitialized = true;

            RNBD_Init();                       
            
            RNBD_SetAsyncMessageHandler(statusBuffer, (uint8_t)sizeof(statusBuffer));  
            
            if (appInitialized) {

                app_bleData.state = APP_BLE_STATE_INIT_CONNCTION;               
               
            }
            break;
        }
        
         
        case APP_BLE_STATE_INIT_CONNCTION:
        {                       
            if(RNBD_EnterCmdMode()){
                
                app_bleData.state = APP_BLE_STATE_WAIT;
            }           
            break;
        }  
        
        
        case APP_BLE_STATE_SCANNING:
        {
            convertToHexString(multiLinkDemoDevices[NODE_1].deviceName,deviceName_hexString);
            multiLinkDemoDevices[NODE_1].deviceName_hex_length= strlen(multiLinkDemoDevices[NODE_1].deviceName);
            sprintf(deviceName_hexString_length, "%02X", multiLinkDemoDevices[NODE_1].deviceName_hex_length);
            strcat(deviceName_hexString_length,deviceName_hexString);
            status=scan_Node1(multiLinkDemoDevices[NODE_1].deviceAddress,deviceName_hexString_length);            
            if(status){
                appScreenMLConnectState =ML_CONNECT_START_CONNECT;
                app_bleData.state = APP_BLE_STATE_WAIT;
            }
            else
                app_bleData.state = APP_BLE_STATE_ERROR;
            break;
        }
        
         
        case APP_BLE_STATE_START_CONNECTION_NODE1:
        {                          
            Connect_Node1(multiLinkDemoDevices[NODE_1].deviceAddress);    //Connect to Lifeguard  - BLE node 1

            multiLinkDemoDevices[NODE_1].connected= RNBD_IsConnected();                                 

            if(multiLinkDemoDevices[NODE_1].connected==true){

                SYS_TIME_TimerStop(mlConnectProgressTimer);

                Set_RNBD_IsConnected(false); // For multilink 

                Set_Streamconnect(false);

                LED0_On();      //Indicate Node 1 connected  

                appScreenMLConnectState =ML_CONNECT_DEVICE_CONNECTED; 
                
                app_bleData.state =APP_BLE_STATE_INIT_CONNCTION;  

            }

            break;
        }
        
        
        case APP_BLE_STATE_START_CONNECTION_NODE2:
        {         
                          
            Connect_Node2(multiLinkDemoDevices[NODE_2].deviceAddress); //Connect to WBZ451  - BLE node 2

            multiLinkDemoDevices[NODE_2].connected= RNBD_IsConnected();

            if(multiLinkDemoDevices[NODE_2].connected==true){

                SYS_TIME_TimerStop(mlConnectProgressTimer);   

                Set_Streamconnect(false);

                LED1_On();

                appScreenMLConnectState =ML_CONNECT_DEVICE_CONNECTED; 
                
                app_bleData.state = APP_BLE_STATE_NODE1_GATT_CLI_ENABLE;                 
            }

            break;
        }
        
        
        case APP_BLE_STATE_NODE1_GATT_CLI_ENABLE:
        {  
            /*Flush unwanted data if any*/
            while (RNBD.DataReady())
            {
                RNBD.Read();                   
            }
            
            status= RNBD_Set_GATTClient(NODE_1);  
            
            if(status)
            {                                
                app_bleData.state = APP_BLE_STATE_NODE2_GATT_CLI_ENABLE;
            }
            
            else
                app_bleData.state = APP_BLE_STATE_ERROR;
                
            break;
        }
        
        
        case APP_BLE_STATE_NODE2_GATT_CLI_ENABLE:
        {
            /*Flush unwanted data if any*/
            while (RNBD.DataReady())
            {
                RNBD.Read();                   
            }
          
            status= RNBD_Set_GATTClient(NODE_2);            
            if(status)
            {
                app_bleData.state = APP_BLE_STATE_WAIT;
                appScreenMLConnectState =ML_CONNECT_CONNECTED_INIT;
            }
            else
                app_bleData.state = APP_BLE_STATE_ERROR;
            
            break;
        }
        
        case APP_BLE_STATE_FETCH_NODE1_TEMP:
        {
            char tx_handle[]="1002";
            
            /*Flush unwanted data if any*/
            while (RNBD.DataReady())
            {
                RNBD.Read();                   
            }
            
            status= RNBD_ReadremoteCharacteristic(NODE_1,tx_handle,strlen(tx_handle),sensorTemp1,4);           
            
            if(status)
            {               
                appScreenMLMonitorState=ML_MONITOR_TEMP1_SCREEN_WRITE;
                SERCOM2_USART_Write(sensorTemp1,4);
            }
            
            else
                app_bleData.state = APP_BLE_STATE_ERROR;
            
            app_bleData.state = APP_BLE_STATE_FETCH_NODE2_TEMP;
            
            break;
        }
        
        
        case APP_BLE_STATE_FETCH_NODE2_TEMP:
        {
            char tx_handle[]="8002";  
            
            /*Flush unwanted data if any*/
            while (RNBD.DataReady())
            {
                RNBD.Read();                   
            }
            
            status= RNBD_ReadremoteCharacteristic(NODE_2,tx_handle,strlen(tx_handle),sensorTemp2,4); 
            
            Calc_tempString(&sensorTemp2[2]);
            
            memcpy(&sensorTemp2[2],temperatureSTRING,2);
            
            if(status)
            {                
                SERCOM2_USART_Write(sensorTemp2,4);
                appScreenMLMonitorState=ML_MONITOR_TEMP2_SCREEN_WRITE;
            }
            else
                app_bleData.state = APP_BLE_STATE_ERROR;
            
            app_bleData.state = APP_BLE_STATE_WAIT;
            break;
        }
        
        
        case APP_BLE_STATE_SEND_TEMP_LIMIT_N1:
        {
            char tx_handle[]="1004"; 
            
            /*Flush unwanted data if any*/
            while (RNBD.DataReady())
            {
                RNBD.Read();                   
            }

            getLimit(&CutOff,NODE_1);
            
            Calc_limitString(CutOff,tempConv); 
            
            status= RNBD_WriteremoteCharacteristic(NODE_1,tx_handle,strlen(tx_handle),tempConv);  
            
            if(status!=true)
                app_bleData.state = APP_BLE_STATE_ERROR;
            
            app_bleData.state = APP_BLE_STATE_WAIT;
            
            break;
            
        }
        
        
        case APP_BLE_STATE_SEND_TEMP_LIMIT_N2:
        {
            char tx_handle[]="8005"; 
            
            /*Flush unwanted data if any*/
            while (RNBD.DataReady())
            {
                RNBD.Read();                   
            }

            getLimit(&CutOff,NODE_2);
            
            Calc_limitString(CutOff,tempConv); 
            
            status= RNBD_WriteremoteCharacteristic(NODE_2,tx_handle,strlen(tx_handle),tempConv);  
            
            if(status!=true)
                app_bleData.state = APP_BLE_STATE_ERROR;
            
            app_bleData.state = APP_BLE_STATE_WAIT;;
            
            break;
        }   
        
        case APP_BLE_STATE_DISCONNECT:
        {
              RNBD_Disconnect();
              LED0_Off();
              LED1_Off();
              app_bleData.state=APP_BLE_STATE_INIT;
        }
            
        case APP_BLE_STATE_WAIT:
        {
            break;
        }        
        
        case APP_BLE_STATE_ERROR:
        {
            LED0_Off();
            LED1_Off();
            break;
        }      


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
