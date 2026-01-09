/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_WIDGETS.CPP                                                        */
/*                                                                         */
/*   C wrapper implementation for Turbo Vision widget classes             */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_TButton
#define Uses_TInputLine
#define Uses_TLabel
#define Uses_TStaticText
#define Uses_TCheckBoxes
#define Uses_TRadioButtons
#define Uses_TSItem
#define Uses_TRect
#include <tvision/tv.h>

#include "tvision_c/tv_widgets.h"
#include <cstring>

extern "C" {

/* TButton functions */

tv_Button* tv_button_create(tv_Rect bounds, const char* title, tv_ushort command, tv_ushort flags) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Button*>(new TButton(rect, title, command, flags));
}

void tv_button_destroy(tv_Button* button) {
    if (button) {
        TObject::destroy(reinterpret_cast<TButton*>(button));
    }
}

void tv_button_set_title(tv_Button* button, const char* title) {
    TButton* btn = reinterpret_cast<TButton*>(button);
    if (btn->title) {
        delete[] btn->title;
    }
    if (title) {
        size_t len = std::strlen(title);
        char* new_title = new char[len + 1];
        std::strcpy(new_title, title);
        btn->title = new_title;
    } else {
        btn->title = nullptr;
    }
}

const char* tv_button_get_title(tv_Button* button) {
    return reinterpret_cast<TButton*>(button)->title;
}

void tv_button_make_default(tv_Button* button, tv_bool enable) {
    reinterpret_cast<TButton*>(button)->makeDefault(enable ? True : False);
}

tv_View* tv_button_to_view(tv_Button* button) {
    return reinterpret_cast<tv_View*>(button);
}

tv_Button* tv_view_to_button(tv_View* view) {
    return reinterpret_cast<tv_Button*>(view);
}

/* TInputLine functions */

tv_InputLine* tv_inputline_create(tv_Rect bounds, int max_len) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_InputLine*>(new TInputLine(rect, max_len));
}

void tv_inputline_destroy(tv_InputLine* input) {
    if (input) {
        TObject::destroy(reinterpret_cast<TInputLine*>(input));
    }
}

void tv_inputline_set_data(tv_InputLine* input, const char* text) {
    if (text) {
        reinterpret_cast<TInputLine*>(input)->setData(const_cast<char*>(text));
    }
}

void tv_inputline_get_data(tv_InputLine* input, char* buffer, int buffer_size) {
    if (buffer && buffer_size > 0) {
        TInputLine* inp = reinterpret_cast<TInputLine*>(input);
        inp->getData(buffer);
        buffer[buffer_size - 1] = '\0';  // Ensure null termination
    }
}

const char* tv_inputline_get_text(tv_InputLine* input) {
    return reinterpret_cast<TInputLine*>(input)->data;
}

void tv_inputline_select_all(tv_InputLine* input, tv_bool enable) {
    reinterpret_cast<TInputLine*>(input)->selectAll(enable ? True : False);
}

int tv_inputline_get_max_len(tv_InputLine* input) {
    return reinterpret_cast<TInputLine*>(input)->maxLen;
}

tv_View* tv_inputline_to_view(tv_InputLine* input) {
    return reinterpret_cast<tv_View*>(input);
}

tv_InputLine* tv_view_to_inputline(tv_View* view) {
    return reinterpret_cast<tv_InputLine*>(view);
}

/* TStaticText functions */

tv_StaticText* tv_statictext_create(tv_Rect bounds, const char* text) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_StaticText*>(new TStaticText(rect, text));
}

void tv_statictext_destroy(tv_StaticText* text) {
    if (text) {
        TObject::destroy(reinterpret_cast<TStaticText*>(text));
    }
}

/*
void tv_statictext_set_text(tv_StaticText* text, const char* new_text) {
    TStaticText* st = reinterpret_cast<TStaticText*>(text);
    if (st->text) {
        delete[] st->text;
    }
    if (new_text) {
        size_t len = std::strlen(new_text);
        char* txt = new char[len + 1];
        std::strcpy(txt, new_text);
        st->text = txt;
    } else {
        st->text = nullptr;
    }
}

const char* tv_statictext_get_text(tv_StaticText* text) {
    return reinterpret_cast<TStaticText*>(text)->getText();
}
*/

tv_View* tv_statictext_to_view(tv_StaticText* text) {
    return reinterpret_cast<tv_View*>(text);
}

tv_StaticText* tv_view_to_statictext(tv_View* view) {
    return reinterpret_cast<tv_StaticText*>(view);
}

