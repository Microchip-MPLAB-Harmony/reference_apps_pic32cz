#ifndef LE_GEN_SCREEN_SCREEN1_H
#define LE_GEN_SCREEN_SCREEN1_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Screen1_Multiconnect_Panel;
extern leImageSequenceWidget* Screen1_ImageSequenceWidget_Node1;
extern leImageSequenceWidget* Screen1_ImageSequenceWidget_Node2;
extern leLabelWidget* Screen1_Connectionstatus_label;
extern leImageSequenceWidget* Screen1_ImageSequenceWidget_ProgressAnime;
extern leLabelWidget* Screen1_LabelWidgetNode1;
extern leImageWidget* Screen1_ImageWidgetCheck1;
extern leLabelWidget* Screen1_LabelWidgetNode2;
extern leImageWidget* Screen1_ImageWidgetCheck2;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Screen1(void); // called when Legato is initialized
leResult screenShow_Screen1(void); // called when screen is shown
void screenHide_Screen1(void); // called when screen is hidden
void screenDestroy_Screen1(void); // called when Legato is destroyed
void screenUpdate_Screen1(void); // called when Legato is updating

leWidget* screenGetRoot_Screen1(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Screen1_OnShow(void); // called when this screen is shown
void Screen1_OnHide(void); // called when this screen is hidden
void Screen1_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SCREEN1_H
