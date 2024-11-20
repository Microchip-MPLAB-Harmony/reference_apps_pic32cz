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
    app_screen3_setlimit.c

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

#include "app_screen3_setlimit.h"
#include "gfx/legato/generated/le_gen_init.h"
#include "gfx/legato/generated/screen/le_gen_screen_Screen3.h"
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


#define MULTILINK_NUM_DEVICES 2 
#define DEVICE_ICON_POSX_HIDE_LEFT -80
#define DEVICE_ICON_POSX_HIDE_RIGHT 480
#define DEVICE_ANIM_COEFF 3
#define CONNECT_POSY_HIDE_BOTTOM 320

#define MAX_STATUS_LABEL_LENGTH 24
#define MAX_TEXT_LENGTH 3

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
    leImageWidget * deviceIncImage;
    leButtonWidget* deviceIncButton;
    leImageRotateWidget * deviceDecImage;
    leButtonWidget* deviceDecButton;
    uint32_t xpos;
    uint32_t ypos;  
} ML_SETLIMIT_DEVICE;

static uint8_t defaultTemperature=25; // Initial Temperature set to default 25°C
static uint8_t SetTempN1,SetTempN2;
APP_SCREEN3_SETLIMIT_DATA app_screen3_setlimit;
static APP_BLE_DEVICE_ID currentDevice = DEV1;
static ML_SETLIMIT_DEVICE devices[MULTILINK_NUM_DEVICES] = {0};

static SYS_TIME_HANDLE mlSetLimitAnimTimer = SYS_TIME_HANDLE_INVALID;
static volatile uint32_t mlSetLimitAnimTickCount = 0;
static uint32_t mlSetLimitAnimTickPrev = 0;

static void MLSetlimitAnimTimer_Callback (uintptr_t context);
static void MLSetLimit_InitDeviceTable(void);
static void MLSetLimit_UpdateTemperature(uint8_t val,uint8_t node);

static leFixedString statusStr1;
static leChar statusStrBuff1[MAX_TEXT_LENGTH] = {0};

extern volatile bool bleConnect_Ready;

extern APP_BLE_DATA app_bleData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static void MLSetlimitAnimTimer_Callback (uintptr_t context)
{
    mlSetLimitAnimTickCount++;
}


void event_Screen3_ButtonWidget_Back_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_Screen2);
}

void event_Screen3_ButtonWidget_Enterlimit_OnPressed(leButtonWidget* btn)
{
    if(currentDevice == DEV1){
        appScreenMLSetLimitState = ML_SETLIMIT_FEEDBACK_NODE1;
    } else if(currentDevice == DEV2)
        appScreenMLSetLimitState =ML_SETLIMIT_FEEDBACK_NODE2;
}

void event_Screen3_ButtonWidget_IncNode1_OnPressed(leButtonWidget* btn)
{
    currentDevice = DEV1;
    SetTempN1++;
    MLSetLimit_UpdateTemperature(SetTempN1,1);
}
void event_Screen3_ButtonWidget_IncNode2_OnPressed(leButtonWidget* btn)
{
    currentDevice = DEV2;
    SetTempN2++;
    MLSetLimit_UpdateTemperature(SetTempN2,2);
}

void event_Screen3_ButtonWidget_DecNode1_OnPressed(leButtonWidget* btn)
{
    currentDevice = DEV1;
    SetTempN1--;
    MLSetLimit_UpdateTemperature(SetTempN1,1);
}
void event_Screen3_ButtonWidget_DecNode2_OnPressed(leButtonWidget* btn)
{
    currentDevice = DEV2;
    SetTempN2--;
    MLSetLimit_UpdateTemperature(SetTempN2,2);
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


void Screen3_OnShow()
{
    appScreenMLSetLimitState= ML_SETLIMIT_INIT;    
    
    MLSetLimit_InitDeviceTable();
    
    leFixedString_Constructor(&statusStr1, statusStrBuff1, MAX_TEXT_LENGTH);
    
    
    statusStr1.fn->setFont(&statusStr1, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              string_Default_Temp.index,
                                                              0));
    
    APP_LE_SETX(devices[DEV1].deviceImage, DEVICE_ICON_POSX_HIDE_LEFT);
    APP_LE_SETX(devices[DEV2].deviceImage, DEVICE_ICON_POSX_HIDE_RIGHT);
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceVal, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceVal, LE_FALSE);
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceLabel, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceLabel, LE_FALSE);   
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceIncImage, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceIncImage, LE_FALSE);  
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceIncButton, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceIncButton, LE_FALSE);  
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceDecImage, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceDecImage, LE_FALSE); 
    
    APP_LE_SETVISIBLE(devices[DEV1].deviceDecButton, LE_FALSE);
    APP_LE_SETVISIBLE(devices[DEV2].deviceDecButton, LE_FALSE);
    
    APP_LE_SETVISIBLE(Screen3_ImageWidget_Celsius1,LE_FALSE);
    APP_LE_SETVISIBLE(Screen3_ImageWidget_Celsius2,LE_FALSE);
    APP_LE_SETVISIBLE(Screen3_ButtonWidget_Back,LE_FALSE);
    APP_LE_SETVISIBLE(Screen3_ButtonWidget_Enterlimit,LE_FALSE);    
    APP_LE_SETVISIBLE(Screen3_ImageWidget_Back,LE_FALSE);
    APP_LE_SETVISIBLE(Screen3_ImageWidget_Enterlimit,LE_FALSE); 
    
    SetTempN1 = defaultTemperature;
    SetTempN2 = defaultTemperature;
    
    mlSetLimitAnimTickCount = 0;
    mlSetLimitAnimTimer = SYS_TIME_CallbackRegisterMS(MLSetlimitAnimTimer_Callback,
                                                     1, ANIM_TIMER_TICK_PERIOD_MS,
                                                     SYS_TIME_PERIODIC);  
            
    SYS_TIME_TimerStop(mlSetLimitAnimTimer);   
}

