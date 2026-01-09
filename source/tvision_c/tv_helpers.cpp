/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_HELPERS.CPP                                                        */
/*                                                                         */
/*   C wrapper implementation for helper functions                        */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_MsgBox
#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TRect
#define Uses_TPoint
#define Uses_TEvent
#define Uses_TScrollBar
#define Uses_TDialog
#define Uses_TButton
#define Uses_TInputLine
#define Uses_TLabel
#define Uses_TCollection
#define Uses_TStringCollection
#define Uses_TFileDialog
#include <tvision/tv.h>

#include "tvision_c/tv_helpers.h"
#include <cstring>

extern "C" {

/* Message box functions */

tv_ushort execDialog( tv_Dialog *d, void *data ) {
    TView *p =  reinterpret_cast<TProgram*> (TProgram::application)->validView( reinterpret_cast<TView*>(d) );
    if( p == 0 ) {
        return cmCancel;
    } else{
        if( data != 0 ) {
            p->setData( data );
        }
        ushort result = TProgram::deskTop->execView( p );
        if( result != cmCancel && data != 0 ) {
            p->getData( data );
        }
        TObject::destroy( p );
        return result;
    }
}


tv_ushort tv_message_box(const char* msg, tv_ushort flags) {
    return messageBox(msg, flags);
}

tv_ushort tv_message_box_rect(tv_Rect rect, const char* msg, tv_ushort flags) {
    TRect r(rect.ax, rect.ay, rect.bx, rect.by);
    return messageBoxRect(r, msg, flags);
}

/* Input box function */

tv_bool tv_input_box(const char* title, const char* label, char* buffer, int buffer_size) {
    if (!buffer || buffer_size <= 0) return TV_FALSE;
    
    char temp[256];
    if (buffer_size > 256) buffer_size = 256;
    std::strncpy(temp, buffer, buffer_size - 1);
    temp[buffer_size - 1] = '\0';
    
    ushort result = inputBox(title, label, temp, buffer_size);
    
    if (result == cmOK) {
        std::strncpy(buffer, temp, buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
        return TV_TRUE;
    }
    return TV_FALSE;
}

/* Standard scrollbar creation helpers */

tv_ScrollBar* tv_create_vertical_scrollbar(int x, int y, int height) {
    TRect r(x, y, x + 1, y + height);
    return reinterpret_cast<tv_ScrollBar*>(new TScrollBar(r));
}

tv_ScrollBar* tv_create_horizontal_scrollbar(int x, int y, int width) {
    TRect r(x, y, x + width, y + 1);
    return reinterpret_cast<tv_ScrollBar*>(new TScrollBar(r));
}

/* Standard dialog helpers */

tv_Dialog* tv_create_centered_dialog(int width, int height, const char* title) {
    TRect r(0, 0, width, height);
    TDialog* dialog = new TDialog(r, title);
    dialog->options |= ofCentered;
    return reinterpret_cast<tv_Dialog*>(dialog);
}

void tv_dialog_add_ok_cancel(tv_Dialog* dialog) {
    TDialog* dlg = reinterpret_cast<TDialog*>(dialog);
    TRect r = dlg->getExtent();
    
    // OK button
    TRect okRect(r.b.x - 24, r.b.y - 3, r.b.x - 14, r.b.y - 1);
    TButton* okBtn = new TButton(okRect, "~O~K", cmOK, bfDefault);
    dlg->insert(okBtn);
    
    // Cancel button
    TRect cancelRect(r.b.x - 12, r.b.y - 3, r.b.x - 2, r.b.y - 1);
    TButton* cancelBtn = new TButton(cancelRect, "Cancel", cmCancel, bfNormal);
    dlg->insert(cancelBtn);
}

void tv_dialog_add_button(tv_Dialog* dialog, const char* title, tv_ushort command, int x, int y) {
    TDialog* dlg = reinterpret_cast<TDialog*>(dialog);
    TRect r(x, y, x + 10, y + 2);
    TButton* btn = new TButton(r, title, command, bfNormal);
    dlg->insert(btn);
}

/* View positioning helpers */

void tv_center_view(tv_View* view, tv_Rect bounds) {
    TView* v = reinterpret_cast<TView*>(view);
    TRect r = v->getBounds();
    TRect container(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    
    int x = container.a.x + (container.b.x - container.a.x - r.b.x) / 2;
    int y = container.a.y + (container.b.y - container.a.y - r.b.y) / 2;
    
    v->moveTo(x, y);
}

void tv_center_view_in_desktop(tv_View* view) {
    if (TProgram::deskTop) {
        TRect r = TProgram::deskTop->getExtent();
        tv_Rect bounds;
        bounds.ax = r.a.x;
        bounds.ay = r.a.y;
        bounds.bx = r.b.x;
        bounds.by = r.b.y;
        tv_center_view(view, bounds);
    }
}

tv_Rect tv_get_desktop_bounds(void) {
    tv_Rect result = {0, 0, 80, 25};
    if (TProgram::deskTop) {
        TRect r = TProgram::deskTop->getExtent();
        result.ax = r.a.x;
        result.ay = r.a.y;
        result.bx = r.b.x;
        result.by = r.b.y;
    }
    return result;
}

/* Color and palette helpers */

tv_uchar tv_make_color(tv_uchar foreground, tv_uchar background) {
    return (background << 4) | (foreground & 0x0F);
}

tv_ColorPair tv_split_color(tv_uchar color) {
    tv_ColorPair pair;
    pair.foreground = color & 0x0F;
    pair.background = (color >> 4) & 0x0F;
    return pair;
}

/* Event helpers */

tv_Event tv_make_command_event(tv_ushort command, void* info_ptr) {
    tv_Event event;
    event.what = TV_EV_COMMAND;
    event.data.message.command = command;
    event.data.message.info_ptr = info_ptr;
    return event;
}

tv_Event tv_make_broadcast_event(tv_ushort command, void* info_ptr) {
    tv_Event event;
    event.what = TV_EV_BROADCAST;
    event.data.message.command = command;
    event.data.message.info_ptr = info_ptr;
    return event;
}

tv_Event tv_make_key_event(tv_ushort key_code, tv_ushort control_key_state) {
    tv_Event event;
    event.what = TV_EV_KEY_DOWN;
    event.data.key.key_code = key_code;
    event.data.key.control_key_state = control_key_state;
    event.data.key.text_length = 0;
    return event;
}

tv_bool tv_is_key_event(tv_Event event, tv_ushort key_code) {
    return (event.what == TV_EV_KEY_DOWN && event.data.key.key_code == key_code) ? TV_TRUE : TV_FALSE;
}

/* String helpers */

char* tv_new_str(const char* str) {
    if (!str) return nullptr;
    return newStr(str);
}

void tv_delete_str(char* str) {
    if (str) delete[] str;
}

char* tv_str_copy(char* dest, const char* src, int max_len) {
    if (!dest || !src || max_len <= 0) return dest;
    std::strncpy(dest, src, max_len - 1);
    dest[max_len - 1] = '\0';
    return dest;
}

/* Collection helpers for string lists */

tv_Collection* tv_create_string_list(const char** strings, int count) {
    TStringCollection* coll = new TStringCollection(count, 10);
    for (int i = 0; i < count; ++i) {
        if (strings[i]) {
            coll->insert(newStr(strings[i]));
        }
    }
    return reinterpret_cast<tv_Collection*>(coll);
}

void tv_string_list_add(tv_Collection* list, const char* str) {
    if (list && str) {
        reinterpret_cast<TStringCollection*>(list)->insert(newStr(str));
    }
}

const char* tv_string_list_get(tv_Collection* list, int index) {
    if (!list) return nullptr;
    return static_cast<const char*>(reinterpret_cast<TCollection*>(list)->at(index));
}

int tv_string_list_count(tv_Collection* list) {
    if (!list) return 0;
    return reinterpret_cast<TCollection*>(list)->getCount();
}

/* File dialog helpers */

/*
tv_bool tv_open_file_dialog(const char* wildcard, const char* title, char* filename, int filename_size) {
    if (!filename || filename_size <= 0) return TV_FALSE;
    
    char temp[256];
    std::strncpy(temp, filename, 255);
    temp[255] = '\0';
    
    ushort result = execDialog(new TFileDialog(wildcard, title, "~N~ame", fdOpenButton, 100), temp);
    
    if (result == cmFileOpen) {
        std::strncpy(filename, temp, filename_size - 1);
        filename[filename_size - 1] = '\0';
        return TV_TRUE;
    }
    return TV_FALSE;
}

tv_bool tv_save_file_dialog(const char* wildcard, const char* title, char* filename, int filename_size) {
    if (!filename || filename_size <= 0) return TV_FALSE;
    
    char temp[256];
    std::strncpy(temp, filename, 255);
    temp[255] = '\0';
    
    ushort result = execDialog(new TFileDialog(wildcard, title, "~N~ame", 0, 101), temp);
    
    if (result == cmFileOpen) {
        std::strncpy(filename, temp, filename_size - 1);
        filename[filename_size - 1] = '\0';
        return TV_TRUE;
    }
    return TV_FALSE;
}
*/

void tv_close_all_windows(void) {
    if (TProgram::deskTop) {
        TView* p = TProgram::deskTop->first();
        while (p) {
            TView* next = p->next;
            if (p->options & ofTileable) {
                TObject::destroy(p);
            }
            p = next;
        }
    }
}

} /* extern "C" */

// Made with Bob
