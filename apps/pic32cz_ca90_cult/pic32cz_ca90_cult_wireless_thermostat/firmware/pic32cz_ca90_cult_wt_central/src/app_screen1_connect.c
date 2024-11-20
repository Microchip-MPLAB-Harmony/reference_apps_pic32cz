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
    app_screen1_connect.c

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

#include "app_screen1_connect.h"
#include "gfx/legato/generated/le_gen_init.h"
#include "gfx/legato/generated/screen/le_gen_screen_Screen1.h"
#include "gfx/legato/legato.h"
#include <stdio.h>
#include <string.h>
#include "gfx/legato/renderer/legato_renderer.h"
#include "system/time/sys_time.h"
#include "app_ble.h"

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
    This structure should be initialized by the APP_SCREEN1_CONNECT_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

#define ANIM_TIMER_TICK_PERIOD_MS   10
#define PROGRESS_TIMER_TICK_PERIOD_MS   1000

#define DEVICE_ACTIVE_IMAGE_ID 0
#define DEVICE_INACTIVE_IMAGE_ID 1
#define PROGRESS_FULL 4
#define NO_PROGRESS 0
#define MULTILINK_NUM_DEVICES 2 
#define DEVICE_ICON_POSX_HIDE_LEFT -80
#define DEVICE_ICON_POSX_HIDE_RIGHT 480
#define DEVICE_ANIM_COEFF 3
#define CONNECT_POSY_HIDE_BOTTOM 320
#define MAX_STATUS_LABEL_LENGTH 24


#define APP_LE_SETX(widget, xpos) widget->fn->setX(widget, xpos)
#define APP_LE_SETY(widget, ypos) widget->fn->setY(widget, ypos)
#define APP_LE_GETX(widget) widget->fn->getX(widget)
#define APP_LE_GETY(widget) widget->fn->getY(widget)
#define APP_LE_SETVISIBLE(widget, visible) widget->fn->setVisible(widget, visible)
#define APP_LE_SHOWIMAGE_NEXT(imageSequenceWidget) imageSequenceWidget->fn->showNextImage(imageSequenceWidget)
#define APP_LE_SHOWIMAGE_IDX(imageSequenceWidget, idx) imageSequenceWidget->fn->showImage(imageSequenceWidget, idx)
#define APP_LE_SETLABELSTRING(labelWidget, string) labelWidget->fn->setString(labelWidget, (leString*)&string);

typedef struct
{
    leImageSequenceWidget * deviceImage;  
    leLabelWidget * deviceLabel;
    leImageWidget * deviceStatusIcon;
    uint32_t xpos;
    uint32_t ypos;  
} ML_CONNECT_DEVICE;

static APP_BLE_DEVICE_ID currentDevice = DEV1;
static uint32_t connectedDevicesCount = 0;
static ML_CONNECT_DEVICE devices[MULTILINK_NUM_DEVICES] = {0};
static SYS_TIME_HANDLE mlConnectAnimTimer = SYS_TIME_HANDLE_INVALID;
SYS_TIME_HANDLE mlConnectProgressTimer = SYS_TIME_HANDLE_INVALID;
static volatile uint32_t mlConnectProgressTickCount = 0;
static volatile uint32_t mlConnectAnimTickCount = 0;
static uint32_t mlConnectAnimTickPrev = 0;

static void MLConnectAnimTimer_Callback (uintptr_t context);
static void MLConnectProgressTimer_Callback (uintptr_t context);
static void MLConnect_InitDeviceTable(void);
static void MLConnect_UpdateStatusString(char * str);

static leFixedString statusStr;
static leChar statusStrBuff[MAX_STATUS_LABEL_LENGTH] = {0};

extern APP_BLE_DATA app_bleData;
extern APP_BLE_DEVICE multiLinkDemoDevices[];
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static void MLConnectAnimTimer_Callback (uintptr_t context)
{
    mlConnectAnimTickCount++;
}

