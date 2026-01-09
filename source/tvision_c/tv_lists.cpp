/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_LISTS.CPP                                                          */
/*                                                                         */
/*   C wrapper implementation for list/viewer classes                     */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_TScroller
#define Uses_TListViewer
#define Uses_TListBox
#define Uses_TScrollBar
#define Uses_TCollection
#define Uses_TLineCollection
#define Uses_TStringCollection
#define Uses_TRect
#include <tvision/tv.h>

#include "tvision_c/tv_lists.h"
#include <cstring>

extern "C" {

/* TScrollBar functions */

tv_ScrollBar* tv_scrollbar_create(tv_Rect bounds, tv_ushort options) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_ScrollBar*>(new TScrollBar(rect));
}

void tv_scrollbar_destroy(tv_ScrollBar* scrollbar) {
    if (scrollbar) {
        TObject::destroy(reinterpret_cast<TScrollBar*>(scrollbar));
    }
}

void tv_scrollbar_set_params(tv_ScrollBar* scrollbar, int value, int min, int max, int page_size) {
    reinterpret_cast<TScrollBar*>(scrollbar)->setParams(value, min, max, page_size, 1);
}

int tv_scrollbar_get_value(tv_ScrollBar* scrollbar) {
    return reinterpret_cast<TScrollBar*>(scrollbar)->value;
}

void tv_scrollbar_set_value(tv_ScrollBar* scrollbar, int value) {
    reinterpret_cast<TScrollBar*>(scrollbar)->setValue(value);
}

void tv_scrollbar_set_range(tv_ScrollBar* scrollbar, int min, int max) {
    TScrollBar* sb = reinterpret_cast<TScrollBar*>(scrollbar);
    sb->setParams(sb->value, min, max, sb->pgStep, sb->arStep);
}

void tv_scrollbar_set_step(tv_ScrollBar* scrollbar, int step) {
    TScrollBar* sb = reinterpret_cast<TScrollBar*>(scrollbar);
    sb->setParams(sb->value, sb->minVal, sb->maxVal, sb->pgStep, step);
}

tv_View* tv_scrollbar_to_view(tv_ScrollBar* scrollbar) {
    return reinterpret_cast<tv_View*>(scrollbar);
}

tv_ScrollBar* tv_view_to_scrollbar(tv_View* view) {
    return reinterpret_cast<tv_ScrollBar*>(view);
}

/* TScroller functions */

tv_Scroller* tv_scroller_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar, tv_ScrollBar* v_scrollbar) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Scroller*>(
        new TScroller(rect, 
                     reinterpret_cast<TScrollBar*>(h_scrollbar),
                     reinterpret_cast<TScrollBar*>(v_scrollbar))
    );
}

void tv_scroller_destroy(tv_Scroller* scroller) {
    if (scroller) {
        TObject::destroy(reinterpret_cast<TScroller*>(scroller));
    }
}

void tv_scroller_set_limit(tv_Scroller* scroller, int x, int y) {
    reinterpret_cast<TScroller*>(scroller)->setLimit(x, y);
}

void tv_scroller_scroll_to(tv_Scroller* scroller, int x, int y) {
    reinterpret_cast<TScroller*>(scroller)->scrollTo(x, y);
}

void tv_scroller_scroll_draw(tv_Scroller* scroller) {
    reinterpret_cast<TScroller*>(scroller)->scrollDraw();
}

tv_Point tv_scroller_get_delta(tv_Scroller* scroller) {
    TPoint delta = reinterpret_cast<TScroller*>(scroller)->delta;
    tv_Point result;
    result.x = delta.x;
    result.y = delta.y;
    return result;
}

tv_View* tv_scroller_to_view(tv_Scroller* scroller) {
    return reinterpret_cast<tv_View*>(scroller);
}

tv_Scroller* tv_view_to_scroller(tv_View* view) {
    return reinterpret_cast<tv_Scroller*>(view);
}

/* TListViewer functions */

tv_ListViewer* tv_listviewer_create(tv_Rect bounds, tv_ushort num_cols,
                                     tv_ScrollBar* h_scrollbar, tv_ScrollBar* v_scrollbar) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_ListViewer*>(
        new TListViewer(rect, num_cols,
                       reinterpret_cast<TScrollBar*>(h_scrollbar),
                       reinterpret_cast<TScrollBar*>(v_scrollbar))
    );
}

void tv_listviewer_destroy(tv_ListViewer* viewer) {
    if (viewer) {
        TObject::destroy(reinterpret_cast<TListViewer*>(viewer));
    }
}