void Screen3_OnHide()
{    
    mlSetLimitAnimTickCount=0;
    
    SYS_TIME_TimerDestroy(mlSetLimitAnimTimer);
   
    appScreenMLSetLimitState = ML_SETLIMIT_INIT;
    
}

void Screen3_OnUpdate(){
    
    switch (appScreenMLSetLimitState) {
        case ML_SETLIMIT_INIT:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0) {      
                
                currentDevice = DEV1;
               
                SYS_TIME_TimerStart(mlSetLimitAnimTimer);    
            
                appScreenMLSetLimitState =ML_SETLIMIT_ANIM0;               
               
            }
            break;
        }
        case ML_SETLIMIT_ANIM0:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){                     
            
            if (mlSetLimitAnimTickCount != mlSetLimitAnimTickPrev)
            {
                int32_t xpos = APP_LE_GETX(devices[DEV1].deviceImage);
                int32_t deltaX = (devices[DEV1].xpos - xpos) / DEVICE_ANIM_COEFF;
                
                appScreenMLSetLimitState =ML_SETLIMIT_ANIM1;                
                
                if (deltaX > 0)
                {
                    APP_LE_SETX(devices[DEV1].deviceImage, xpos + deltaX);
                    
                    appScreenMLSetLimitState =ML_SETLIMIT_ANIM0;
                }
                else
                {
                    APP_LE_SETX(devices[DEV1].deviceImage, devices[DEV1].xpos);
                }
                
                xpos = APP_LE_GETX(devices[DEV2].deviceImage);
                deltaX = (xpos - devices[DEV2].xpos) / DEVICE_ANIM_COEFF;
                
                if (deltaX > 0)
                {
                    appScreenMLSetLimitState =ML_SETLIMIT_ANIM0;
                    
                    APP_LE_SETX(devices[DEV2].deviceImage, xpos - deltaX);
                }
                else
                {
                    APP_LE_SETX(devices[DEV2].deviceImage, devices[DEV2].xpos);
                }

                mlSetLimitAnimTickPrev = mlSetLimitAnimTickCount;
            }                      
            
            }
            break;
        }
        
        case ML_SETLIMIT_ANIM1:
        {
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){                  

                APP_LE_SETVISIBLE(devices[DEV1].deviceLabel, LE_TRUE);           
                APP_LE_SETVISIBLE(devices[DEV2].deviceLabel, LE_TRUE); 
                APP_LE_SETVISIBLE(devices[DEV1].deviceVal, LE_TRUE);
                APP_LE_SETVISIBLE(devices[DEV2].deviceVal, LE_TRUE);
              
                appScreenMLSetLimitState =ML_SETLIMIT_ANIM_DONE;                 
            }
            break;
        }
        
        case ML_SETLIMIT_ANIM_DONE:
        {           
            SYS_TIME_TimerStop(mlSetLimitAnimTimer);
            
            if (leRenderer_IsIdle() || leEvent_GetCount() == 0){
                
                APP_LE_SETVISIBLE(devices[DEV1].deviceIncImage, LE_TRUE);
                APP_LE_SETVISIBLE(devices[DEV2].deviceIncImage, LE_TRUE);  

                APP_LE_SETVISIBLE(devices[DEV1].deviceIncButton, LE_TRUE);
                APP_LE_SETVISIBLE(devices[DEV2].deviceIncButton, LE_TRUE);  

                APP_LE_SETVISIBLE(devices[DEV1].deviceDecImage, LE_TRUE);
                APP_LE_SETVISIBLE(devices[DEV2].deviceDecImage, LE_TRUE); 

                APP_LE_SETVISIBLE(devices[DEV1].deviceDecButton, LE_TRUE);
                APP_LE_SETVISIBLE(devices[DEV2].deviceDecButton, LE_TRUE);
            
                APP_LE_SETVISIBLE(Screen3_ImageWidget_Celsius1,LE_TRUE);
                APP_LE_SETVISIBLE(Screen3_ImageWidget_Celsius2,LE_TRUE);
                APP_LE_SETVISIBLE(Screen3_ImageWidget_Back,LE_TRUE);
                APP_LE_SETVISIBLE(Screen3_ImageWidget_Enterlimit,LE_TRUE);
                APP_LE_SETVISIBLE(Screen3_ButtonWidget_Back,LE_TRUE);
                APP_LE_SETVISIBLE(Screen3_ButtonWidget_Enterlimit,LE_TRUE);   

                
                MLSetLimit_UpdateTemperature(defaultTemperature,1);
                MLSetLimit_UpdateTemperature(defaultTemperature,2);               

                appScreenMLSetLimitState =ML_SETLIMIT_WAIT;

                currentDevice = DEV1;
            }            
            break;
        }
        
        case ML_SETLIMIT_FEEDBACK_NODE1:
        {
            app_bleData.state = APP_BLE_STATE_SEND_TEMP_LIMIT_N1;
            appScreenMLSetLimitState =ML_SETLIMIT_WAIT;
            break;
        }
        
        case ML_SETLIMIT_FEEDBACK_NODE2:
        {
            app_bleData.state = APP_BLE_STATE_SEND_TEMP_LIMIT_N2;
            appScreenMLSetLimitState =ML_SETLIMIT_WAIT;
            break;
        }
        
        case ML_SETLIMIT_WAIT:                
        default:
            break;
    }
}

