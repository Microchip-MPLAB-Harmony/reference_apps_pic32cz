#include "gfx/legato/generated/screen/le_gen_screen_Screen3.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen3_MultiNode_TempLimitPanel;
leImageWidget* Screen3_ImageWidget_LimitNode1;
leImageWidget* Screen3_ImageWidget_LimitNode2;
leButtonWidget* Screen3_ButtonWidget_Back;
leButtonWidget* Screen3_ButtonWidget_Enterlimit;
leButtonWidget* Screen3_ButtonWidget_IncNode1;
leButtonWidget* Screen3_ButtonWidget_IncNode2;
leButtonWidget* Screen3_ButtonWidget_DecNode1;
leButtonWidget* Screen3_ButtonWidget_DecNode2;
leTextFieldWidget* Screen3_TextFieldWidget_Limit1;
leTextFieldWidget* Screen3_TextFieldWidget_Limit2;
leImageWidget* Screen3_ImageWidget_Celsius1;
leImageWidget* Screen3_ImageWidget_Celsius2;
leLabelWidget* Screen3_LabelWidget_TempLimitNode1;
leLabelWidget* Screen3_LabelWidget_TempLimitNode2;
leImageWidget* Screen3_ImageWidget_Back;
leImageWidget* Screen3_ImageWidget_Enterlimit;
leImageWidget* Screen3_ImageWidget_IncNode1;
leImageWidget* Screen3_ImageWidget_IncNode2;
leImageRotateWidget* Screen3_ImageWidget_DecNode1;
leImageRotateWidget* Screen3_ImageWidget_DecNode2;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen3(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen3(void)
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

    Screen3_MultiNode_TempLimitPanel = leWidget_New();
    Screen3_MultiNode_TempLimitPanel->fn->setPosition(Screen3_MultiNode_TempLimitPanel, 1, 1);
    Screen3_MultiNode_TempLimitPanel->fn->setSize(Screen3_MultiNode_TempLimitPanel, 480, 272);
    Screen3_MultiNode_TempLimitPanel->fn->setScheme(Screen3_MultiNode_TempLimitPanel, &Scheme1);
    root0->fn->addChild(root0, (leWidget*)Screen3_MultiNode_TempLimitPanel);

    Screen3_ImageWidget_LimitNode1 = leImageWidget_New();
    Screen3_ImageWidget_LimitNode1->fn->setPosition(Screen3_ImageWidget_LimitNode1, 77, 81);
    Screen3_ImageWidget_LimitNode1->fn->setSize(Screen3_ImageWidget_LimitNode1, 103, 93);
    Screen3_ImageWidget_LimitNode1->fn->setScheme(Screen3_ImageWidget_LimitNode1, &Scheme1);
    Screen3_ImageWidget_LimitNode1->fn->setBackgroundType(Screen3_ImageWidget_LimitNode1, LE_WIDGET_BACKGROUND_NONE);
    Screen3_ImageWidget_LimitNode1->fn->setBorderType(Screen3_ImageWidget_LimitNode1, LE_WIDGET_BORDER_NONE);
    Screen3_ImageWidget_LimitNode1->fn->setImage(Screen3_ImageWidget_LimitNode1, (leImage*)&DeviceNode_noselect);
    root0->fn->addChild(root0, (leWidget*)Screen3_ImageWidget_LimitNode1);

    Screen3_LabelWidget_TempLimitNode1 = leLabelWidget_New();
    Screen3_LabelWidget_TempLimitNode1->fn->setPosition(Screen3_LabelWidget_TempLimitNode1, 23, 18);
    Screen3_LabelWidget_TempLimitNode1->fn->setSize(Screen3_LabelWidget_TempLimitNode1, 15, 17);
    Screen3_LabelWidget_TempLimitNode1->fn->setScheme(Screen3_LabelWidget_TempLimitNode1, &Scheme1);
    Screen3_LabelWidget_TempLimitNode1->fn->setString(Screen3_LabelWidget_TempLimitNode1, (leString*)&string_Node1);
    Screen3_ImageWidget_LimitNode1->fn->addChild(Screen3_ImageWidget_LimitNode1, (leWidget*)Screen3_LabelWidget_TempLimitNode1);

    Screen3_ImageWidget_LimitNode2 = leImageWidget_New();
    Screen3_ImageWidget_LimitNode2->fn->setPosition(Screen3_ImageWidget_LimitNode2, 256, 75);
    Screen3_ImageWidget_LimitNode2->fn->setScheme(Screen3_ImageWidget_LimitNode2, &Scheme1);
    Screen3_ImageWidget_LimitNode2->fn->setBorderType(Screen3_ImageWidget_LimitNode2, LE_WIDGET_BORDER_NONE);
    Screen3_ImageWidget_LimitNode2->fn->setImage(Screen3_ImageWidget_LimitNode2, (leImage*)&DeviceNode_noselect);
    root0->fn->addChild(root0, (leWidget*)Screen3_ImageWidget_LimitNode2);

    Screen3_LabelWidget_TempLimitNode2 = leLabelWidget_New();
    Screen3_LabelWidget_TempLimitNode2->fn->setPosition(Screen3_LabelWidget_TempLimitNode2, 20, 21);
    Screen3_LabelWidget_TempLimitNode2->fn->setSize(Screen3_LabelWidget_TempLimitNode2, 17, 17);
    Screen3_LabelWidget_TempLimitNode2->fn->setScheme(Screen3_LabelWidget_TempLimitNode2, &Scheme1);
    Screen3_LabelWidget_TempLimitNode2->fn->setBackgroundType(Screen3_LabelWidget_TempLimitNode2, LE_WIDGET_BACKGROUND_NONE);
    Screen3_LabelWidget_TempLimitNode2->fn->setString(Screen3_LabelWidget_TempLimitNode2, (leString*)&string_Node2);
    Screen3_ImageWidget_LimitNode2->fn->addChild(Screen3_ImageWidget_LimitNode2, (leWidget*)Screen3_LabelWidget_TempLimitNode2);

    Screen3_ButtonWidget_Back = leButtonWidget_New();
    Screen3_ButtonWidget_Back->fn->setPosition(Screen3_ButtonWidget_Back, 2, 208);
    Screen3_ButtonWidget_Back->fn->setSize(Screen3_ButtonWidget_Back, 322, 64);
    Screen3_ButtonWidget_Back->fn->setScheme(Screen3_ButtonWidget_Back, &Scheme1);
    Screen3_ButtonWidget_Back->fn->setBorderType(Screen3_ButtonWidget_Back, LE_WIDGET_BORDER_NONE);
    Screen3_ButtonWidget_Back->fn->setString(Screen3_ButtonWidget_Back, (leString*)&string_Go_back);
    Screen3_ButtonWidget_Back->fn->setPressedEventCallback(Screen3_ButtonWidget_Back, event_Screen3_ButtonWidget_Back_OnPressed);
    root0->fn->addChild(root0, (leWidget*)Screen3_ButtonWidget_Back);

    Screen3_ImageWidget_Back = leImageWidget_New();
    Screen3_ImageWidget_Back->fn->setPosition(Screen3_ImageWidget_Back, -1, 6);
    Screen3_ImageWidget_Back->fn->setSize(Screen3_ImageWidget_Back, 65, 53);
    Screen3_ImageWidget_Back->fn->setScheme(Screen3_ImageWidget_Back, &Scheme1);
    Screen3_ImageWidget_Back->fn->setBorderType(Screen3_ImageWidget_Back, LE_WIDGET_BORDER_NONE);
    Screen3_ImageWidget_Back->fn->setImage(Screen3_ImageWidget_Back, (leImage*)&Back_button);
    Screen3_ButtonWidget_Back->fn->addChild(Screen3_ButtonWidget_Back, (leWidget*)Screen3_ImageWidget_Back);

    Screen3_ButtonWidget_Enterlimit = leButtonWidget_New();
    Screen3_ButtonWidget_Enterlimit->fn->setPosition(Screen3_ButtonWidget_Enterlimit, 384, 6);
    Screen3_ButtonWidget_Enterlimit->fn->setSize(Screen3_ButtonWidget_Enterlimit, 92, 106);
    Screen3_ButtonWidget_Enterlimit->fn->setScheme(Screen3_ButtonWidget_Enterlimit, &Scheme1);
    Screen3_ButtonWidget_Enterlimit->fn->setBorderType(Screen3_ButtonWidget_Enterlimit, LE_WIDGET_BORDER_NONE);
    Screen3_ButtonWidget_Enterlimit->fn->setPressedEventCallback(Screen3_ButtonWidget_Enterlimit, event_Screen3_ButtonWidget_Enterlimit_OnPressed);
    root0->fn->addChild(root0, (leWidget*)Screen3_ButtonWidget_Enterlimit);

    Screen3_ImageWidget_Enterlimit = leImageWidget_New();
    Screen3_ImageWidget_Enterlimit->fn->setPosition(Screen3_ImageWidget_Enterlimit, 10, 11);
    Screen3_ImageWidget_Enterlimit->fn->setSize(Screen3_ImageWidget_Enterlimit, 80, 96);
    Screen3_ImageWidget_Enterlimit->fn->setScheme(Screen3_ImageWidget_Enterlimit, &Scheme1);
    Screen3_ImageWidget_Enterlimit->fn->setBorderType(Screen3_ImageWidget_Enterlimit, LE_WIDGET_BORDER_NONE);
    Screen3_ImageWidget_Enterlimit->fn->setImage(Screen3_ImageWidget_Enterlimit, (leImage*)&Enter_limit);
    Screen3_ButtonWidget_Enterlimit->fn->addChild(Screen3_ButtonWidget_Enterlimit, (leWidget*)Screen3_ImageWidget_Enterlimit);

    Screen3_ButtonWidget_IncNode1 = leButtonWidget_New();
    Screen3_ButtonWidget_IncNode1->fn->setPosition(Screen3_ButtonWidget_IncNode1, 77, 41);
    Screen3_ButtonWidget_IncNode1->fn->setSize(Screen3_ButtonWidget_IncNode1, 102, 46);
    Screen3_ButtonWidget_IncNode1->fn->setScheme(Screen3_ButtonWidget_IncNode1, &Scheme1);
    Screen3_ButtonWidget_IncNode1->fn->setBorderType(Screen3_ButtonWidget_IncNode1, LE_WIDGET_BORDER_NONE);
    Screen3_ButtonWidget_IncNode1->fn->setPressedEventCallback(Screen3_ButtonWidget_IncNode1, event_Screen3_ButtonWidget_IncNode1_OnPressed);
    root0->fn->addChild(root0, (leWidget*)Screen3_ButtonWidget_IncNode1);

    Screen3_ImageWidget_IncNode1 = leImageWidget_New();
    Screen3_ImageWidget_IncNode1->fn->setPosition(Screen3_ImageWidget_IncNode1, 10, 3);
    Screen3_ImageWidget_IncNode1->fn->setSize(Screen3_ImageWidget_IncNode1, 79, 44);
    Screen3_ImageWidget_IncNode1->fn->setScheme(Screen3_ImageWidget_IncNode1, &Scheme1);
    Screen3_ImageWidget_IncNode1->fn->setBorderType(Screen3_ImageWidget_IncNode1, LE_WIDGET_BORDER_NONE);
    Screen3_ImageWidget_IncNode1->fn->setImage(Screen3_ImageWidget_IncNode1, (leImage*)&Up_arrow);
    Screen3_ButtonWidget_IncNode1->fn->addChild(Screen3_ButtonWidget_IncNode1, (leWidget*)Screen3_ImageWidget_IncNode1);

    Screen3_ButtonWidget_IncNode2 = leButtonWidget_New();
    Screen3_ButtonWidget_IncNode2->fn->setPosition(Screen3_ButtonWidget_IncNode2, 259, 44);
    Screen3_ButtonWidget_IncNode2->fn->setSize(Screen3_ButtonWidget_IncNode2, 96, 40);
    Screen3_ButtonWidget_IncNode2->fn->setScheme(Screen3_ButtonWidget_IncNode2, &Scheme1);
    Screen3_ButtonWidget_IncNode2->fn->setBorderType(Screen3_ButtonWidget_IncNode2, LE_WIDGET_BORDER_NONE);
    Screen3_ButtonWidget_IncNode2->fn->setPressedEventCallback(Screen3_ButtonWidget_IncNode2, event_Screen3_ButtonWidget_IncNode2_OnPressed);
    root0->fn->addChild(root0, (leWidget*)Screen3_ButtonWidget_IncNode2);

    Screen3_ImageWidget_IncNode2 = leImageWidget_New();
    Screen3_ImageWidget_IncNode2->fn->setPosition(Screen3_ImageWidget_IncNode2, 10, 3);
    Screen3_ImageWidget_IncNode2->fn->setSize(Screen3_ImageWidget_IncNode2, 76, 36);
    Screen3_ImageWidget_IncNode2->fn->setScheme(Screen3_ImageWidget_IncNode2, &Scheme1);
    Screen3_ImageWidget_IncNode2->fn->setBorderType(Screen3_ImageWidget_IncNode2, LE_WIDGET_BORDER_NONE);
    Screen3_ImageWidget_IncNode2->fn->setImage(Screen3_ImageWidget_IncNode2, (leImage*)&Up_arrow);
    Screen3_ButtonWidget_IncNode2->fn->addChild(Screen3_ButtonWidget_IncNode2, (leWidget*)Screen3_ImageWidget_IncNode2);

    Screen3_ButtonWidget_DecNode1 = leButtonWidget_New();
    Screen3_ButtonWidget_DecNode1->fn->setPosition(Screen3_ButtonWidget_DecNode1, 84, 167);
    Screen3_ButtonWidget_DecNode1->fn->setSize(Screen3_ButtonWidget_DecNode1, 101, 38);
    Screen3_ButtonWidget_DecNode1->fn->setScheme(Screen3_ButtonWidget_DecNode1, &Scheme1);
    Screen3_ButtonWidget_DecNode1->fn->setBorderType(Screen3_ButtonWidget_DecNode1, LE_WIDGET_BORDER_NONE);
    Screen3_ButtonWidget_DecNode1->fn->setPressedEventCallback(Screen3_ButtonWidget_DecNode1, event_Screen3_ButtonWidget_DecNode1_OnPressed);
    root0->fn->addChild(root0, (leWidget*)Screen3_ButtonWidget_DecNode1);

    Screen3_ImageWidget_DecNode1 = leImageRotateWidget_New();
    Screen3_ImageWidget_DecNode1->fn->setPosition(Screen3_ImageWidget_DecNode1, 6, 0);
    Screen3_ImageWidget_DecNode1->fn->setSize(Screen3_ImageWidget_DecNode1, 81, 38);
    Screen3_ImageWidget_DecNode1->fn->setScheme(Screen3_ImageWidget_DecNode1, &Scheme1);
    Screen3_ImageWidget_DecNode1->fn->setImage(Screen3_ImageWidget_DecNode1, (leImage*)&Up_arrow);
    Screen3_ImageWidget_DecNode1->fn->setAngle(Screen3_ImageWidget_DecNode1, 180);
    Screen3_ButtonWidget_DecNode1->fn->addChild(Screen3_ButtonWidget_DecNode1, (leWidget*)Screen3_ImageWidget_DecNode1);

    Screen3_ButtonWidget_DecNode2 = leButtonWidget_New();
    Screen3_ButtonWidget_DecNode2->fn->setPosition(Screen3_ButtonWidget_DecNode2, 266, 165);
    Screen3_ButtonWidget_DecNode2->fn->setSize(Screen3_ButtonWidget_DecNode2, 97, 35);
    Screen3_ButtonWidget_DecNode2->fn->setScheme(Screen3_ButtonWidget_DecNode2, &Scheme1);
    Screen3_ButtonWidget_DecNode2->fn->setBorderType(Screen3_ButtonWidget_DecNode2, LE_WIDGET_BORDER_NONE);
    Screen3_ButtonWidget_DecNode2->fn->setPressedEventCallback(Screen3_ButtonWidget_DecNode2, event_Screen3_ButtonWidget_DecNode2_OnPressed);
    root0->fn->addChild(root0, (leWidget*)Screen3_ButtonWidget_DecNode2);

    Screen3_ImageWidget_DecNode2 = leImageRotateWidget_New();
    Screen3_ImageWidget_DecNode2->fn->setPosition(Screen3_ImageWidget_DecNode2, -4, 6);
    Screen3_ImageWidget_DecNode2->fn->setSize(Screen3_ImageWidget_DecNode2, 95, 31);
    Screen3_ImageWidget_DecNode2->fn->setScheme(Screen3_ImageWidget_DecNode2, &Scheme1);
    Screen3_ImageWidget_DecNode2->fn->setImage(Screen3_ImageWidget_DecNode2, (leImage*)&Up_arrow);
    Screen3_ImageWidget_DecNode2->fn->setAngle(Screen3_ImageWidget_DecNode2, 180);
    Screen3_ButtonWidget_DecNode2->fn->addChild(Screen3_ButtonWidget_DecNode2, (leWidget*)Screen3_ImageWidget_DecNode2);

    Screen3_TextFieldWidget_Limit1 = leTextFieldWidget_New();
    Screen3_TextFieldWidget_Limit1->fn->setPosition(Screen3_TextFieldWidget_Limit1, 115, 112);
    Screen3_TextFieldWidget_Limit1->fn->setSize(Screen3_TextFieldWidget_Limit1, 35, 32);
    Screen3_TextFieldWidget_Limit1->fn->setScheme(Screen3_TextFieldWidget_Limit1, &Scheme1);
    Screen3_TextFieldWidget_Limit1->fn->setBackgroundType(Screen3_TextFieldWidget_Limit1, LE_WIDGET_BACKGROUND_NONE);
    Screen3_TextFieldWidget_Limit1->fn->setBorderType(Screen3_TextFieldWidget_Limit1, LE_WIDGET_BORDER_NONE);
    Screen3_TextFieldWidget_Limit1->fn->setHAlignment(Screen3_TextFieldWidget_Limit1, LE_HALIGN_LEFT);
    Screen3_TextFieldWidget_Limit1->fn->setString(Screen3_TextFieldWidget_Limit1, (leString*)&string_Default_Temp);
    Screen3_TextFieldWidget_Limit1->fn->setHintString(Screen3_TextFieldWidget_Limit1, (leString*)&string_Default_Temp);
    Screen3_TextFieldWidget_Limit1->fn->setFont(Screen3_TextFieldWidget_Limit1, (leFont*)&Font2);
    root0->fn->addChild(root0, (leWidget*)Screen3_TextFieldWidget_Limit1);

    Screen3_TextFieldWidget_Limit2 = leTextFieldWidget_New();
    Screen3_TextFieldWidget_Limit2->fn->setPosition(Screen3_TextFieldWidget_Limit2, 290, 112);
    Screen3_TextFieldWidget_Limit2->fn->setSize(Screen3_TextFieldWidget_Limit2, 40, 33);
    Screen3_TextFieldWidget_Limit2->fn->setScheme(Screen3_TextFieldWidget_Limit2, &Scheme1);
    Screen3_TextFieldWidget_Limit2->fn->setBackgroundType(Screen3_TextFieldWidget_Limit2, LE_WIDGET_BACKGROUND_NONE);
    Screen3_TextFieldWidget_Limit2->fn->setBorderType(Screen3_TextFieldWidget_Limit2, LE_WIDGET_BORDER_NONE);
    Screen3_TextFieldWidget_Limit2->fn->setHAlignment(Screen3_TextFieldWidget_Limit2, LE_HALIGN_LEFT);
    Screen3_TextFieldWidget_Limit2->fn->setString(Screen3_TextFieldWidget_Limit2, (leString*)&string_Default_Temp);
    Screen3_TextFieldWidget_Limit2->fn->setHintString(Screen3_TextFieldWidget_Limit2, (leString*)&string_Default_Temp);
    Screen3_TextFieldWidget_Limit2->fn->setFont(Screen3_TextFieldWidget_Limit2, (leFont*)&Font2);
    root0->fn->addChild(root0, (leWidget*)Screen3_TextFieldWidget_Limit2);

    Screen3_ImageWidget_Celsius1 = leImageWidget_New();
    Screen3_ImageWidget_Celsius1->fn->setPosition(Screen3_ImageWidget_Celsius1, 169, 95);
    Screen3_ImageWidget_Celsius1->fn->setSize(Screen3_ImageWidget_Celsius1, 38, 43);
    Screen3_ImageWidget_Celsius1->fn->setScheme(Screen3_ImageWidget_Celsius1, &Scheme1);
    Screen3_ImageWidget_Celsius1->fn->setBorderType(Screen3_ImageWidget_Celsius1, LE_WIDGET_BORDER_NONE);
    Screen3_ImageWidget_Celsius1->fn->setImage(Screen3_ImageWidget_Celsius1, (leImage*)&celsius_deg);
    root0->fn->addChild(root0, (leWidget*)Screen3_ImageWidget_Celsius1);

    Screen3_ImageWidget_Celsius2 = leImageWidget_New();
    Screen3_ImageWidget_Celsius2->fn->setPosition(Screen3_ImageWidget_Celsius2, 343, 87);
    Screen3_ImageWidget_Celsius2->fn->setSize(Screen3_ImageWidget_Celsius2, 52, 55);
    Screen3_ImageWidget_Celsius2->fn->setScheme(Screen3_ImageWidget_Celsius2, &Scheme1);
    Screen3_ImageWidget_Celsius2->fn->setBorderType(Screen3_ImageWidget_Celsius2, LE_WIDGET_BORDER_NONE);
    Screen3_ImageWidget_Celsius2->fn->setImage(Screen3_ImageWidget_Celsius2, (leImage*)&celsius_deg);
    root0->fn->addChild(root0, (leWidget*)Screen3_ImageWidget_Celsius2);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen3_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen3(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen3_OnUpdate(); // raise event
}

void screenHide_Screen3(void)
{
    Screen3_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen3_MultiNode_TempLimitPanel = NULL;
    Screen3_ImageWidget_LimitNode1 = NULL;
    Screen3_ImageWidget_LimitNode2 = NULL;
    Screen3_ButtonWidget_Back = NULL;
    Screen3_ButtonWidget_Enterlimit = NULL;
    Screen3_ButtonWidget_IncNode1 = NULL;
    Screen3_ButtonWidget_IncNode2 = NULL;
    Screen3_ButtonWidget_DecNode1 = NULL;
    Screen3_ButtonWidget_DecNode2 = NULL;
    Screen3_TextFieldWidget_Limit1 = NULL;
    Screen3_TextFieldWidget_Limit2 = NULL;
    Screen3_ImageWidget_Celsius1 = NULL;
    Screen3_ImageWidget_Celsius2 = NULL;
    Screen3_LabelWidget_TempLimitNode1 = NULL;
    Screen3_LabelWidget_TempLimitNode2 = NULL;
    Screen3_ImageWidget_Back = NULL;
    Screen3_ImageWidget_Enterlimit = NULL;
    Screen3_ImageWidget_IncNode1 = NULL;
    Screen3_ImageWidget_IncNode2 = NULL;
    Screen3_ImageWidget_DecNode1 = NULL;
    Screen3_ImageWidget_DecNode2 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen3(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen3(uint32_t lyrIdx)
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