void tv_listviewer_set_range(tv_ListViewer* viewer, int range) {
    reinterpret_cast<TListViewer*>(viewer)->setRange(range);
}

int tv_listviewer_get_range(tv_ListViewer* viewer) {
    return reinterpret_cast<TListViewer*>(viewer)->range;
}

void tv_listviewer_focus_item(tv_ListViewer* viewer, int item) {
    reinterpret_cast<TListViewer*>(viewer)->focusItem(item);
}

int tv_listviewer_get_focused(tv_ListViewer* viewer) {
    return reinterpret_cast<TListViewer*>(viewer)->focused;
}

void tv_listviewer_select_item(tv_ListViewer* viewer, int item) {
    reinterpret_cast<TListViewer*>(viewer)->selectItem(item);
}

tv_bool tv_listviewer_is_selected(tv_ListViewer* viewer, int item) {
    return reinterpret_cast<TListViewer*>(viewer)->isSelected(item) ? TV_TRUE : TV_FALSE;
}

tv_View* tv_listviewer_to_view(tv_ListViewer* viewer) {
    return reinterpret_cast<tv_View*>(viewer);
}

tv_Scroller* tv_listviewer_to_scroller(tv_ListViewer* viewer) {
    return reinterpret_cast<tv_Scroller*>(viewer);
}

tv_ListViewer* tv_view_to_listviewer(tv_View* view) {
    return reinterpret_cast<tv_ListViewer*>(view);
}

tv_ListViewer* tv_scroller_to_listviewer(tv_Scroller* scroller) {
    return reinterpret_cast<tv_ListViewer*>(scroller);
}

/* String collection helpers */

tv_Collection* tv_string_collection_create(void) {
    return reinterpret_cast<tv_Collection*>(new TStringCollection(10, 10));
}

void tv_string_collection_insert(tv_Collection* collection, const char* str) {
    if (str) {
        char* new_str = newStr(str);
        reinterpret_cast<TStringCollection*>(collection)->insert(new_str);
    }
}

const char* tv_string_collection_at(tv_Collection* collection, int index) {
    return static_cast<const char*>(reinterpret_cast<TStringCollection*>(collection)->at(index));
}

/* TListBox functions */

tv_ListBox* tv_listbox_create(tv_Rect bounds, tv_ushort num_cols, tv_ScrollBar* scrollbar) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_ListBox*>(
        new TListBox(rect, num_cols, reinterpret_cast<TScrollBar*>(scrollbar))
    );
}

void tv_listbox_destroy(tv_ListBox* listbox) {
    if (listbox) {
        TObject::destroy(reinterpret_cast<TListBox*>(listbox));
    }
}

/*
void tv_listbox_set_list(tv_ListBox* listbox, tv_Collection* list) {
    reinterpret_cast<TListBox*>(listbox)->list = reinterpret_cast<TCollection*>(list);
}

tv_Collection* tv_listbox_get_list(tv_ListBox* listbox) {
    return reinterpret_cast<tv_Collection*>(reinterpret_cast<TListBox*>(listbox)->list);
}
*/

void tv_listbox_new_list(tv_ListBox* listbox, tv_Collection* list) {
    reinterpret_cast<TListBox*>(listbox)->newList(reinterpret_cast<TCollection*>(list));
}

int tv_listbox_get_selection(tv_ListBox* listbox) {
    return reinterpret_cast<TListBox*>(listbox)->focused;
}

void tv_listbox_set_selection(tv_ListBox* listbox, int index) {
    reinterpret_cast<TListBox*>(listbox)->focusItem(index);
}

tv_View* tv_listbox_to_view(tv_ListBox* listbox) {
    return reinterpret_cast<tv_View*>(listbox);
}

tv_Scroller* tv_listbox_to_scroller(tv_ListBox* listbox) {
    return reinterpret_cast<tv_Scroller*>(listbox);
}

tv_ListViewer* tv_listbox_to_listviewer(tv_ListBox* listbox) {
    return reinterpret_cast<tv_ListViewer*>(listbox);
}

tv_ListBox* tv_view_to_listbox(tv_View* view) {
    return reinterpret_cast<tv_ListBox*>(view);
}

tv_ListBox* tv_listviewer_to_listbox(tv_ListViewer* viewer) {
    return reinterpret_cast<tv_ListBox*>(viewer);
}

} /* extern "C" */

// Made with Bob