/* TLabel functions * /

tv_Label* tv_label_create(tv_Rect bounds, const char* text, tv_View* link) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Label*>(new TLabel(rect, text, reinterpret_cast<TView*>(link)));
}

void tv_label_destroy(tv_Label* label) {
    if (label) {
        TObject::destroy(reinterpret_cast<TLabel*>(label));
    }
}

void tv_label_set_text(tv_Label* label, const char* text) {
    TLabel* lbl = reinterpret_cast<TLabel*>(label);
    if (lbl->text) {
        delete[] lbl->text;
    }
    if (text) {
        size_t len = std::strlen(text);
        char* txt = new char[len + 1];
        std::strcpy(txt, text);
        lbl->text = txt;
    } else {
        lbl->text = nullptr;
    }
}

const char* tv_label_get_text(tv_Label* label) {
    return reinterpret_cast<TLabel*>(label)->text;
}

void tv_label_set_link(tv_Label* label, tv_View* link) {
    reinterpret_cast<TLabel*>(label)->link = reinterpret_cast<TView*>(link);
}

tv_View* tv_label_get_link(tv_Label* label) {
    return reinterpret_cast<tv_View*>(reinterpret_cast<TLabel*>(label)->link);
}

tv_View* tv_label_to_view(tv_Label* label) {
    return reinterpret_cast<tv_View*>(label);
}

tv_Label* tv_view_to_label(tv_View* view) {
    return reinterpret_cast<tv_Label*>(view);
}
*/

/* Helper functions for TSItem */

tv_SItem* tv_sitem_create(const char* text, tv_ushort value) {
    tv_SItem* item = new tv_SItem;
    if (text) {
        size_t len = std::strlen(text);
        char* txt = new char[len + 1];
        std::strcpy(txt, text);
        item->text = txt;
    } else {
        item->text = nullptr;
    }
    item->value = value;
    item->next = nullptr;
    return item;
}

void tv_sitem_append(tv_SItem* list, tv_SItem* item) {
    if (list && item) {
        tv_SItem* current = list;
        while (current->next) {
            current = current->next;
        }
        current->next = item;
    }
}

void tv_sitem_destroy_list(tv_SItem* list) {
    while (list) {
        tv_SItem* next = list->next;
        if (list->text) {
            delete[] list->text;
        }
        delete list;
        list = next;
    }
}

/* TCheckBoxes functions */

tv_CheckBoxes* tv_checkboxes_create(tv_Rect bounds, tv_SItem* items) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_CheckBoxes*>(
        new TCheckBoxes(rect, reinterpret_cast<TSItem*>(items))
    );
}

void tv_checkboxes_destroy(tv_CheckBoxes* checkboxes) {
    if (checkboxes) {
        TObject::destroy(reinterpret_cast<TCheckBoxes*>(checkboxes));
    }
}

tv_ushort tv_checkboxes_get_value(tv_CheckBoxes* checkboxes) {
    tv_ushort value = 0;
    reinterpret_cast<TCheckBoxes*>(checkboxes)->getData(&value);
    return value;
}

void tv_checkboxes_set_value(tv_CheckBoxes* checkboxes, tv_ushort value) {
    reinterpret_cast<TCheckBoxes*>(checkboxes)->setData(&value);
}

tv_View* tv_checkboxes_to_view(tv_CheckBoxes* checkboxes) {
    return reinterpret_cast<tv_View*>(checkboxes);
}

tv_CheckBoxes* tv_view_to_checkboxes(tv_View* view) {
    return reinterpret_cast<tv_CheckBoxes*>(view);
}

/* TRadioButtons functions */

tv_RadioButtons* tv_radiobuttons_create(tv_Rect bounds, tv_SItem* items) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_RadioButtons*>(
        new TRadioButtons(rect, reinterpret_cast<TSItem*>(items))
    );
}

void tv_radiobuttons_destroy(tv_RadioButtons* radiobuttons) {
    if (radiobuttons) {
        TObject::destroy(reinterpret_cast<TRadioButtons*>(radiobuttons));
    }
}

tv_ushort tv_radiobuttons_get_value(tv_RadioButtons* radiobuttons) {
    tv_ushort value = 0;
    reinterpret_cast<TRadioButtons*>(radiobuttons)->getData(&value);
    return value;
}

void tv_radiobuttons_set_value(tv_RadioButtons* radiobuttons, tv_ushort value) {
    reinterpret_cast<TRadioButtons*>(radiobuttons)->setData(&value);
}

tv_View* tv_radiobuttons_to_view(tv_RadioButtons* radiobuttons) {
    return reinterpret_cast<tv_View*>(radiobuttons);
}

tv_RadioButtons* tv_view_to_radiobuttons(tv_View* view) {
    return reinterpret_cast<tv_RadioButtons*>(view);
}

} /* extern "C" */

// Made with Bob
