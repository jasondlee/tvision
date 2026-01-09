/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_VIEW.H                                                             */
/*                                                                         */
/*   C wrapper for Turbo Vision TView class                               */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_VIEW_H
#define TV_VIEW_H

#include "tv_types.h"
#include "tv_events.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque pointer to TView */
typedef struct tv_View tv_View;

/* View state flags */
#define TV_SF_VISIBLE       0x0001
#define TV_SF_CURSOR_VIS    0x0002
#define TV_SF_CURSOR_INS    0x0004
#define TV_SF_SHADOW        0x0008
#define TV_SF_ACTIVE        0x0010
#define TV_SF_SELECTED      0x0020
#define TV_SF_FOCUSED       0x0040
#define TV_SF_DRAGGING      0x0080
#define TV_SF_DISABLED      0x0100
#define TV_SF_MODAL         0x0200
#define TV_SF_DEFAULT       0x0400
#define TV_SF_EXPOSED       0x0800

/* View option flags */
#define TV_OF_SELECTABLE    0x0001
#define TV_OF_TOP_SELECT    0x0002
#define TV_OF_FIRST_CLICK   0x0004
#define TV_OF_FRAME_ONLY    0x0008
#define TV_OF_PRE_PROCESS   0x0010
#define TV_OF_POST_PROCESS  0x0020
#define TV_OF_BUFFERED      0x0040
#define TV_OF_TILEABLE      0x0080
#define TV_OF_CENTER_X      0x0100
#define TV_OF_CENTER_Y      0x0200
#define TV_OF_VALIDATE      0x0400

/* View grow mode flags */
#define TV_GF_GROW_LO_X     0x01
#define TV_GF_GROW_LO_Y     0x02
#define TV_GF_GROW_HI_X     0x04
#define TV_GF_GROW_HI_Y     0x08
#define TV_GF_GROW_ALL      0x0F
#define TV_GF_GROW_REL      0x10

/* View drag mode flags */
#define TV_DM_DRAG_MOVE     0x01
#define TV_DM_DRAG_GROW     0x02
#define TV_DM_LIMIT_LOOX    0x10
#define TV_DM_LIMIT_LOOY    0x20
#define TV_DM_LIMIT_HIOX    0x40
#define TV_DM_LIMIT_HIOY    0x80
#define TV_DM_LIMIT_ALL     0xF0

/* Command codes */
#define TV_CM_VALID         0
#define TV_CM_QUIT          1
#define TV_CM_ERROR         2
#define TV_CM_MENU          3
#define TV_CM_CLOSE         4
#define TV_CM_ZOOM          5
#define TV_CM_RESIZE        6
#define TV_CM_NEXT          7
#define TV_CM_PREV          8
#define TV_CM_OK            10
#define TV_CM_CANCEL        11
#define TV_CM_YES           12
#define TV_CM_NO            13
#define TV_CM_DEFAULT       14

/* View lifecycle */
tv_View* tv_view_create(tv_Rect bounds);
void tv_view_destroy(tv_View* view);

/* View properties */
tv_Rect tv_view_get_bounds(tv_View* view);
tv_Rect tv_view_get_extent(tv_View* view);
tv_Rect tv_view_get_clip_rect(tv_View* view);
void tv_view_set_bounds(tv_View* view, tv_Rect bounds);
void tv_view_locate(tv_View* view, tv_Rect bounds);
void tv_view_move_to(tv_View* view, int x, int y);
void tv_view_grow_to(tv_View* view, int x, int y);

/* View state management */
tv_ushort tv_view_get_state(tv_View* view);
void tv_view_set_state(tv_View* view, tv_ushort state, tv_bool enable);
tv_bool tv_view_get_state_flag(tv_View* view, tv_ushort flag);

/* View options */
tv_ushort tv_view_get_options(tv_View* view);
void tv_view_set_options(tv_View* view, tv_ushort options, tv_bool enable);

/* View visibility */
void tv_view_show(tv_View* view);
void tv_view_hide(tv_View* view);
tv_bool tv_view_exposed(tv_View* view);

/* View focus */
tv_bool tv_view_focus(tv_View* view);

/* View drawing */
void tv_view_draw(tv_View* view);
void tv_view_draw_view(tv_View* view);

/* Cursor management */
void tv_view_set_cursor(tv_View* view, int x, int y);
void tv_view_show_cursor(tv_View* view);
void tv_view_hide_cursor(tv_View* view);
void tv_view_block_cursor(tv_View* view);
void tv_view_normal_cursor(tv_View* view);

/* Event handling */
void tv_view_handle_event(tv_View* view, tv_EventHandle* event);
void tv_view_get_event(tv_View* view, tv_EventHandle* event);
void tv_view_put_event(tv_View* view, tv_EventHandle* event);
void tv_view_clear_event(tv_View* view, tv_EventHandle* event);
tv_bool tv_view_event_avail(tv_View* view);

/* Data transfer */
tv_ushort tv_view_data_size(tv_View* view);
void tv_view_get_data(tv_View* view, void* rec);
void tv_view_set_data(tv_View* view, void* rec);

/* Validation */
tv_bool tv_view_valid(tv_View* view, tv_ushort command);

/* Help context */
tv_ushort tv_view_get_help_ctx(tv_View* view);

/* Mouse interaction */
tv_bool tv_view_mouse_in_view(tv_View* view, tv_Point mouse);
tv_bool tv_view_contains_mouse(tv_View* view, tv_EventHandle* event);

/* Command support */
tv_bool tv_view_command_enabled(tv_ushort command);
void tv_view_enable_command(tv_ushort command);
void tv_view_disable_command(tv_ushort command);
void tv_view_enable_commands(tv_ushort* commands, int count);
void tv_view_disable_commands(tv_ushort* commands, int count);

#ifdef __cplusplus
}
#endif

#endif /* TV_VIEW_H */

// Made with Bob
