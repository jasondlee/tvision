/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_LISTS.H                                                            */
/*                                                                         */
/*   C wrapper for Turbo Vision list/viewer classes                       */
/*   (TScroller, TListViewer, TListBox)                                   */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_LISTS_H
#define TV_LISTS_H

#include "tv_types.h"
#include "tv_view.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque pointers */
typedef struct tv_Scroller tv_Scroller;
typedef struct tv_ListViewer tv_ListViewer;
typedef struct tv_ListBox tv_ListBox;
typedef struct tv_ScrollBar tv_ScrollBar;
typedef struct tv_Collection tv_Collection;

/* Scroll bar part codes */
#define TV_SB_LEFT_ARROW    0
#define TV_SB_RIGHT_ARROW   1
#define TV_SB_PAGE_LEFT     2
#define TV_SB_PAGE_RIGHT    3
#define TV_SB_UP_ARROW      4
#define TV_SB_DOWN_ARROW    5
#define TV_SB_PAGE_UP       6
#define TV_SB_PAGE_DOWN     7
#define TV_SB_INDICATOR     8

/* Scroll bar options */
#define TV_SB_HORIZONTAL    0x0000
#define TV_SB_VERTICAL      0x0001
#define TV_SB_HANDLE_KEYBOARD 0x0002

/* TScrollBar functions */
tv_ScrollBar* tv_scrollbar_create(tv_Rect bounds, tv_ushort options);
void tv_scrollbar_destroy(tv_ScrollBar* scrollbar);
void tv_scrollbar_set_params(tv_ScrollBar* scrollbar, int value, int min, int max, int page_size);
int tv_scrollbar_get_value(tv_ScrollBar* scrollbar);
void tv_scrollbar_set_value(tv_ScrollBar* scrollbar, int value);
void tv_scrollbar_set_range(tv_ScrollBar* scrollbar, int min, int max);
void tv_scrollbar_set_step(tv_ScrollBar* scrollbar, int step);

/* Cast functions */
tv_View* tv_scrollbar_to_view(tv_ScrollBar* scrollbar);
tv_ScrollBar* tv_view_to_scrollbar(tv_View* view);

/* TScroller functions */
tv_Scroller* tv_scroller_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar, tv_ScrollBar* v_scrollbar);
void tv_scroller_destroy(tv_Scroller* scroller);
void tv_scroller_set_limit(tv_Scroller* scroller, int x, int y);
void tv_scroller_scroll_to(tv_Scroller* scroller, int x, int y);
void tv_scroller_scroll_draw(tv_Scroller* scroller);
tv_Point tv_scroller_get_delta(tv_Scroller* scroller);

/* Cast functions */
tv_View* tv_scroller_to_view(tv_Scroller* scroller);
tv_Scroller* tv_view_to_scroller(tv_View* view);

/* TListViewer functions */
tv_ListViewer* tv_listviewer_create(tv_Rect bounds, tv_ushort num_cols, 
                                     tv_ScrollBar* h_scrollbar, tv_ScrollBar* v_scrollbar);
void tv_listviewer_destroy(tv_ListViewer* viewer);
void tv_listviewer_set_range(tv_ListViewer* viewer, int range);
int tv_listviewer_get_range(tv_ListViewer* viewer);
void tv_listviewer_focus_item(tv_ListViewer* viewer, int item);
int tv_listviewer_get_focused(tv_ListViewer* viewer);
void tv_listviewer_select_item(tv_ListViewer* viewer, int item);
tv_bool tv_listviewer_is_selected(tv_ListViewer* viewer, int item);

/* Cast functions */
tv_View* tv_listviewer_to_view(tv_ListViewer* viewer);
tv_Scroller* tv_listviewer_to_scroller(tv_ListViewer* viewer);
tv_ListViewer* tv_view_to_listviewer(tv_View* view);
tv_ListViewer* tv_scroller_to_listviewer(tv_Scroller* scroller);

/* TCollection functions (for use with TListBox) */
tv_Collection* tv_collection_create(int limit, int delta);
void tv_collection_destroy(tv_Collection* collection);
void tv_collection_insert(tv_Collection* collection, void* item);
void tv_collection_at_insert(tv_Collection* collection, int index, void* item);
void* tv_collection_at(tv_Collection* collection, int index);
void tv_collection_at_free(tv_Collection* collection, int index);
void tv_collection_at_remove(tv_Collection* collection, int index);
void tv_collection_free_all(tv_Collection* collection);
int tv_collection_get_count(tv_Collection* collection);

/* String collection helpers */
tv_Collection* tv_string_collection_create(void);
void tv_string_collection_insert(tv_Collection* collection, const char* str);
const char* tv_string_collection_at(tv_Collection* collection, int index);

/* TListBox functions */
tv_ListBox* tv_listbox_create(tv_Rect bounds, tv_ushort num_cols, tv_ScrollBar* scrollbar);
void tv_listbox_destroy(tv_ListBox* listbox);
void tv_listbox_set_list(tv_ListBox* listbox, tv_Collection* list);
tv_Collection* tv_listbox_get_list(tv_ListBox* listbox);
void tv_listbox_new_list(tv_ListBox* listbox, tv_Collection* list);
int tv_listbox_get_selection(tv_ListBox* listbox);
void tv_listbox_set_selection(tv_ListBox* listbox, int index);

/* Cast functions */
tv_View* tv_listbox_to_view(tv_ListBox* listbox);
tv_Scroller* tv_listbox_to_scroller(tv_ListBox* listbox);
tv_ListViewer* tv_listbox_to_listviewer(tv_ListBox* listbox);
tv_ListBox* tv_view_to_listbox(tv_View* view);
tv_ListBox* tv_listviewer_to_listbox(tv_ListViewer* viewer);

#ifdef __cplusplus
}
#endif

#endif /* TV_LISTS_H */

// Made with Bob
