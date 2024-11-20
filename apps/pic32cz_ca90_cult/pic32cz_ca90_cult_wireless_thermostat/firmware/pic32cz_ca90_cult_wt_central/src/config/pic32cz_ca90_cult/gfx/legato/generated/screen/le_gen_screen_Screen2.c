#include "gfx/legato/generated/screen/le_gen_screen_Screen2.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen2_MultiNode_TempMonitor;
leWidget* Screen2_Multimonitorbackground;
leImageWidget* Screen2_ImageWidget_TempNode1;
leImageWidget* Screen2_ImageWidget_TempNode2;
leButtonWidget* Screen2_ButtonWidget_Setlimit;
leImageWidget* Screen2_ImageWidget_CelsiusNode1;
leImageWidget* Screen2_ImageWidget_CelsiusNode2;
leLabelWidget* Screen2_LabelWidget_Temp_Node1;
leTextFieldWidget* Screen2_TextFieldWidget_TempNode1;
leLabelWidget* Screen2_LabelWidget_Temp_Node2;
leTextFieldWidget* Screen2_TextFieldWidget_TempNode2;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen2(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen2(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, 480, 272);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    Screen2_MultiNode_TempMonitor = leWidget_New();
    Screen2_MultiNode_TempMonitor->fn->setPosition(Screen2_MultiNode_TempMonitor, 0, 0);
    Screen2_MultiNode_TempMonitor->fn->setSize(Screen2_MultiNode_TempMonitor, 480, 272);
    Screen2_MultiNode_TempMonitor->fn->setScheme(Screen2_MultiNode_TempMonitor, &Scheme1);
    root0->fn->addChild(root0, (leWidget*)Screen2_MultiNode_TempMonitor);

    Screen2_Multimonitorbackground = leWidget_New();
    Screen2_Multimonitorbackground->fn->setPosition(Screen2_Multimonitorbackground, 0, -2);
    Screen2_Multimonitorbackground->fn->setSize(Screen2_Multimonitorbackground, 480, 272);
    Screen2_Multimonitorbackground->fn->setScheme(Screen2_Multimonitorbackground, &Scheme1);
    root0->fn->addChild(root0, (leWidget*)Screen2_Multimonitorbackground);

    Screen2_ImageWidget_TempNode1 = leImageWidget_New();
    Screen2_ImageWidget_TempNode1->fn->setPosition(Screen2_ImageWidget_TempNode1, 68, 29);
    Screen2_ImageWidget_TempNode1->fn->setScheme(Screen2_ImageWidget_TempNode1, &Scheme1);
    Screen2_ImageWidget_TempNode1->fn->setBorderType(Screen2_ImageWidget_TempNode1, LE_WIDGET_BORDER_NONE);
    Screen2_ImageWidget_TempNode1->fn->setImage(Screen2_ImageWidget_TempNode1, (leImage*)&DeviceNode_select_bmp);
    root0->fn->addChild(root0, (leWidget*)Screen2_ImageWidget_TempNode1);

    Screen2_LabelWidget_Temp_Node1 = leLabelWidget_New();
    Screen2_LabelWidget_Temp_Node1->fn->setPosition(Screen2_LabelWidget_Temp_Node1, 21, 20);
    Screen2_LabelWidget_Temp_Node1->fn->setSize(Screen2_LabelWidget_Temp_Node1, 15, 18);
    Screen2_LabelWidget_Temp_Node1->fn->setScheme(Screen2_LabelWidget_Temp_Node1, &Scheme1);
    Screen2_LabelWidget_Temp_Node1->fn->setBackgroundType(Screen2_LabelWidget_Temp_Node1, LE_WIDGET_BACKGROUND_NONE);
    Screen2_LabelWidget_Temp_Node1->fn->setString(Screen2_LabelWidget_Temp_Node1, (leString*)&string_Node1);
    Screen2_ImageWidget_TempNode1->fn->addChild(Screen2_ImageWidget_TempNode1, (leWidget*)Screen2_LabelWidget_Temp_Node1);

    Screen2_TextFieldWidget_TempNode1 = leTextFieldWidget_New();
    Screen2_TextFieldWidget_TempNode1->fn->setPosition(Screen2_TextFieldWidget_TempNode1, 36, 42);
    Screen2_TextFieldWidget_TempNode1->fn->setSize(Screen2_TextFieldWidget_TempNode1, 46, 27);
    Screen2_TextFieldWidget_TempNode1->fn->setScheme(Screen2_TextFieldWidget_TempNode1, &Scheme1);
    Screen2_TextFieldWidget_TempNode1->fn->setBackgroundType(Screen2_TextFieldWidget_TempNode1, LE_WIDGET_BACKGROUND_NONE);
    Screen2_TextFieldWidget_TempNode1->fn->setBorderType(Screen2_TextFieldWidget_TempNode1, LE_WIDGET_BORDER_NONE);
    Screen2_TextFieldWidget_TempNode1->fn->setHAlignment(Screen2_TextFieldWidget_TempNode1, LE_HALIGN_LEFT);
    Screen2_TextFieldWidget_TempNode1->fn->setString(Screen2_TextFieldWidget_TempNode1, (leString*)&string_Default_Temp);
    Screen2_TextFieldWidget_TempNode1->fn->setHintString(Screen2_TextFieldWidget_TempNode1, (leString*)&string_Default_Temp);
    Screen2_TextFieldWidget_TempNode1->fn->setFont(Screen2_TextFieldWidget_TempNode1, (leFont*)&Font2);
    Screen2_ImageWidget_TempNode1->fn->addChild(Screen2_ImageWidget_TempNode1, (leWidget*)Screen2_TextFieldWidget_TempNode1);

    Screen2_ImageWidget_TempNode2 = leImageWidget_New();
    Screen2_ImageWidget_TempNode2->fn->setPosition(Screen2_ImageWidget_TempNode2, 297, 40);
    Screen2_ImageWidget_TempNode2->fn->setSize(Screen2_ImageWidget_TempNode2, 78, 83);
    Screen2_ImageWidget_TempNode2->fn->setScheme(Screen2_ImageWidget_TempNode2, &Scheme1);
    Screen2_ImageWidget_TempNode2->fn->setBorderType(Screen2_ImageWidget_TempNode2, LE_WIDGET_BORDER_NONE);
    Screen2_ImageWidget_TempNode2->fn->setImage(Screen2_ImageWidget_TempNode2, (leImage*)&DeviceNode_select_bmp);
    root0->fn->addChild(root0, (leWidget*)Screen2_ImageWidget_TempNode2);

    Screen2_LabelWidget_Temp_Node2 = leLabelWidget_New();
    Screen2_LabelWidget_Temp_Node2->fn->setPosition(Screen2_LabelWidget_Temp_Node2, 11, 11);
    Screen2_LabelWidget_Temp_Node2->fn->setSize(Screen2_LabelWidget_Temp_Node2, 15, 17);
    Screen2_LabelWidget_Temp_Node2->fn->setScheme(Screen2_LabelWidget_Temp_Node2, &Scheme1);
    Screen2_LabelWidget_Temp_Node2->fn->setString(Screen2_LabelWidget_Temp_Node2, (leString*)&string_Node2);
    Screen2_ImageWidget_TempNode2->fn->addChild(Screen2_ImageWidget_TempNode2, (leWidget*)Screen2_LabelWidget_Temp_Node2);

    Screen2_TextFieldWidget_TempNode2 = leTextFieldWidget_New();
    Screen2_TextFieldWidget_TempNode2->fn->setPosition(Screen2_TextFieldWidget_TempNode2, 24, 31);
    Screen2_TextFieldWidget_TempNode2->fn->setSize(Screen2_TextFieldWidget_TempNode2, 45, 28);
    Screen2_TextFieldWidget_TempNode2->fn->setScheme(Screen2_TextFieldWidget_TempNode2, &Scheme1);
    Screen2_TextFieldWidget_TempNode2->fn->setBackgroundType(Screen2_TextFieldWidget_TempNode2, LE_WIDGET_BACKGROUND_NONE);
    Screen2_TextFieldWidget_TempNode2->fn->setBorderType(Screen2_TextFieldWidget_TempNode2, LE_WIDGET_BORDER_NONE);
    Screen2_TextFieldWidget_TempNode2->fn->setHAlignment(Screen2_TextFieldWidget_TempNode2, LE_HALIGN_LEFT);
    Screen2_TextFieldWidget_TempNode2->fn->setString(Screen2_TextFieldWidget_TempNode2, (leString*)&string_Default_Temp);
    Screen2_TextFieldWidget_TempNode2->fn->setHintString(Screen2_TextFieldWidget_TempNode2, (leString*)&string_Default_Temp);
    Screen2_TextFieldWidget_TempNode2->fn->setFont(Screen2_TextFieldWidget_TempNode2, (leFont*)&Font2);
    Screen2_ImageWidget_TempNode2->fn->addChild(Screen2_ImageWidget_TempNode2, (leWidget*)Screen2_TextFieldWidget_TempNode2);

    Screen2_ButtonWidget_Setlimit = leButtonWidget_New();
    Screen2_ButtonWidget_Setlimit->fn->setPosition(Screen2_ButtonWidget_Setlimit, 143, 154);
    Screen2_ButtonWidget_Setlimit->fn->setSize(Screen2_ButtonWidget_Setlimit, 162, 77);
    Screen2_ButtonWidget_Setlimit->fn->setScheme(Screen2_ButtonWidget_Setlimit, &Scheme1);
    Screen2_ButtonWidget_Setlimit->fn->setString(Screen2_ButtonWidget_Setlimit, (leString*)&string_SetThreshold);
    Screen2_ButtonWidget_Setlimit->fn->setPressedEventCallback(Screen2_ButtonWidget_Setlimit, event_Screen2_ButtonWidget_Setlimit_OnPressed);
    Screen2_ButtonWidget_Setlimit->fn->setReleasedEventCallback(Screen2_ButtonWidget_Setlimit, event_Screen2_ButtonWidget_Setlimit_OnReleased);
    root0->fn->addChild(root0, (leWidget*)Screen2_ButtonWidget_Setlimit);

    Screen2_ImageWidget_CelsiusNode1 = leImageWidget_New();
    Screen2_ImageWidget_CelsiusNode1->fn->setPosition(Screen2_ImageWidget_CelsiusNode1, 162, 42);
    Screen2_ImageWidget_CelsiusNode1->fn->setSize(Screen2_ImageWidget_CelsiusNode1, 36, 45);
    Screen2_ImageWidget_CelsiusNode1->fn->setScheme(Screen2_ImageWidget_CelsiusNode1, &Scheme1);
    Screen2_ImageWidget_CelsiusNode1->fn->setBackgroundType(Screen2_ImageWidget_CelsiusNode1, LE_WIDGET_BACKGROUND_NONE);
    Screen2_ImageWidget_CelsiusNode1->fn->setBorderType(Screen2_ImageWidget_CelsiusNode1, LE_WIDGET_BORDER_NONE);
    Screen2_ImageWidget_CelsiusNode1->fn->setImage(Screen2_ImageWidget_CelsiusNode1, (leImage*)&celsius_deg);
    root0->fn->addChild(root0, (leWidget*)Screen2_ImageWidget_CelsiusNode1);

    Screen2_ImageWidget_CelsiusNode2 = leImageWidget_New();
    Screen2_ImageWidget_CelsiusNode2->fn->setPosition(Screen2_ImageWidget_CelsiusNode2, 376, 34);
    Screen2_ImageWidget_CelsiusNode2->fn->setSize(Screen2_ImageWidget_CelsiusNode2, 75, 64);
    Screen2_ImageWidget_CelsiusNode2->fn->setScheme(Screen2_ImageWidget_CelsiusNode2, &Scheme1);
    Screen2_ImageWidget_CelsiusNode2->fn->setBackgroundType(Screen2_ImageWidget_CelsiusNode2, LE_WIDGET_BACKGROUND_NONE);
    Screen2_ImageWidget_CelsiusNode2->fn->setBorderType(Screen2_ImageWidget_CelsiusNode2, LE_WIDGET_BORDER_NONE);
    Screen2_ImageWidget_CelsiusNode2->fn->setImage(Screen2_ImageWidget_CelsiusNode2, (leImage*)&celsius_deg);
    root0->fn->addChild(root0, (leWidget*)Screen2_ImageWidget_CelsiusNode2);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen2_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen2(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen2_OnUpdate(); // raise event
}

void screenHide_Screen2(void)
{
    Screen2_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen2_MultiNode_TempMonitor = NULL;
    Screen2_Multimonitorbackground = NULL;
    Screen2_ImageWidget_TempNode1 = NULL;
    Screen2_ImageWidget_TempNode2 = NULL;
    Screen2_ButtonWidget_Setlimit = NULL;
    Screen2_ImageWidget_CelsiusNode1 = NULL;
    Screen2_ImageWidget_CelsiusNode2 = NULL;
    Screen2_LabelWidget_Temp_Node1 = NULL;
    Screen2_TextFieldWidget_TempNode1 = NULL;
    Screen2_LabelWidget_Temp_Node2 = NULL;
    Screen2_TextFieldWidget_TempNode2 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen2(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen2(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        default:
        {
            return NULL;
        }
    }
}