static void MLConnectProgressTimer_Callback (uintptr_t context)
{
    appScreenMLConnectState=ML_CONNECT_CONNECTING;
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

void Screen1_OnShow()
{
    appScreenMLConnectState= ML_CONNECT_INIT;
    
    MLConnect_InitDeviceTable();
    
    leFixedString_Constructor(&statusStr, statusStrBuff, MAX_STATUS_LABEL_LENGTH);
    
    statusStr.fn->setFont(&statusStr, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              stringID_Connecting,
                                                              0));
    
    APP_LE_SETX(devices[DEV1].deviceImage, DEVICE_ICON_POSX_HIDE_LEFT);
    APP_LE_SETX(devices[DEV2].deviceImage, DEVICE_ICON_POSX_HIDE_RIGHT);
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceStatusIcon, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceStatusIcon, LE_FALSE);
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceLabel, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceLabel, LE_FALSE);
    
    APP_LE_SHOWIMAGE_IDX(devices[DEV1].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
    APP_LE_SHOWIMAGE_IDX(devices[DEV2].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
    
    APP_LE_SHOWIMAGE_IDX(devices[DEV1].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
    APP_LE_SHOWIMAGE_IDX(devices[DEV2].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
    
    APP_LE_SETVISIBLE(Screen1_ImageSequenceWidget_ProgressAnime, LE_FALSE);
    APP_LE_SETVISIBLE(Screen1_Connectionstatus_label, LE_FALSE);    
   
    MLConnect_UpdateStatusString("Scanning...");
    mlConnectAnimTickCount = 0;
    mlConnectAnimTimer = SYS_TIME_CallbackRegisterMS(MLConnectAnimTimer_Callback,
                                                     1, ANIM_TIMER_TICK_PERIOD_MS,
                                                     SYS_TIME_PERIODIC);
    
    mlConnectProgressTimer =  SYS_TIME_CallbackRegisterMS(MLConnectProgressTimer_Callback,
                                                    1, PROGRESS_TIMER_TICK_PERIOD_MS,
                                                    SYS_TIME_PERIODIC);
            
    SYS_TIME_TimerStop(mlConnectAnimTimer);
    SYS_TIME_TimerStop(mlConnectProgressTimer);
}

void Screen1_OnHide()
{
    mlConnectProgressTickCount=0;
    mlConnectAnimTickCount=0;
    multiLinkDemoDevices[NODE_1].connected=0;
    multiLinkDemoDevices[NODE_2].connected=0;
    SYS_TIME_TimerDestroy(mlConnectAnimTimer);
    SYS_TIME_TimerDestroy(mlConnectProgressTimer);
    appScreenMLConnectState = ML_CONNECT_INIT;    
}

void Screen1_OnUpdate(){
    
    switch (appScreenMLConnectState) {
        case ML_CONNECT_INIT:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0) {      
                
                currentDevice = DEV1;
                connectedDevicesCount=0;
                SYS_TIME_TimerStart(mlConnectAnimTimer);             
                appScreenMLConnectState =ML_CONNECT_ANIM0;               
                APP_LE_SETVISIBLE(Screen1_ImageSequenceWidget_ProgressAnime, LE_FALSE);
            }
            break;
        }
        case ML_CONNECT_ANIM0:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){                     
            
            if (mlConnectAnimTickCount != mlConnectAnimTickPrev)
            {
                int32_t xpos = APP_LE_GETX(devices[DEV1].deviceImage);
                int32_t deltaX = (devices[DEV1].xpos - xpos) / DEVICE_ANIM_COEFF;
                
                appScreenMLConnectState =ML_CONNECT_ANIM1;                
                
                if (deltaX > 0)
                {
                    APP_LE_SETX(devices[DEV1].deviceImage, xpos + deltaX);
                    
                    appScreenMLConnectState =ML_CONNECT_ANIM0;
                }
                else
                {
                    APP_LE_SETX(devices[DEV1].deviceImage, devices[DEV1].xpos);
                }
                
                xpos = APP_LE_GETX(devices[DEV2].deviceImage);
                deltaX = (xpos - devices[DEV2].xpos) / DEVICE_ANIM_COEFF;
                
                if (deltaX > 0)
                {
                    appScreenMLConnectState =ML_CONNECT_ANIM0;
                    
                    APP_LE_SETX(devices[DEV2].deviceImage, xpos - deltaX);
                }
                else
                {
                    APP_LE_SETX(devices[DEV2].deviceImage, devices[DEV2].xpos);
                }

                mlConnectAnimTickPrev = mlConnectAnimTickCount;
            }                      
            
            }
            break;
        }
        
        case ML_CONNECT_ANIM1:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){                  

                APP_LE_SETVISIBLE(devices[DEV1].deviceLabel, LE_TRUE);           
                APP_LE_SETVISIBLE(devices[DEV2].deviceLabel, LE_TRUE);
              
                appScreenMLConnectState =ML_CONNECT_ANIM_DONE;                 
            }
            break;
        }
        
        case ML_CONNECT_ANIM_DONE:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){
            
                APP_LE_SHOWIMAGE_IDX(devices[DEV1].deviceImage, DEVICE_INACTIVE_IMAGE_ID);
                APP_LE_SHOWIMAGE_IDX(devices[DEV2].deviceImage, DEVICE_INACTIVE_IMAGE_ID);                       

                APP_LE_SETVISIBLE(Screen1_ImageSequenceWidget_ProgressAnime, LE_TRUE);
                APP_LE_SETVISIBLE(Screen1_Connectionstatus_label, LE_TRUE);                                          
                

                SYS_TIME_TimerStop(mlConnectAnimTimer);                                           

                appScreenMLConnectState =ML_CONNECT_START_SCANNING;

                currentDevice = DEV1;
            }            
            break;
        } 
        case ML_CONNECT_START_SCANNING:
        {
           app_bleData.state=APP_BLE_STATE_SCANNING;
           appScreenMLConnectState = ML_CONNECT_WAIT;           
           break;
        }
        
        case ML_CONNECT_START_CONNECT:
        {  
            if(currentDevice==DEV1)
                MLConnect_UpdateStatusString("Connecting Node 1");            
            SYS_TIME_TimerStart(mlConnectProgressTimer);            
            appScreenMLConnectState = ML_CONNECT_WAIT;           
            break;
        }
        
        case ML_CONNECT_CONNECTING:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){            
                APP_LE_SHOWIMAGE_NEXT(Screen1_ImageSequenceWidget_ProgressAnime);
                APP_LE_SHOWIMAGE_NEXT(devices[currentDevice].deviceImage);                        
                mlConnectProgressTickCount++;            
                if(mlConnectProgressTickCount>10){              
                    if(currentDevice==DEV1)
                        app_bleData.state=APP_BLE_STATE_START_CONNECTION_NODE1;                     
                    else if(currentDevice==DEV2)
                        app_bleData.state=APP_BLE_STATE_START_CONNECTION_NODE2;                    
                }            
                appScreenMLConnectState = ML_CONNECT_WAIT;
            }
            break;
        }
        
        case ML_CONNECT_DEVICE_CONNECTED:{
            
            if((multiLinkDemoDevices[NODE_1].connected)||(multiLinkDemoDevices[NODE_2].connected)){
                if((multiLinkDemoDevices[NODE_1].connected)&&(!multiLinkDemoDevices[NODE_2].connected))
                    {
                        APP_LE_SETVISIBLE(Screen1_ImageWidgetCheck1,LE_TRUE);
                        APP_LE_SHOWIMAGE_IDX(Screen1_ImageSequenceWidget_ProgressAnime, PROGRESS_FULL);
                        MLConnect_UpdateStatusString("Connected to Node 1");                        
                        currentDevice++;                                               
                    }
                if(multiLinkDemoDevices[NODE_2].connected){
                        APP_LE_SETVISIBLE(Screen1_ImageWidgetCheck2,LE_TRUE);                        
                        currentDevice++;
                    }     
                mlConnectProgressTickCount=0;                                     
                connectedDevicesCount++;                        
                if (currentDevice >= DEVMAX)
                {  
                    if (connectedDevicesCount > 0)
                    {                   

                        MLConnect_UpdateStatusString("Preparing");
                        appScreenMLConnectState =ML_CONNECT_WAIT;
                        
                    }
                    else //No devices connected
                    {
                        appScreenMLConnectState =ML_CONNECT_FAILED;                    
                        
                    }
                }
                else{
                    appScreenMLConnectState = ML_CONNECT_START_CONNECT; 
                    APP_LE_SHOWIMAGE_IDX(Screen1_ImageSequenceWidget_ProgressAnime, NO_PROGRESS);
                    MLConnect_UpdateStatusString("Connecting Node 2"); 
                }
            }
                break;
        }
        
        case ML_CONNECT_CONNECTED_INIT:
        {
            legato_showScreen(screenID_Screen2);  
        }
        
        case ML_CONNECT_WAIT:                
        default:
            break;
    }
}

