#include "gfx/legato/generated/screen/le_gen_screen_Screen1.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen1_Multiconnect_Panel;
leImageSequenceWidget* Screen1_ImageSequenceWidget_Node1;
leImageSequenceWidget* Screen1_ImageSequenceWidget_Node2;
leLabelWidget* Screen1_Connectionstatus_label;
leImageSequenceWidget* Screen1_ImageSequenceWidget_ProgressAnime;
leLabelWidget* Screen1_LabelWidgetNode1;
leImageWidget* Screen1_ImageWidgetCheck1;
leLabelWidget* Screen1_LabelWidgetNode2;
leImageWidget* Screen1_ImageWidgetCheck2;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen1(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen1(void)
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

    Screen1_Multiconnect_Panel = leWidget_New();
    Screen1_Multiconnect_Panel->fn->setPosition(Screen1_Multiconnect_Panel, 0, 0);
    Screen1_Multiconnect_Panel->fn->setSize(Screen1_Multiconnect_Panel, 480, 272);
    Screen1_Multiconnect_Panel->fn->setScheme(Screen1_Multiconnect_Panel, &Scheme1);
    root0->fn->addChild(root0, (leWidget*)Screen1_Multiconnect_Panel);

    Screen1_ImageSequenceWidget_Node1 = leImageSequenceWidget_New();
    Screen1_ImageSequenceWidget_Node1->fn->setPosition(Screen1_ImageSequenceWidget_Node1, 66, 29);
    Screen1_ImageSequenceWidget_Node1->fn->setBackgroundType(Screen1_ImageSequenceWidget_Node1, LE_WIDGET_BACKGROUND_NONE);
    Screen1_ImageSequenceWidget_Node1->fn->setRepeat(Screen1_ImageSequenceWidget_Node1, LE_TRUE);
    Screen1_ImageSequenceWidget_Node1->fn->setImageCount(Screen1_ImageSequenceWidget_Node1, 2);
    Screen1_ImageSequenceWidget_Node1->fn->setImage(Screen1_ImageSequenceWidget_Node1, 0, &DeviceNode_noselect);
    Screen1_ImageSequenceWidget_Node1->fn->setImageDelay(Screen1_ImageSequenceWidget_Node1, 0, 1000);
    Screen1_ImageSequenceWidget_Node1->fn->setImage(Screen1_ImageSequenceWidget_Node1, 1, &DeviceNode_select_bmp);
    Screen1_ImageSequenceWidget_Node1->fn->setImageDelay(Screen1_ImageSequenceWidget_Node1, 1, 1000);
    root0->fn->addChild(root0, (leWidget*)Screen1_ImageSequenceWidget_Node1);

    Screen1_LabelWidgetNode1 = leLabelWidget_New();
    Screen1_LabelWidgetNode1->fn->setPosition(Screen1_LabelWidgetNode1, 22, 21);
    Screen1_LabelWidgetNode1->fn->setSize(Screen1_LabelWidgetNode1, 16, 19);
    Screen1_LabelWidgetNode1->fn->setScheme(Screen1_LabelWidgetNode1, &Scheme_2);
    Screen1_LabelWidgetNode1->fn->setBackgroundType(Screen1_LabelWidgetNode1, LE_WIDGET_BACKGROUND_NONE);
    Screen1_LabelWidgetNode1->fn->setString(Screen1_LabelWidgetNode1, (leString*)&string_Node1);
    Screen1_ImageSequenceWidget_Node1->fn->addChild(Screen1_ImageSequenceWidget_Node1, (leWidget*)Screen1_LabelWidgetNode1);

    Screen1_ImageWidgetCheck1 = leImageWidget_New();
    Screen1_ImageWidgetCheck1->fn->setPosition(Screen1_ImageWidgetCheck1, 30, 40);
    Screen1_ImageWidgetCheck1->fn->setSize(Screen1_ImageWidgetCheck1, 44, 29);
    Screen1_ImageWidgetCheck1->fn->setVisible(Screen1_ImageWidgetCheck1, LE_FALSE);
    Screen1_ImageWidgetCheck1->fn->setScheme(Screen1_ImageWidgetCheck1, &WhiteScheme);
    Screen1_ImageWidgetCheck1->fn->setBackgroundType(Screen1_ImageWidgetCheck1, LE_WIDGET_BACKGROUND_NONE);
    Screen1_ImageWidgetCheck1->fn->setBorderType(Screen1_ImageWidgetCheck1, LE_WIDGET_BORDER_NONE);
    Screen1_ImageWidgetCheck1->fn->setImage(Screen1_ImageWidgetCheck1, (leImage*)&check);
    Screen1_ImageSequenceWidget_Node1->fn->addChild(Screen1_ImageSequenceWidget_Node1, (leWidget*)Screen1_ImageWidgetCheck1);

    Screen1_ImageSequenceWidget_Node2 = leImageSequenceWidget_New();
    Screen1_ImageSequenceWidget_Node2->fn->setPosition(Screen1_ImageSequenceWidget_Node2, 297, 40);
    Screen1_ImageSequenceWidget_Node2->fn->setSize(Screen1_ImageSequenceWidget_Node2, 78, 83);
    Screen1_ImageSequenceWidget_Node2->fn->setScheme(Screen1_ImageSequenceWidget_Node2, &Scheme1);
    Screen1_ImageSequenceWidget_Node2->fn->setBackgroundType(Screen1_ImageSequenceWidget_Node2, LE_WIDGET_BACKGROUND_NONE);
    Screen1_ImageSequenceWidget_Node2->fn->setRepeat(Screen1_ImageSequenceWidget_Node2, LE_TRUE);
    Screen1_ImageSequenceWidget_Node2->fn->setImageCount(Screen1_ImageSequenceWidget_Node2, 2);
    Screen1_ImageSequenceWidget_Node2->fn->setImage(Screen1_ImageSequenceWidget_Node2, 0, &DeviceNode_noselect);
    Screen1_ImageSequenceWidget_Node2->fn->setImageDelay(Screen1_ImageSequenceWidget_Node2, 0, 1000);
    Screen1_ImageSequenceWidget_Node2->fn->setImage(Screen1_ImageSequenceWidget_Node2, 1, &DeviceNode_select_bmp);
    Screen1_ImageSequenceWidget_Node2->fn->setImageDelay(Screen1_ImageSequenceWidget_Node2, 1, 1000);
    root0->fn->addChild(root0, (leWidget*)Screen1_ImageSequenceWidget_Node2);

    Screen1_LabelWidgetNode2 = leLabelWidget_New();
    Screen1_LabelWidgetNode2->fn->setPosition(Screen1_LabelWidgetNode2, 10, 11);
    Screen1_LabelWidgetNode2->fn->setSize(Screen1_LabelWidgetNode2, 16, 19);
    Screen1_LabelWidgetNode2->fn->setScheme(Screen1_LabelWidgetNode2, &Scheme_2);
    Screen1_LabelWidgetNode2->fn->setBackgroundType(Screen1_LabelWidgetNode2, LE_WIDGET_BACKGROUND_NONE);
    Screen1_LabelWidgetNode2->fn->setString(Screen1_LabelWidgetNode2, (leString*)&string_Node2);
    Screen1_ImageSequenceWidget_Node2->fn->addChild(Screen1_ImageSequenceWidget_Node2, (leWidget*)Screen1_LabelWidgetNode2);

    Screen1_ImageWidgetCheck2 = leImageWidget_New();
    Screen1_ImageWidgetCheck2->fn->setPosition(Screen1_ImageWidgetCheck2, 24, 28);
    Screen1_ImageWidgetCheck2->fn->setSize(Screen1_ImageWidgetCheck2, 28, 26);
    Screen1_ImageWidgetCheck2->fn->setBackgroundType(Screen1_ImageWidgetCheck2, LE_WIDGET_BACKGROUND_NONE);
    Screen1_ImageWidgetCheck2->fn->setBorderType(Screen1_ImageWidgetCheck2, LE_WIDGET_BORDER_NONE);
    Screen1_ImageWidgetCheck2->fn->setImage(Screen1_ImageWidgetCheck2, (leImage*)&check);
    Screen1_ImageSequenceWidget_Node2->fn->addChild(Screen1_ImageSequenceWidget_Node2, (leWidget*)Screen1_ImageWidgetCheck2);

    Screen1_Connectionstatus_label = leLabelWidget_New();
    Screen1_Connectionstatus_label->fn->setPosition(Screen1_Connectionstatus_label, 129, 167);
    Screen1_Connectionstatus_label->fn->setSize(Screen1_Connectionstatus_label, 202, 29);
    Screen1_Connectionstatus_label->fn->setScheme(Screen1_Connectionstatus_label, &Scheme1);
    Screen1_Connectionstatus_label->fn->setHAlignment(Screen1_Connectionstatus_label, LE_HALIGN_CENTER);
    Screen1_Connectionstatus_label->fn->setString(Screen1_Connectionstatus_label, (leString*)&string_Connecting);
    root0->fn->addChild(root0, (leWidget*)Screen1_Connectionstatus_label);

    Screen1_ImageSequenceWidget_ProgressAnime = leImageSequenceWidget_New();
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setPosition(Screen1_ImageSequenceWidget_ProgressAnime, 150, 204);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setSize(Screen1_ImageSequenceWidget_ProgressAnime, 152, 28);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setScheme(Screen1_ImageSequenceWidget_ProgressAnime, &WhiteScheme);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setBackgroundType(Screen1_ImageSequenceWidget_ProgressAnime, LE_WIDGET_BACKGROUND_NONE);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setRepeat(Screen1_ImageSequenceWidget_ProgressAnime, LE_TRUE);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImageCount(Screen1_ImageSequenceWidget_ProgressAnime, 5);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImage(Screen1_ImageSequenceWidget_ProgressAnime, 0, &noload);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImageDelay(Screen1_ImageSequenceWidget_ProgressAnime, 0, 1000);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImage(Screen1_ImageSequenceWidget_ProgressAnime, 1, &load_1);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImageDelay(Screen1_ImageSequenceWidget_ProgressAnime, 1, 1000);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImage(Screen1_ImageSequenceWidget_ProgressAnime, 2, &load_2);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImageDelay(Screen1_ImageSequenceWidget_ProgressAnime, 2, 1000);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImage(Screen1_ImageSequenceWidget_ProgressAnime, 3, &load_3);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImageDelay(Screen1_ImageSequenceWidget_ProgressAnime, 3, 1000);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImage(Screen1_ImageSequenceWidget_ProgressAnime, 4, &full_load);
    Screen1_ImageSequenceWidget_ProgressAnime->fn->setImageDelay(Screen1_ImageSequenceWidget_ProgressAnime, 4, 1000);
    root0->fn->addChild(root0, (leWidget*)Screen1_ImageSequenceWidget_ProgressAnime);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    Screen1_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen1(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen1_OnUpdate(); // raise event
}

void screenHide_Screen1(void)
{
    Screen1_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen1_Multiconnect_Panel = NULL;
    Screen1_ImageSequenceWidget_Node1 = NULL;
    Screen1_ImageSequenceWidget_Node2 = NULL;
    Screen1_Connectionstatus_label = NULL;
    Screen1_ImageSequenceWidget_ProgressAnime = NULL;
    Screen1_LabelWidgetNode1 = NULL;
    Screen1_ImageWidgetCheck1 = NULL;
    Screen1_LabelWidgetNode2 = NULL;
    Screen1_ImageWidgetCheck2 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen1(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen1(uint32_t lyrIdx)
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

