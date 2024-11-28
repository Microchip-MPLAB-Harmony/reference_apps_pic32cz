/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "app_mqtt.h"

#ifdef SYS_MQTT_DEF_PUB_TOPIC_NAME
#include "system/mqtt/sys_mqtt.h"
#include "system/sys_time_h2_adapter.h"
#include "string.h"
#include "cryptoauthlib.h"
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

#define RX_BUFFER_SIZE                  40
#define TEMP_RECV_BUFFER                10
#ifdef SYS_MQTT_DEF_PUB_TOPIC_NAME
static uint32_t     g_lastPubTimeout = 0;
#define MQTT_PERIOIDC_PUB_TIMEOUT   30 //Sec ; if the value is 0, Periodic Publish will disable
#define MQTT_PUB_TIMEOUT_CONST (MQTT_PERIOIDC_PUB_TIMEOUT * SYS_TMR_TickCounterFrequencyGet())
#endif

ATCA_STATUS status;
ATCAIfaceCfg *cfg;
uint8_t tempRecv[TEMP_RECV_BUFFER]={0};
char message[RX_BUFFER_SIZE]={0};
volatile bool readStatus=false;
volatile bool errorStatus=false;
extern ATCAIfaceCfg atecc608_0_init_data;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/
APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void APP_ReadCallback(uintptr_t context)
{   
    
    if(UART2_ErrorGet() != UART_ERROR_NONE)
    {
        /* ErrorGet clears errors, set error flag to notify console */
        errorStatus = true;
    }
    else
    {
        readStatus = true;
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/
void message_frame()
{ 
    char tempBuf[3]={0};   
    tempBuf[0]=tempRecv[2];
    tempBuf[1]=tempRecv[3];
    if(tempRecv[1]=='1')
    {       
      sprintf(message,"{\"Temperature of Node 1\":\"%s\" deg C}",tempBuf);
    } else if(tempRecv[1]=='2')
    {
      sprintf(message,"{\"Temperature of Node 2\":\"%s\" deg C}",tempBuf); 
    }
    return;
}


#ifdef SYS_MQTT_DEF_PUB_TOPIC_NAME

void APP_CheckTimeOut(uint32_t timeOutValue, uint32_t lastTimeOut)
{      
	if(SYS_MQTT_STATUS_MQTT_CONNECTED != APP_MQTT_GetStatus(NULL))
	{
        SYS_CONSOLE_PRINT("\nNot connected to MQTT : Publish Topic %s\r\n",SYS_MQTT_DEF_PUB_TOPIC_NAME);
        appData.state = APP_STATE_WAIT_READ_TASK;
		return;
	}    
	static uint32_t PubMsgCnt = 0;    
   
    message_frame();   
  
   if (APP_MQTT_PublishMsg(message)== SYS_MQTT_SUCCESS)
	{
        SYS_CONSOLE_PRINT("\nPublished Message to Topic %s\r\n",SYS_MQTT_DEF_PUB_TOPIC_NAME);         
		PubMsgCnt++;
	}

	appData.state = APP_STATE_WAIT_READ_TASK;

}
#endif


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
/* TODO: Initialize your application's state machine and other
     * parameters.
*/
void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    cfg = &atecc608_0_init_data;
    
	APP_MQTT_Initialize();
     
    UART2_ReadCallbackRegister(APP_ReadCallback, 0);
     
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
  /* TODO: implement your application state machine.*/
void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state )
    {        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
           
            if (appInitialized)
            {          
                appData.state = APP_STATE_WAIT; 
            }
            break;
        }

        case APP_STATE_WAIT_READ_TASK: 
        {      
            SYS_CONSOLE_PRINT("\nTemperature to be received\r\n");
            
            UART2_Read(tempRecv, 4);         
            
            appData.state = APP_STATE_PUBLISH_SERVICE_TASK;
            
            break;
            
        }      
     
        case APP_STATE_PUBLISH_SERVICE_TASK:
        {    
            if(readStatus==true){
                readStatus=false;
            #ifdef SYS_MQTT_DEF_PUB_TOPIC_NAME            	
               APP_CheckTimeOut(MQTT_PUB_TIMEOUT_CONST, g_lastPubTimeout); //Publish data to cloud
            #endif
            }else if(errorStatus==true)
                appData.state = APP_STATE_ERROR;
            break;
        }
        /* The default state should never be executed. */
        case APP_STATE_ERROR:
        {
            SYS_CONSOLE_PRINT("\nError in publishing data..\r\n");
            break;
        }
        
        case APP_STATE_WAIT:
        {
            if(SYS_MQTT_STATUS_MQTT_CONNECTED == APP_MQTT_GetStatus(NULL))
            {                
                appData.state = APP_STATE_WAIT_READ_TASK;                
            }
            
            break;
        }
        
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        } 
     }
    APP_MQTT_Tasks(); 
}
/*******************************************************************************
 End of File
 */
