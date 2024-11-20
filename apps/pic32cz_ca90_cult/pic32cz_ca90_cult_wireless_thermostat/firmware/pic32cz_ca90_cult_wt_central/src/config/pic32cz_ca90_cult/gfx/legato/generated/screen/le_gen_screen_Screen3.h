#ifndef LE_GEN_SCREEN_SCREEN3_H
#define LE_GEN_SCREEN_SCREEN3_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Screen3_MultiNode_TempLimitPanel;
extern leImageWidget* Screen3_ImageWidget_LimitNode1;
extern leImageWidget* Screen3_ImageWidget_LimitNode2;
extern leButtonWidget* Screen3_ButtonWidget_Back;
extern leButtonWidget* Screen3_ButtonWidget_Enterlimit;
extern leButtonWidget* Screen3_ButtonWidget_IncNode1;
extern leButtonWidget* Screen3_ButtonWidget_IncNode2;
extern leButtonWidget* Screen3_ButtonWidget_DecNode1;
extern leButtonWidget* Screen3_ButtonWidget_DecNode2;
extern leTextFieldWidget* Screen3_TextFieldWidget_Limit1;
extern leTextFieldWidget* Screen3_TextFieldWidget_Limit2;
extern leImageWidget* Screen3_ImageWidget_Celsius1;
extern leImageWidget* Screen3_ImageWidget_Celsius2;
extern leLabelWidget* Screen3_LabelWidget_TempLimitNode1;
extern leLabelWidget* Screen3_LabelWidget_TempLimitNode2;
extern leImageWidget* Screen3_ImageWidget_Back;
extern leImageWidget* Screen3_ImageWidget_Enterlimit;
extern leImageWidget* Screen3_ImageWidget_IncNode1;
extern leImageWidget* Screen3_ImageWidget_IncNode2;
extern leImageRotateWidget* Screen3_ImageWidget_DecNode1;
extern leImageRotateWidget* Screen3_ImageWidget_DecNode2;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_Screen3_ButtonWidget_Back_OnPressed(leButtonWidget* btn);
void event_Screen3_ButtonWidget_Enterlimit_OnPressed(leButtonWidget* btn);
void event_Screen3_ButtonWidget_IncNode1_OnPressed(leButtonWidget* btn);
void event_Screen3_ButtonWidget_IncNode2_OnPressed(leButtonWidget* btn);
void event_Screen3_ButtonWidget_DecNode1_OnPressed(leButtonWidget* btn);
void event_Screen3_ButtonWidget_DecNode2_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Screen3(void); // called when Legato is initialized
leResult screenShow_Screen3(void); // called when screen is shown
void screenHide_Screen3(void); // called when screen is hidden
void screenDestroy_Screen3(void); // called when Legato is destroyed
void screenUpdate_Screen3(void); // called when Legato is updating

leWidget* screenGetRoot_Screen3(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Screen3_OnShow(void); // called when this screen is shown
void Screen3_OnHide(void); // called when this screen is hidden
void Screen3_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SCREEN3_H
