/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_HELPERS.H                                                          */
/*                                                                         */
/*   C wrapper helper functions for common Turbo Vision operations        */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_HELPERS_H
#define TV_HELPERS_H

#include "tv_types.h"
#include "tv_events.h"
#include "tv_view.h"
#include "tv_window.h"
#include "tv_widgets.h"
#include "tv_lists.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Message box functions */
#define TV_MF_WARNING       0x0000
#define TV_MF_ERROR         0x0001
#define TV_MF_INFORMATION   0x0002
#define TV_MF_CONFIRMATION  0x0003
#define TV_MF_YES_BUTTON    0x0100
#define TV_MF_NO_BUTTON     0x0200
#define TV_MF_OK_BUTTON     0x0400
#define TV_MF_CANCEL_BUTTON 0x0800

tv_ushort execDialog( tv_Dialog *d, void *data );

tv_ushort tv_message_box(const char* msg, tv_ushort flags);
tv_ushort tv_message_box_rect(tv_Rect rect, const char* msg, tv_ushort flags);

/* Input box function */
tv_bool tv_input_box(const char* title, const char* label, char* buffer, int buffer_size);

/* Standard scrollbar creation helpers */
tv_ScrollBar* tv_create_vertical_scrollbar(int x, int y, int height);
tv_ScrollBar* tv_create_horizontal_scrollbar(int x, int y, int width);

/* Standard dialog helpers */
tv_Dialog* tv_create_centered_dialog(int width, int height, const char* title);
void tv_dialog_add_ok_cancel(tv_Dialog* dialog);
void tv_dialog_add_button(tv_Dialog* dialog, const char* title, tv_ushort command, int x, int y);

/* View positioning helpers */
void tv_center_view(tv_View* view, tv_Rect bounds);
void tv_center_view_in_desktop(tv_View* view);
tv_Rect tv_get_desktop_bounds(void);

/* Color and palette helpers */
typedef struct tv_ColorPair {
    tv_uchar foreground;
    tv_uchar background;
} tv_ColorPair;

/* Standard colors */
#define TV_COLOR_BLACK          0
#define TV_COLOR_BLUE           1
#define TV_COLOR_GREEN          2
#define TV_COLOR_CYAN           3
#define TV_COLOR_RED            4
#define TV_COLOR_MAGENTA        5
#define TV_COLOR_BROWN          6
#define TV_COLOR_LIGHT_GRAY     7
#define TV_COLOR_DARK_GRAY      8
#define TV_COLOR_LIGHT_BLUE     9
#define TV_COLOR_LIGHT_GREEN    10
#define TV_COLOR_LIGHT_CYAN     11
#define TV_COLOR_LIGHT_RED      12
#define TV_COLOR_LIGHT_MAGENTA  13
#define TV_COLOR_YELLOW         14
#define TV_COLOR_WHITE          15

tv_uchar tv_make_color(tv_uchar foreground, tv_uchar background);
tv_ColorPair tv_split_color(tv_uchar color);

/* Event helpers */
tv_Event tv_make_command_event(tv_ushort command, void* info_ptr);
tv_Event tv_make_broadcast_event(tv_ushort command, void* info_ptr);
tv_Event tv_make_key_event(tv_ushort key_code, tv_ushort control_key_state);
tv_bool tv_is_key_event(tv_Event event, tv_ushort key_code);

/* Key code constants */
#define TV_KB_ESC           0x011B
#define TV_KB_ENTER         0x000D
#define TV_KB_SPACE         0x0020
#define TV_KB_TAB           0x0009
#define TV_KB_BACK          0x0008
#define TV_KB_UP            0x4800
#define TV_KB_DOWN          0x5000
#define TV_KB_LEFT          0x4B00
#define TV_KB_RIGHT         0x4D00
#define TV_KB_HOME          0x4700
#define TV_KB_END           0x4F00
#define TV_KB_PGUP          0x4900
#define TV_KB_PGDN          0x5100
#define TV_KB_INS           0x5200
#define TV_KB_DEL           0x5300
#define TV_KB_F1            0x3B00
#define TV_KB_F2            0x3C00
#define TV_KB_F3            0x3D00
#define TV_KB_F4            0x3E00
#define TV_KB_F5            0x3F00
#define TV_KB_F6            0x4000
#define TV_KB_F7            0x4100
#define TV_KB_F8            0x4200
#define TV_KB_F9            0x4300
#define TV_KB_F10           0x4400

/* Control key state flags */
#define TV_KB_SHIFT         0x0003
#define TV_KB_CTRL          0x0004
#define TV_KB_ALT           0x0008

/* String helpers */
char* tv_new_str(const char* str);
void tv_delete_str(char* str);
char* tv_str_copy(char* dest, const char* src, int max_len);

/* Collection helpers for string lists */
tv_Collection* tv_create_string_list(const char** strings, int count);
void tv_string_list_add(tv_Collection* list, const char* str);
const char* tv_string_list_get(tv_Collection* list, int index);
int tv_string_list_count(tv_Collection* list);

/* File dialog helpers */
// tv_bool tv_open_file_dialog(const char* wildcard, const char* title, char* filename, int filename_size);
// tv_bool tv_save_file_dialog(const char* wildcard, const char* title, char* filename, int filename_size);

/* Desktop operations */
void tv_close_all_windows(void);

#ifdef __cplusplus
}
#endif

#endif /* TV_HELPERS_H */

// Made with Bob
