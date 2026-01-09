/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_WINDOW.CPP                                                         */
/*                                                                         */
/*   C wrapper implementation for TWindow and TDialog classes             */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_TGroup
#define Uses_TWindow
#define Uses_TDialog
#define Uses_TRect
#define Uses_TView
#include <tvision/tv.h>

#include "tvision_c/tv_window.h"
#include <cstring>

extern "C" {

/* TGroup functions */

tv_Group* tv_group_create(tv_Rect bounds) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Group*>(new TGroup(rect));
}

void tv_group_destroy(tv_Group* group) {
    if (group) {
        TObject::destroy(reinterpret_cast<TGroup*>(group));
    }
}

void tv_group_insert(tv_Group* group, tv_View* view) {
    reinterpret_cast<TGroup*>(group)->insert(reinterpret_cast<TView*>(view));
}

void tv_group_insert_before(tv_Group* group, tv_View* view, tv_View* target) {
    reinterpret_cast<TGroup*>(group)->insertBefore(
        reinterpret_cast<TView*>(view),
        reinterpret_cast<TView*>(target)
    );
}

void tv_group_remove(tv_Group* group, tv_View* view) {
    reinterpret_cast<TGroup*>(group)->remove(reinterpret_cast<TView*>(view));
}

tv_View* tv_group_first(tv_Group* group) {
    return reinterpret_cast<tv_View*>(reinterpret_cast<TGroup*>(group)->first());
}

tv_View* tv_group_at(tv_Group* group, int index) {
    return reinterpret_cast<tv_View*>(reinterpret_cast<TGroup*>(group)->at(index));
}

tv_View* tv_group_current(tv_Group* group) {
    return reinterpret_cast<tv_View*>(reinterpret_cast<TGroup*>(group)->current);
}

void tv_group_set_current(tv_Group* group, tv_View* view, int select_mode) {
    reinterpret_cast<TGroup*>(group)->setCurrent(
        reinterpret_cast<TView*>(view),
        static_cast<TView::selectMode>(select_mode)
    );
}

void tv_group_select_next(tv_Group* group, tv_bool forwards) {
    reinterpret_cast<TGroup*>(group)->selectNext(forwards ? True : False);
}

tv_bool tv_group_focus_next(tv_Group* group, tv_bool forwards) {
    return reinterpret_cast<TGroup*>(group)->focusNext(forwards ? True : False) ? TV_TRUE : TV_FALSE;
}

tv_ushort tv_group_execute(tv_Group* group) {
    return reinterpret_cast<TGroup*>(group)->execute();
}

tv_ushort tv_group_exec_view(tv_Group* group, tv_View* view) {
    return reinterpret_cast<TGroup*>(group)->execView(reinterpret_cast<TView*>(view));
}

void tv_group_redraw(tv_Group* group) {
    reinterpret_cast<TGroup*>(group)->redraw();
}

void tv_group_lock(tv_Group* group) {
    reinterpret_cast<TGroup*>(group)->lock();
}

void tv_group_unlock(tv_Group* group) {
    reinterpret_cast<TGroup*>(group)->unlock();
}

/* Cast functions for TGroup */

tv_View* tv_group_to_view(tv_Group* group) {
    return reinterpret_cast<tv_View*>(group);
}

tv_Group* tv_view_to_group(tv_View* view) {
    return reinterpret_cast<tv_Group*>(view);
}

/* TWindow functions */

tv_Window* tv_window_create(tv_Rect bounds, const char* title, int number) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Window*>(new TWindow(rect, title, number));
}

void tv_window_destroy(tv_Window* window) {
    if (window) {
        TObject::destroy(reinterpret_cast<TWindow*>(window));
    }
}

void tv_window_close(tv_Window* window) {
    reinterpret_cast<TWindow*>(window)->close();
}

void tv_window_zoom(tv_Window* window) {
    reinterpret_cast<TWindow*>(window)->zoom();
}

const char* tv_window_get_title(tv_Window* window, int max_size) {
    return reinterpret_cast<TWindow*>(window)->getTitle(max_size);
}

void tv_window_set_title(tv_Window* window, const char* title) {
    TWindow* win = reinterpret_cast<TWindow*>(window);
    if (win->title) {
        delete[] win->title;
    }
    if (title) {
        size_t len = std::strlen(title);
        char* new_title = new char[len + 1];
        std::strcpy(new_title, title);
        win->title = new_title;
    } else {
        win->title = nullptr;
    }
}

int tv_window_get_number(tv_Window* window) {
    return reinterpret_cast<TWindow*>(window)->number;
}

void tv_window_set_number(tv_Window* window, int number) {
    reinterpret_cast<TWindow*>(window)->number = number;
}

tv_uchar tv_window_get_flags(tv_Window* window) {
    return reinterpret_cast<TWindow*>(window)->flags;
}

void tv_window_set_flags(tv_Window* window, tv_uchar flags) {
    reinterpret_cast<TWindow*>(window)->flags = flags;
}

/* Cast functions for TWindow */

tv_View* tv_window_to_view(tv_Window* window) {
    return reinterpret_cast<tv_View*>(window);
}

tv_Group* tv_window_to_group(tv_Window* window) {
    return reinterpret_cast<tv_Group*>(window);
}

tv_Window* tv_view_to_window(tv_View* view) {
    return reinterpret_cast<tv_Window*>(view);
}

tv_Window* tv_group_to_window(tv_Group* group) {
    return reinterpret_cast<tv_Window*>(group);
}

/* TDialog functions */

tv_Dialog* tv_dialog_create(tv_Rect bounds, const char* title) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Dialog*>(new TDialog(rect, title));
}

void tv_dialog_destroy(tv_Dialog* dialog) {
    if (dialog) {
        TObject::destroy(reinterpret_cast<TDialog*>(dialog));
    }
}

tv_bool tv_dialog_valid(tv_Dialog* dialog, tv_ushort command) {
    return reinterpret_cast<TDialog*>(dialog)->valid(command) ? TV_TRUE : TV_FALSE;
}

/* Cast functions for TDialog */

tv_View* tv_dialog_to_view(tv_Dialog* dialog) {
    return reinterpret_cast<tv_View*>(dialog);
}

tv_Group* tv_dialog_to_group(tv_Dialog* dialog) {
    return reinterpret_cast<tv_Group*>(dialog);
}

tv_Window* tv_dialog_to_window(tv_Dialog* dialog) {
    return reinterpret_cast<tv_Window*>(dialog);
}

tv_Dialog* tv_view_to_dialog(tv_View* view) {
    return reinterpret_cast<tv_Dialog*>(view);
}

tv_Dialog* tv_group_to_dialog(tv_Group* group) {
    return reinterpret_cast<tv_Dialog*>(group);
}

tv_Dialog* tv_window_to_dialog(tv_Window* window) {
    return reinterpret_cast<tv_Dialog*>(window);
}

} /* extern "C" */

// Made with Bob
