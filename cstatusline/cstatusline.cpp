/*----------------------------------------------------------*/
/*                                                          */
/*   cstatusline.cpp - C wrappers for TStatusLine classes  */
/*                                                          */
/*   Implementation of C interface for Turbo Vision status */
/*                                                          */
/*----------------------------------------------------------*/

#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TStatusLine
#define Uses_TRect
#define Uses_TKeys
#include <tvision/tv.h>

#include "cstatusline.h"

/*
 * TStatusItem wrapper implementations
 */

extern "C" {

TStatusItem_C* c_statusitem_new(
    const char* text,
    unsigned short key,
    unsigned short command
)
{
    TStatusItem* item = new TStatusItem(text, key, command, nullptr);
    return reinterpret_cast<TStatusItem_C*>(item);
}

void c_statusitem_destroy(TStatusItem_C* item)
{
    if (item) {
        TStatusItem* statusItem = reinterpret_cast<TStatusItem*>(item);
        delete statusItem;
    }
}

TStatusItem_C* c_statusitem_append(TStatusItem_C* item1, TStatusItem_C* item2)
{
    if (!item1 || !item2) {
        return item1 ? item1 : item2;
    }
    
    TStatusItem* si1 = reinterpret_cast<TStatusItem*>(item1);
    TStatusItem* si2 = reinterpret_cast<TStatusItem*>(item2);
    
    // Manually chain the items (TStatusItem doesn't have operator+)
    // Find the end of the first chain
    TStatusItem* last = si1;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = si2;
    
    return item1;
}

/*
 * TStatusDef wrapper implementations
 */

TStatusDef_C* c_statusdef_new(
    unsigned short min,
    unsigned short max,
    TStatusItem_C* items
)
{
    TStatusItem* statusItems = reinterpret_cast<TStatusItem*>(items);
    TStatusDef* def = new TStatusDef(min, max, statusItems, nullptr);
    return reinterpret_cast<TStatusDef_C*>(def);
}

void c_statusdef_destroy(TStatusDef_C* def)
{
    if (def) {
        TStatusDef* statusDef = reinterpret_cast<TStatusDef*>(def);
        delete statusDef;
    }
}

TStatusDef_C* c_statusdef_add_item(TStatusDef_C* def, TStatusItem_C* item)
{
    if (!def || !item) {
        return def;
    }
    
    TStatusDef* sd = reinterpret_cast<TStatusDef*>(def);
    TStatusItem* si = reinterpret_cast<TStatusItem*>(item);
    
    // Use the operator+ overload: TStatusDef& operator+(TStatusDef&, TStatusItem&)
    TStatusDef& result = *sd + *si;
    return reinterpret_cast<TStatusDef_C*>(&result);
}

TStatusDef_C* c_statusdef_add_def(TStatusDef_C* def1, TStatusDef_C* def2)
{
    if (!def1 || !def2) {
        return def1 ? def1 : def2;
    }
    
    TStatusDef* sd1 = reinterpret_cast<TStatusDef*>(def1);
    TStatusDef* sd2 = reinterpret_cast<TStatusDef*>(def2);
    
    // Use the operator+ overload: TStatusDef& operator+(TStatusDef&, TStatusDef&)
    TStatusDef& result = *sd1 + *sd2;
    return reinterpret_cast<TStatusDef_C*>(&result);
}

/*
 * TStatusLine wrapper implementations
 */

TStatusLine_C* c_statusline_new(
    short ax, short ay, short bx, short by,
    TStatusDef_C* defs
)
{
    if (!defs) {
        return nullptr;
    }
    
    TRect r(ax, ay, bx, by);
    TStatusDef* statusDefs = reinterpret_cast<TStatusDef*>(defs);
    TStatusLine* statusLine = new TStatusLine(r, *statusDefs);
    return reinterpret_cast<TStatusLine_C*>(statusLine);
}

void c_statusline_destroy(TStatusLine_C* statusLine)
{
    if (statusLine) {
        TStatusLine* sl = reinterpret_cast<TStatusLine*>(statusLine);
        delete sl;
    }
}

void* c_statusline_get_ptr(TStatusLine_C* statusLine)
{
    return reinterpret_cast<void*>(statusLine);
}

void* c_statusdef_get_ptr(TStatusDef_C* def)
{
    return reinterpret_cast<void*>(def);
}

} // extern "C"

// Made with Bob