static void MLSetLimit_InitDeviceTable(void)
{
    devices[DEV1] = (ML_SETLIMIT_DEVICE)
    {   .deviceImage = Screen3_ImageWidget_LimitNode1, 
        .deviceLabel = Screen3_LabelWidget_TempLimitNode1,
        .deviceVal = Screen3_TextFieldWidget_Limit1,
        .deviceIncImage = Screen3_ImageWidget_IncNode1,
        .deviceIncButton = Screen3_ButtonWidget_IncNode1,
        .deviceDecImage=Screen3_ImageWidget_DecNode1,
        .deviceDecButton=Screen3_ButtonWidget_DecNode1,
    };
    
    devices[DEV1].xpos = APP_LE_GETX(devices[DEV1].deviceImage);
    devices[DEV1].ypos = APP_LE_GETY(devices[DEV1].deviceImage);

    devices[DEV2] = (ML_SETLIMIT_DEVICE)
    {   .deviceImage = Screen3_ImageWidget_LimitNode2, 
        .deviceLabel = Screen3_LabelWidget_TempLimitNode2,
        .deviceVal = Screen3_TextFieldWidget_Limit2,
        .deviceIncImage = Screen3_ImageWidget_IncNode2,
        .deviceIncButton = Screen3_ButtonWidget_IncNode2,
        .deviceDecImage=Screen3_ImageWidget_DecNode2,
        .deviceDecButton=Screen3_ButtonWidget_DecNode2,
    };
    
    devices[DEV2].xpos = APP_LE_GETX(devices[DEV2].deviceImage);
    devices[DEV2].ypos = APP_LE_GETY(devices[DEV2].deviceImage);      
}

void getLimit(uint8_t * CutOff,uint8_t nodeIdx)
{
    if(nodeIdx==DEV1)
        *CutOff=SetTempN1;
    else if(nodeIdx==DEV2)
        *CutOff=SetTempN2;
}


static void MLSetLimit_UpdateTemperature(uint8_t val,uint8_t node)
{    
    char temperature[2];
    sprintf(temperature,"%d",val);
    if (strlen(temperature) > MAX_TEXT_LENGTH)
        return;
    statusStr1.fn->setFromCStr(&statusStr1, temperature);   
   
    if(node==1){
        APP_LE_SETTEXTSTRING(Screen3_TextFieldWidget_Limit1, statusStr1);
    } else if(node==2)
        APP_LE_SETTEXTSTRING(Screen3_TextFieldWidget_Limit2, statusStr1);    
}


/*******************************************************************************
 End of File
 */
