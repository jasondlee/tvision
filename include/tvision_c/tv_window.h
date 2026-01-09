/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_WINDOW.H                                                           */
/*                                                                         */
/*   C wrapper for Turbo Vision TWindow and TDialog classes               */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_WINDOW_H
#define TV_WINDOW_H

#include "tv_types.h"
#include "tv_view.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque pointers */
typedef struct tv_Window tv_Window;
typedef struct tv_Dialog tv_Dialog;
typedef struct tv_Group tv_Group;

/* Window flags */
#define TV_WF_MOVE          0x01
#define TV_WF_GROW          0x02
#define TV_WF_CLOSE         0x04
#define TV_WF_ZOOM          0x08

/* TGroup functions (base class for TWindow) */
tv_Group* tv_group_create(tv_Rect bounds);
void tv_group_destroy(tv_Group* group);
void tv_group_insert(tv_Group* group, tv_View* view);
void tv_group_insert_before(tv_Group* group, tv_View* view, tv_View* target);
void tv_group_remove(tv_Group* group, tv_View* view);
tv_View* tv_group_first(tv_Group* group);
tv_View* tv_group_at(tv_Group* group, int index);
tv_View* tv_group_current(tv_Group* group);
void tv_group_set_current(tv_Group* group, tv_View* view, int select_mode);
void tv_group_select_next(tv_Group* group, tv_bool forwards);
tv_bool tv_group_focus_next(tv_Group* group, tv_bool forwards);
tv_ushort tv_group_execute(tv_Group* group);
tv_ushort tv_group_exec_view(tv_Group* group, tv_View* view);
void tv_group_redraw(tv_Group* group);
void tv_group_lock(tv_Group* group);
void tv_group_unlock(tv_Group* group);

/* Cast functions */
tv_View* tv_group_to_view(tv_Group* group);
tv_Group* tv_view_to_group(tv_View* view);

/* TWindow functions */
tv_Window* tv_window_create(tv_Rect bounds, const char* title, int number);
void tv_window_destroy(tv_Window* window);
void tv_window_close(tv_Window* window);
void tv_window_zoom(tv_Window* window);
const char* tv_window_get_title(tv_Window* window, int max_size);
void tv_window_set_title(tv_Window* window, const char* title);
int tv_window_get_number(tv_Window* window);
void tv_window_set_number(tv_Window* window, int number);
tv_uchar tv_window_get_flags(tv_Window* window);
void tv_window_set_flags(tv_Window* window, tv_uchar flags);

/* Cast functions */
tv_View* tv_window_to_view(tv_Window* window);
tv_Group* tv_window_to_group(tv_Window* window);
tv_Window* tv_view_to_window(tv_View* view);
tv_Window* tv_group_to_window(tv_Group* group);

/* TDialog functions */
tv_Dialog* tv_dialog_create(tv_Rect bounds, const char* title);
void tv_dialog_destroy(tv_Dialog* dialog);
tv_bool tv_dialog_valid(tv_Dialog* dialog, tv_ushort command);

/* Cast functions */
tv_View* tv_dialog_to_view(tv_Dialog* dialog);
tv_Group* tv_dialog_to_group(tv_Dialog* dialog);
tv_Window* tv_dialog_to_window(tv_Dialog* dialog);
tv_Dialog* tv_view_to_dialog(tv_View* view);
tv_Dialog* tv_group_to_dialog(tv_Group* group);
tv_Dialog* tv_window_to_dialog(tv_Window* window);

#ifdef __cplusplus
}
#endif

#endif /* TV_WINDOW_H */

// Made with Bob