static void MLConnect_InitDeviceTable(void)
{
    devices[DEV1] = (ML_CONNECT_DEVICE)
    {   .deviceImage = Screen1_ImageSequenceWidget_Node1, 
        .deviceLabel = Screen1_LabelWidgetNode1,
        .deviceStatusIcon = Screen1_ImageWidgetCheck1,
    };
    
    devices[DEV1].xpos = APP_LE_GETX(devices[DEV1].deviceImage);
    devices[DEV1].ypos = APP_LE_GETY(devices[DEV1].deviceImage);

    devices[DEV2] = (ML_CONNECT_DEVICE)
    {   .deviceImage = Screen1_ImageSequenceWidget_Node2, 
        .deviceLabel = Screen1_LabelWidgetNode2,
        .deviceStatusIcon = Screen1_ImageWidgetCheck2,
    };
    
    devices[DEV2].xpos = APP_LE_GETX(devices[DEV2].deviceImage);
    devices[DEV2].ypos = APP_LE_GETY(devices[DEV2].deviceImage);      
}

static void MLConnect_UpdateStatusString(char * str)
{
    if (strlen(str) > MAX_STATUS_LABEL_LENGTH)
        return;
    
    statusStr.fn->setFromCStr(&statusStr, str);    
    APP_LE_SETLABELSTRING(Screen1_Connectionstatus_label, statusStr);
}

/*******************************************************************************
 End of File
 */
