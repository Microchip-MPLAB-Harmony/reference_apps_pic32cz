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
  MPLAB Harmony Application Temperature Monitor Screen Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_screen2_monitor.c

  Summary:
    This file contains the source code for the monitor screen of the demo.

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

#include "app_screen2_monitor.h"
#include "gfx/legato/generated/le_gen_init.h"
#include "gfx/legato/generated/screen/le_gen_screen_Screen2.h"
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

#define ANIM_TIMER_TICK_PERIOD_MS   10
#define UPDATE_TIMER_TICK_PERIOD_MS   1000

#define MULTILINK_NUM_DEVICES 2 
#define DEVICE_ICON_POSX_HIDE_LEFT -80
#define DEVICE_ICON_POSX_HIDE_RIGHT 480
#define DEVICE_ANIM_COEFF 3
#define CONNECT_POSY_HIDE_BOTTOM 320

#define MAX_STATUS_LABEL_LENGTH 24
#define MAX_TEXT_LENGTH 6

#define APP_LE_SETX(widget, xpos) widget->fn->setX(widget, xpos)
#define APP_LE_SETY(widget, ypos) widget->fn->setY(widget, ypos)
#define APP_LE_GETX(widget) widget->fn->getX(widget)
#define APP_LE_GETY(widget) widget->fn->getY(widget)
#define APP_LE_SETVISIBLE(widget, visible) widget->fn->setVisible(widget, visible)
#define APP_LE_SETLABELSTRING(labelWidget, string) labelWidget->fn->setString(labelWidget, (leString*)&string);
#define APP_LE_SETTEXTSTRING(TextWidget, string) TextWidget->fn->setString(TextWidget, (leString*)&string);

typedef struct
{
    leImageWidget * deviceImage;  
    leLabelWidget * deviceLabel;
    leTextFieldWidget * deviceVal;
    uint32_t xpos;
    uint32_t ypos;  
} ML_MONITOR_DEVICE;


static APP_BLE_DEVICE_ID currentDevice = DEV1;
static ML_MONITOR_DEVICE devices[MULTILINK_NUM_DEVICES] = {0};
static SYS_TIME_HANDLE mlMonitorAnimTimer = SYS_TIME_HANDLE_INVALID;
SYS_TIME_HANDLE mlUpdateTimer = SYS_TIME_HANDLE_INVALID;

static volatile uint32_t mlMonitorAnimTickCount = 0;
static uint32_t mlMonitorAnimTickPrev = 0;

leFixedString statusStr1;
leChar statusStrBuff1[MAX_TEXT_LENGTH] = {0};

extern APP_BLE_DATA app_bleData;
extern char temperatureSTRING[];
extern char sensorTemp1[];

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static void MLMonitorAnimTimer_Callback (uintptr_t context)
{
    mlMonitorAnimTickCount++;
}

static void MLUpdateTimer_Callback (uintptr_t context)
{
     appScreenMLMonitorState =ML_MONITOR_TEMP_UPDATE;
}

void event_Screen2_ButtonWidget_Setlimit_OnReleased(leButtonWidget* btn)
{
    appScreenMLMonitorState =ML_SET_LIMIT;
}

void event_Screen2_ButtonWidget_Setlimit_OnPressed(leButtonWidget* btn)
{
    
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


void Screen2_OnShow()
{
    appScreenMLMonitorState= ML_MONITOR_INIT;
    
    MLMonitor_InitDeviceTable();
    
    leFixedString_Constructor(&statusStr1, statusStrBuff1, MAX_TEXT_LENGTH);
    
    
    statusStr1.fn->setFont(&statusStr1, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              string_Default_Temp.index,
                                                              0));
    
    APP_LE_SETX(devices[DEV1].deviceImage, DEVICE_ICON_POSX_HIDE_LEFT);
    APP_LE_SETX(devices[DEV2].deviceImage, DEVICE_ICON_POSX_HIDE_RIGHT);
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceVal, LE_TRUE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceVal, LE_TRUE);
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceLabel, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceLabel, LE_FALSE);    

    APP_LE_SETVISIBLE(Screen2_ButtonWidget_Setlimit, LE_FALSE);
    APP_LE_SETVISIBLE(Screen2_ImageWidget_CelsiusNode1,LE_FALSE);
    APP_LE_SETVISIBLE(Screen2_ImageWidget_CelsiusNode2,LE_FALSE);
 
    
    mlMonitorAnimTickCount = 0;
    mlMonitorAnimTimer = SYS_TIME_CallbackRegisterMS(MLMonitorAnimTimer_Callback,
                                                     1, ANIM_TIMER_TICK_PERIOD_MS,
                                                     SYS_TIME_PERIODIC);
    
    mlUpdateTimer =  SYS_TIME_CallbackRegisterMS(MLUpdateTimer_Callback,
                                                    1, UPDATE_TIMER_TICK_PERIOD_MS,
                                                    SYS_TIME_PERIODIC);
            
    SYS_TIME_TimerStop(mlMonitorAnimTimer);
    SYS_TIME_TimerStop(mlUpdateTimer);
}

void Screen2_OnHide()
{    
    mlMonitorAnimTickCount=0;    
    SYS_TIME_TimerDestroy(mlMonitorAnimTimer);
    SYS_TIME_TimerDestroy(mlUpdateTimer);
    appScreenMLMonitorState = ML_MONITOR_INIT;
    
}

