/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_WIDGETS.H                                                          */
/*                                                                         */
/*   C wrapper for Turbo Vision widget classes                            */
/*   (TButton, TInputLine, TLabel, TCheckBoxes, TRadioButtons)            */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_WIDGETS_H
#define TV_WIDGETS_H

#include "tv_types.h"
#include "tv_view.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque pointers */
typedef struct tv_Button tv_Button;
typedef struct tv_InputLine tv_InputLine;
typedef struct tv_Label tv_Label;
typedef struct tv_StaticText tv_StaticText;
typedef struct tv_CheckBoxes tv_CheckBoxes;
typedef struct tv_RadioButtons tv_RadioButtons;

/* Button flags */
#define TV_BF_NORMAL        0x00
#define TV_BF_DEFAULT       0x01
#define TV_BF_LEFT_JUST     0x02
#define TV_BF_BROADCAST     0x04

/* TButton functions */
tv_Button* tv_button_create(tv_Rect bounds, const char* title, tv_ushort command, tv_ushort flags);
void tv_button_destroy(tv_Button* button);
void tv_button_set_title(tv_Button* button, const char* title);
const char* tv_button_get_title(tv_Button* button);
void tv_button_make_default(tv_Button* button, tv_bool enable);
tv_View* tv_button_to_view(tv_Button* button);
tv_Button* tv_view_to_button(tv_View* view);

/* TInputLine functions */
tv_InputLine* tv_inputline_create(tv_Rect bounds, int max_len);
void tv_inputline_destroy(tv_InputLine* input);
void tv_inputline_set_data(tv_InputLine* input, const char* text);
void tv_inputline_get_data(tv_InputLine* input, char* buffer, int buffer_size);
const char* tv_inputline_get_text(tv_InputLine* input);
void tv_inputline_select_all(tv_InputLine* input, tv_bool enable);
int tv_inputline_get_max_len(tv_InputLine* input);
tv_View* tv_inputline_to_view(tv_InputLine* input);
tv_InputLine* tv_view_to_inputline(tv_View* view);

/* TStaticText functions */
tv_StaticText* tv_statictext_create(tv_Rect bounds, const char* text);
void tv_statictext_destroy(tv_StaticText* text);
void tv_statictext_set_text(tv_StaticText* text, const char* new_text);
const char* tv_statictext_get_text(tv_StaticText* text);
tv_View* tv_statictext_to_view(tv_StaticText* text);
tv_StaticText* tv_view_to_statictext(tv_View* view);

/* TLabel functions */
tv_Label* tv_label_create(tv_Rect bounds, const char* text, tv_View* link);
void tv_label_destroy(tv_Label* label);
void tv_label_set_text(tv_Label* label, const char* text);
const char* tv_label_get_text(tv_Label* label);
void tv_label_set_link(tv_Label* label, tv_View* link);
tv_View* tv_label_get_link(tv_Label* label);
tv_View* tv_label_to_view(tv_Label* label);
tv_Label* tv_view_to_label(tv_View* view);

/* Cluster item structure */
typedef struct tv_SItem {
    const char* text;
    tv_ushort value;
    struct tv_SItem* next;
} tv_SItem;

/* Helper to create item lists */
tv_SItem* tv_sitem_create(const char* text, tv_ushort value);
void tv_sitem_append(tv_SItem* list, tv_SItem* item);
void tv_sitem_destroy_list(tv_SItem* list);

/* TCheckBoxes functions */
tv_CheckBoxes* tv_checkboxes_create(tv_Rect bounds, tv_SItem* items);
void tv_checkboxes_destroy(tv_CheckBoxes* checkboxes);
tv_ushort tv_checkboxes_get_value(tv_CheckBoxes* checkboxes);
void tv_checkboxes_set_value(tv_CheckBoxes* checkboxes, tv_ushort value);
tv_View* tv_checkboxes_to_view(tv_CheckBoxes* checkboxes);
tv_CheckBoxes* tv_view_to_checkboxes(tv_View* view);

/* TRadioButtons functions */
tv_RadioButtons* tv_radiobuttons_create(tv_Rect bounds, tv_SItem* items);
void tv_radiobuttons_destroy(tv_RadioButtons* radiobuttons);
tv_ushort tv_radiobuttons_get_value(tv_RadioButtons* radiobuttons);
void tv_radiobuttons_set_value(tv_RadioButtons* radiobuttons, tv_ushort value);
tv_View* tv_radiobuttons_to_view(tv_RadioButtons* radiobuttons);
tv_RadioButtons* tv_view_to_radiobuttons(tv_View* view);

#ifdef __cplusplus
}
#endif

#endif /* TV_WIDGETS_H */

// Made with Bob
