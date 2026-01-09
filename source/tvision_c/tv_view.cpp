/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_VIEW.CPP                                                           */
/*                                                                         */
/*   C wrapper implementation for Turbo Vision TView class                */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_TView
#define Uses_TRect
#define Uses_TPoint
#define Uses_TEvent
#include <tvision/tv.h>

#include "tvision_c/tv_view.h"

extern "C" {

/* View lifecycle */

tv_View* tv_view_create(tv_Rect bounds) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_View*>(new TView(rect));
}

void tv_view_destroy(tv_View* view) {
    if (view) {
        TObject::destroy(reinterpret_cast<TView*>(view));
    }
}

/* View properties */

tv_Rect tv_view_get_bounds(tv_View* view) {
    TRect rect = reinterpret_cast<TView*>(view)->getBounds();
    tv_Rect result;
    result.ax = rect.a.x;
    result.ay = rect.a.y;
    result.bx = rect.b.x;
    result.by = rect.b.y;
    return result;
}

tv_Rect tv_view_get_extent(tv_View* view) {
    TRect rect = reinterpret_cast<TView*>(view)->getExtent();
    tv_Rect result;
    result.ax = rect.a.x;
    result.ay = rect.a.y;
    result.bx = rect.b.x;
    result.by = rect.b.y;
    return result;
}

tv_Rect tv_view_get_clip_rect(tv_View* view) {
    TRect rect = reinterpret_cast<TView*>(view)->getClipRect();
    tv_Rect result;
    result.ax = rect.a.x;
    result.ay = rect.a.y;
    result.bx = rect.b.x;
    result.by = rect.b.y;
    return result;
}

void tv_view_set_bounds(tv_View* view, tv_Rect bounds) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    reinterpret_cast<TView*>(view)->setBounds(rect);
}

void tv_view_locate(tv_View* view, tv_Rect bounds) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    reinterpret_cast<TView*>(view)->locate(rect);
}

void tv_view_move_to(tv_View* view, int x, int y) {
    reinterpret_cast<TView*>(view)->moveTo(x, y);
}

void tv_view_grow_to(tv_View* view, int x, int y) {
    reinterpret_cast<TView*>(view)->growTo(x, y);
}

/* View state management */

tv_ushort tv_view_get_state(tv_View* view) {
    return reinterpret_cast<TView*>(view)->state;
}

void tv_view_set_state(tv_View* view, tv_ushort state, tv_bool enable) {
    reinterpret_cast<TView*>(view)->setState(state, enable ? True : False);
}

tv_bool tv_view_get_state_flag(tv_View* view, tv_ushort flag) {
    return (reinterpret_cast<TView*>(view)->state & flag) ? TV_TRUE : TV_FALSE;
}

/* View options */

tv_ushort tv_view_get_options(tv_View* view) {
    return reinterpret_cast<TView*>(view)->options;
}

void tv_view_set_options(tv_View* view, tv_ushort options, tv_bool enable) {
    TView* v = reinterpret_cast<TView*>(view);
    if (enable) {
        v->options |= options;
    } else {
        v->options &= ~options;
    }
}

/* View visibility */

void tv_view_show(tv_View* view) {
    reinterpret_cast<TView*>(view)->show();
}

void tv_view_hide(tv_View* view) {
    reinterpret_cast<TView*>(view)->hide();
}

tv_bool tv_view_exposed(tv_View* view) {
    return reinterpret_cast<TView*>(view)->exposed() ? TV_TRUE : TV_FALSE;
}

/* View focus */

tv_bool tv_view_focus(tv_View* view) {
    return reinterpret_cast<TView*>(view)->focus() ? TV_TRUE : TV_FALSE;
}

/* View drawing */

void tv_view_draw(tv_View* view) {
    reinterpret_cast<TView*>(view)->draw();
}

void tv_view_draw_view(tv_View* view) {
    reinterpret_cast<TView*>(view)->drawView();
}

/* Cursor management */

void tv_view_set_cursor(tv_View* view, int x, int y) {
    reinterpret_cast<TView*>(view)->setCursor(x, y);
}

void tv_view_show_cursor(tv_View* view) {
    reinterpret_cast<TView*>(view)->showCursor();
}

void tv_view_hide_cursor(tv_View* view) {
    reinterpret_cast<TView*>(view)->hideCursor();
}

void tv_view_block_cursor(tv_View* view) {
    reinterpret_cast<TView*>(view)->blockCursor();
}

void tv_view_normal_cursor(tv_View* view) {
    reinterpret_cast<TView*>(view)->normalCursor();
}

/* Event handling */

void tv_view_handle_event(tv_View* view, tv_EventHandle* event) {
    reinterpret_cast<TView*>(view)->handleEvent(*reinterpret_cast<TEvent*>(event));
}

void tv_view_get_event(tv_View* view, tv_EventHandle* event) {
    reinterpret_cast<TView*>(view)->getEvent(*reinterpret_cast<TEvent*>(event));
}

void tv_view_put_event(tv_View* view, tv_EventHandle* event) {
    reinterpret_cast<TView*>(view)->putEvent(*reinterpret_cast<TEvent*>(event));
}

void tv_view_clear_event(tv_View* view, tv_EventHandle* event) {
    reinterpret_cast<TView*>(view)->clearEvent(*reinterpret_cast<TEvent*>(event));
}

tv_bool tv_view_event_avail(tv_View* view) {
    return reinterpret_cast<TView*>(view)->eventAvail() ? TV_TRUE : TV_FALSE;
}

/* Data transfer */

tv_ushort tv_view_data_size(tv_View* view) {
    return reinterpret_cast<TView*>(view)->dataSize();
}

void tv_view_get_data(tv_View* view, void* rec) {
    reinterpret_cast<TView*>(view)->getData(rec);
}

void tv_view_set_data(tv_View* view, void* rec) {
    reinterpret_cast<TView*>(view)->setData(rec);
}

/* Validation */

tv_bool tv_view_valid(tv_View* view, tv_ushort command) {
    return reinterpret_cast<TView*>(view)->valid(command) ? TV_TRUE : TV_FALSE;
}

/* Help context */

tv_ushort tv_view_get_help_ctx(tv_View* view) {
    return reinterpret_cast<TView*>(view)->getHelpCtx();
}

/* Mouse interaction */

tv_bool tv_view_mouse_in_view(tv_View* view, tv_Point mouse) {
    TPoint point;
    point.x = mouse.x;
    point.y = mouse.y;
    return reinterpret_cast<TView*>(view)->mouseInView(point) ? TV_TRUE : TV_FALSE;
}

tv_bool tv_view_contains_mouse(tv_View* view, tv_EventHandle* event) {
    return reinterpret_cast<TView*>(view)->containsMouse(*reinterpret_cast<TEvent*>(event)) ? TV_TRUE : TV_FALSE;
}

/* Command support */

tv_bool tv_view_command_enabled(tv_ushort command) {
    return TView::commandEnabled(command) ? TV_TRUE : TV_FALSE;
}

void tv_view_enable_command(tv_ushort command) {
    TView::enableCommand(command);
}

void tv_view_disable_command(tv_ushort command) {
    TView::disableCommand(command);
}

void tv_view_enable_commands(tv_ushort* commands, int count) {
    for (int i = 0; i < count; ++i) {
        TView::enableCommand(commands[i]);
    }
}

void tv_view_disable_commands(tv_ushort* commands, int count) {
    for (int i = 0; i < count; ++i) {
        TView::disableCommand(commands[i]);
    }
}

} /* extern "C" */

// Made with Bob