void Screen2_OnUpdate(){
    
    switch (appScreenMLMonitorState) {
        case ML_MONITOR_INIT:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0) {      
                
                currentDevice = DEV1;
               
                SYS_TIME_TimerStart(mlMonitorAnimTimer);    
            
                appScreenMLMonitorState =ML_MONITOR_ANIM0;               
               
            }
            break;
        }
        case ML_MONITOR_ANIM0:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){                     
            
            if (mlMonitorAnimTickCount != mlMonitorAnimTickPrev)
            {
                int32_t xpos = APP_LE_GETX(devices[DEV1].deviceImage);
                int32_t deltaX = (devices[DEV1].xpos - xpos) / DEVICE_ANIM_COEFF;
                
                appScreenMLMonitorState =ML_MONITOR_ANIM1;                
                
                if (deltaX > 0)
                {
                    APP_LE_SETX(devices[DEV1].deviceImage, xpos + deltaX);
                    
                    appScreenMLMonitorState =ML_MONITOR_ANIM0;
                }
                else
                {
                    APP_LE_SETX(devices[DEV1].deviceImage, devices[DEV1].xpos);
                }
                
                xpos = APP_LE_GETX(devices[DEV2].deviceImage);
                deltaX = (xpos - devices[DEV2].xpos) / DEVICE_ANIM_COEFF;
                
                if (deltaX > 0)
                {
                    appScreenMLMonitorState =ML_MONITOR_ANIM0;
                    
                    APP_LE_SETX(devices[DEV2].deviceImage, xpos - deltaX);
                }
                else
                {
                    APP_LE_SETX(devices[DEV2].deviceImage, devices[DEV2].xpos);
                }

                mlMonitorAnimTickPrev = mlMonitorAnimTickCount;
            }                      
            
            }
            break;
        }
        
        case ML_MONITOR_ANIM1:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){                  

                APP_LE_SETVISIBLE(devices[DEV1].deviceLabel, LE_TRUE);           
                APP_LE_SETVISIBLE(devices[DEV2].deviceLabel, LE_TRUE);               
             
                appScreenMLMonitorState = ML_MONITOR_ANIM_DONE;                 
            }
            break;
        }
        
        case ML_MONITOR_ANIM_DONE:
        {
            char temp_arr[2]="25";
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){
            
                APP_LE_SETVISIBLE(Screen2_ImageWidget_CelsiusNode1,LE_TRUE);
                APP_LE_SETVISIBLE(Screen2_ImageWidget_CelsiusNode2,LE_TRUE);
                APP_LE_SETVISIBLE(Screen2_ButtonWidget_Setlimit,LE_TRUE);           
                

                SYS_TIME_TimerStop(mlMonitorAnimTimer);
                MLMonitor_UpdateStatusString(temp_arr,1);
                MLMonitor_UpdateStatusString(temp_arr,2);
                SYS_TIME_TimerStart(mlUpdateTimer); 
                

                appScreenMLMonitorState =ML_MONITOR_WAIT;

                currentDevice = DEV1;
            }            
            break;
        }
        
        case ML_MONITOR_TEMP_UPDATE:
        {
            app_bleData.state =APP_BLE_STATE_FETCH_NODE1_TEMP;
            appScreenMLMonitorState =ML_MONITOR_WAIT;            
            break;
        }
        
        case ML_MONITOR_TEMP1_SCREEN_WRITE:
        {
            MLMonitor_UpdateStatusString(&sensorTemp1[2],1);
            appScreenMLMonitorState =ML_MONITOR_WAIT;
            break;
        }
        
        case ML_MONITOR_TEMP2_SCREEN_WRITE:
        {
            MLMonitor_UpdateStatusString(temperatureSTRING,2);
            appScreenMLMonitorState =ML_MONITOR_WAIT;
            break;
        }  
        case ML_SET_LIMIT:
        {            
            legato_showScreen(screenID_Screen3);  
            app_bleData.state = APP_BLE_STATE_WAIT;
        }
        break;        

     
        case ML_MONITOR_WAIT:                
        default:
            break;
    }
}


static void MLMonitor_InitDeviceTable(void)
{
    devices[DEV1] = (ML_MONITOR_DEVICE)
    {   .deviceImage = Screen2_ImageWidget_TempNode1, 
        .deviceLabel = Screen2_LabelWidget_Temp_Node1,
        .deviceVal = Screen2_TextFieldWidget_TempNode1,
    };
    
    devices[DEV1].xpos = APP_LE_GETX(devices[DEV1].deviceImage);
    devices[DEV1].ypos = APP_LE_GETY(devices[DEV1].deviceImage);

    devices[DEV2] = (ML_MONITOR_DEVICE)
    {   .deviceImage = Screen2_ImageWidget_TempNode2, 
        .deviceLabel = Screen2_LabelWidget_Temp_Node2,
        .deviceVal = Screen2_TextFieldWidget_TempNode2,
    };
    
    devices[DEV2].xpos = APP_LE_GETX(devices[DEV2].deviceImage);
    devices[DEV2].ypos = APP_LE_GETY(devices[DEV2].deviceImage);      
}

static void MLMonitor_UpdateStatusString(char * str,uint8_t node)
{
    if (strlen(str) > MAX_TEXT_LENGTH)
        return;
    
    statusStr1.fn->setFromCStr(&statusStr1, str);
    
    if(node==1){
        APP_LE_SETTEXTSTRING(Screen2_TextFieldWidget_TempNode1, statusStr1);
    } else if(node==2)
        APP_LE_SETTEXTSTRING(Screen2_TextFieldWidget_TempNode2, statusStr1);
    
}

/*******************************************************************************
 End of File
 */
