#include "gfx/legato/generated/screen/le_gen_screen_Screen0.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen0_SplashBackground;
leLabelWidget* Screen0_Label_DemoName;
leImageWidget* Screen0_ImageWidget_Thermostat;
leImageWidget* Screen0_SplashBar;
leImageWidget* Screen0_SplashMicrochipLogo;
leImageWidget* Screen0_ImageWidget_Mplab;
leImageWidget* Screen0_SplashPIC32Logo;
leButtonWidget* Screen0_ButtonWidget_Start;
leImageWidget* Screen0_ImageWidget_Wifilogo;
leImageWidget* Screen0_ImageWidget_Startimage;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen0(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen0(void)
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

    Screen0_SplashBackground = leWidget_New();
    Screen0_SplashBackground->fn->setPosition(Screen0_SplashBackground, 0, 0);
    Screen0_SplashBackground->fn->setSize(Screen0_SplashBackground, 480, 272);
    Screen0_SplashBackground->fn->setAlphaEnabled(Screen0_SplashBackground, LE_TRUE);
    Screen0_SplashBackground->fn->setScheme(Screen0_SplashBackground, &Scheme1);
    Screen0_SplashBackground->fn->setBorderType(Screen0_SplashBackground, LE_WIDGET_BORDER_BEVEL);
    root0->fn->addChild(root0, (leWidget*)Screen0_SplashBackground);

    Screen0_Label_DemoName = leLabelWidget_New();
    Screen0_Label_DemoName->fn->setPosition(Screen0_Label_DemoName, 90, 95);
    Screen0_Label_DemoName->fn->setSize(Screen0_Label_DemoName, 300, 74);
    Screen0_Label_DemoName->fn->setAlphaEnabled(Screen0_Label_DemoName, LE_TRUE);
    Screen0_Label_DemoName->fn->setScheme(Screen0_Label_DemoName, &Scheme1);
    Screen0_Label_DemoName->fn->setBackgroundType(Screen0_Label_DemoName, LE_WIDGET_BACKGROUND_NONE);
    Screen0_Label_DemoName->fn->setHAlignment(Screen0_Label_DemoName, LE_HALIGN_CENTER);
    Screen0_Label_DemoName->fn->setString(Screen0_Label_DemoName, (leString*)&string_Thermostat_demo);
    root0->fn->addChild(root0, (leWidget*)Screen0_Label_DemoName);

    Screen0_ImageWidget_Wifilogo = leImageWidget_New();
    Screen0_ImageWidget_Wifilogo->fn->setPosition(Screen0_ImageWidget_Wifilogo, 1, 8);
    Screen0_ImageWidget_Wifilogo->fn->setSize(Screen0_ImageWidget_Wifilogo, 24, 25);
    Screen0_ImageWidget_Wifilogo->fn->setScheme(Screen0_ImageWidget_Wifilogo, &Scheme1);
    Screen0_ImageWidget_Wifilogo->fn->setBackgroundType(Screen0_ImageWidget_Wifilogo, LE_WIDGET_BACKGROUND_NONE);
    Screen0_ImageWidget_Wifilogo->fn->setBorderType(Screen0_ImageWidget_Wifilogo, LE_WIDGET_BORDER_NONE);
    Screen0_ImageWidget_Wifilogo->fn->setImage(Screen0_ImageWidget_Wifilogo, (leImage*)&Image0);
    Screen0_Label_DemoName->fn->addChild(Screen0_Label_DemoName, (leWidget*)Screen0_ImageWidget_Wifilogo);

    Screen0_ImageWidget_Thermostat = leImageWidget_New();
    Screen0_ImageWidget_Thermostat->fn->setPosition(Screen0_ImageWidget_Thermostat, 383, 6);
    Screen0_ImageWidget_Thermostat->fn->setSize(Screen0_ImageWidget_Thermostat, 91, 113);
    Screen0_ImageWidget_Thermostat->fn->setScheme(Screen0_ImageWidget_Thermostat, &Scheme1);
    Screen0_ImageWidget_Thermostat->fn->setBorderType(Screen0_ImageWidget_Thermostat, LE_WIDGET_BORDER_NONE);
    Screen0_ImageWidget_Thermostat->fn->setImage(Screen0_ImageWidget_Thermostat, (leImage*)&Thermostat_resize_bmp);
    root0->fn->addChild(root0, (leWidget*)Screen0_ImageWidget_Thermostat);

    Screen0_SplashBar = leImageWidget_New();
    Screen0_SplashBar->fn->setPosition(Screen0_SplashBar, 481, 204);
    Screen0_SplashBar->fn->setSize(Screen0_SplashBar, 483, 69);
    Screen0_SplashBar->fn->setScheme(Screen0_SplashBar, &Scheme1);
    Screen0_SplashBar->fn->setBackgroundType(Screen0_SplashBar, LE_WIDGET_BACKGROUND_NONE);
    Screen0_SplashBar->fn->setBorderType(Screen0_SplashBar, LE_WIDGET_BORDER_NONE);
    Screen0_SplashBar->fn->setImage(Screen0_SplashBar, (leImage*)&MCHP_bar_bmp);
    root0->fn->addChild(root0, (leWidget*)Screen0_SplashBar);

    Screen0_SplashMicrochipLogo = leImageWidget_New();
    Screen0_SplashMicrochipLogo->fn->setPosition(Screen0_SplashMicrochipLogo, 321, 222);
    Screen0_SplashMicrochipLogo->fn->setSize(Screen0_SplashMicrochipLogo, 149, 36);
    Screen0_SplashMicrochipLogo->fn->setScheme(Screen0_SplashMicrochipLogo, &Scheme1);
    Screen0_SplashMicrochipLogo->fn->setBackgroundType(Screen0_SplashMicrochipLogo, LE_WIDGET_BACKGROUND_NONE);
    Screen0_SplashMicrochipLogo->fn->setBorderType(Screen0_SplashMicrochipLogo, LE_WIDGET_BORDER_NONE);
    Screen0_SplashMicrochipLogo->fn->setImage(Screen0_SplashMicrochipLogo, (leImage*)&MirochipLogo_bmp);
    root0->fn->addChild(root0, (leWidget*)Screen0_SplashMicrochipLogo);

    Screen0_ImageWidget_Mplab = leImageWidget_New();
    Screen0_ImageWidget_Mplab->fn->setPosition(Screen0_ImageWidget_Mplab, 4, 2);
    Screen0_ImageWidget_Mplab->fn->setSize(Screen0_ImageWidget_Mplab, 93, 97);
    Screen0_ImageWidget_Mplab->fn->setAlphaEnabled(Screen0_ImageWidget_Mplab, LE_TRUE);
    Screen0_ImageWidget_Mplab->fn->setScheme(Screen0_ImageWidget_Mplab, &Scheme1);
    Screen0_ImageWidget_Mplab->fn->setBorderType(Screen0_ImageWidget_Mplab, LE_WIDGET_BORDER_NONE);
    Screen0_ImageWidget_Mplab->fn->setImage(Screen0_ImageWidget_Mplab, (leImage*)&MPLAB_Graphics_logo);
    root0->fn->addChild(root0, (leWidget*)Screen0_ImageWidget_Mplab);

    Screen0_SplashPIC32Logo = leImageWidget_New();
    Screen0_SplashPIC32Logo->fn->setPosition(Screen0_SplashPIC32Logo, 0, 2);
    Screen0_SplashPIC32Logo->fn->setSize(Screen0_SplashPIC32Logo, 249, 94);
    Screen0_SplashPIC32Logo->fn->setAlphaEnabled(Screen0_SplashPIC32Logo, LE_TRUE);
    Screen0_SplashPIC32Logo->fn->setScheme(Screen0_SplashPIC32Logo, &Scheme1);
    Screen0_SplashPIC32Logo->fn->setBorderType(Screen0_SplashPIC32Logo, LE_WIDGET_BORDER_NONE);
    Screen0_SplashPIC32Logo->fn->setImage(Screen0_SplashPIC32Logo, (leImage*)&pic32logo_bmp);
    root0->fn->addChild(root0, (leWidget*)Screen0_SplashPIC32Logo);

    Screen0_ButtonWidget_Start = leButtonWidget_New();
    Screen0_ButtonWidget_Start->fn->setPosition(Screen0_ButtonWidget_Start, 180, 162);
    Screen0_ButtonWidget_Start->fn->setSize(Screen0_ButtonWidget_Start, 120, 45);
    Screen0_ButtonWidget_Start->fn->setScheme(Screen0_ButtonWidget_Start, &Scheme1);
    Screen0_ButtonWidget_Start->fn->setBackgroundType(Screen0_ButtonWidget_Start, LE_WIDGET_BACKGROUND_NONE);
    Screen0_ButtonWidget_Start->fn->setHAlignment(Screen0_ButtonWidget_Start, LE_HALIGN_LEFT);
    Screen0_ButtonWidget_Start->fn->setToggleable(Screen0_ButtonWidget_Start, LE_TRUE);
    Screen0_ButtonWidget_Start->fn->setString(Screen0_ButtonWidget_Start, (leString*)&string_Start);
    Screen0_ButtonWidget_Start->fn->setPressedEventCallback(Screen0_ButtonWidget_Start, event_Screen0_ButtonWidget_Start_OnPressed);
    root0->fn->addChild(root0, (leWidget*)Screen0_ButtonWidget_Start);

    Screen0_ImageWidget_Startimage = leImageWidget_New();
    Screen0_ImageWidget_Startimage->fn->setPosition(Screen0_ImageWidget_Startimage, 90, 11);
    Screen0_ImageWidget_Startimage->fn->setSize(Screen0_ImageWidget_Startimage, 27, 25);
    Screen0_ImageWidget_Startimage->fn->setScheme(Screen0_ImageWidget_Startimage, &Scheme1);
    Screen0_ImageWidget_Startimage->fn->setBorderType(Screen0_ImageWidget_Startimage, LE_WIDGET_BORDER_NONE);
    Screen0_ImageWidget_Startimage->fn->setImage(Screen0_ImageWidget_Startimage, (leImage*)&Start);
    Screen0_ButtonWidget_Start->fn->addChild(Screen0_ButtonWidget_Start, (leWidget*)Screen0_ImageWidget_Startimage);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen0_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen0(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen0_OnUpdate(); // raise event
}

void screenHide_Screen0(void)
{
    Screen0_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen0_SplashBackground = NULL;
    Screen0_Label_DemoName = NULL;
    Screen0_ImageWidget_Thermostat = NULL;
    Screen0_SplashBar = NULL;
    Screen0_SplashMicrochipLogo = NULL;
    Screen0_ImageWidget_Mplab = NULL;
    Screen0_SplashPIC32Logo = NULL;
    Screen0_ButtonWidget_Start = NULL;
    Screen0_ImageWidget_Wifilogo = NULL;
    Screen0_ImageWidget_Startimage = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen0(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen0(uint32_t lyrIdx)
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

