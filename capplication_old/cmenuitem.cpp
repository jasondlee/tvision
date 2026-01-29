/*----------------------------------------------------------*/
/*                                                          */
/*   cmenuitem.cpp - C wrappers for TMenuItem and TSubMenu */
/*                                                          */
/*   Implementation of C interface for Turbo Vision menus  */
/*                                                          */
/*----------------------------------------------------------*/

#define Uses_TMenuItem
#define Uses_TSubMenu
#define Uses_TMenu
#define Uses_TKeys
#include <tvision/tv.h>

#include "ckeys.h"
#include "cmenuitem.h"

/*
 * TMenuItem wrapper implementations
 */

extern "C" {

TMenuItem_C* c_menuitem_new(
    const char* name,
    unsigned short command,
    unsigned short key,
    unsigned short helpCtx,
    const char* param
)
{
    TMenuItem* item = new TMenuItem(
        name,
        command,
        key,
        helpCtx,
        param,
        nullptr
    );
    return reinterpret_cast<TMenuItem_C*>(item);
}

TMenuItem_C* c_menuitem_new_submenu(
    const char* name,
    unsigned short key,
    TMenu_C* subMenu,
    unsigned short helpCtx
)
{
    TMenu* menu = reinterpret_cast<TMenu*>(subMenu);
    TMenuItem* item = new TMenuItem(
        name,
        key,
        menu,
        helpCtx,
        nullptr
    );
    return reinterpret_cast<TMenuItem_C*>(item);
}

TMenuItem_C* c_menuitem_newline(void)
{
    TMenuItem* item = new TMenuItem(nullptr, 0, 0, hcNoContext, nullptr, nullptr);
    return reinterpret_cast<TMenuItem_C*>(item);
}

void c_menuitem_destroy(TMenuItem_C* item)
{
    if (item) {
        TMenuItem* menuItem = reinterpret_cast<TMenuItem*>(item);
        delete menuItem;
    }
}

TMenuItem_C* c_menuitem_append(TMenuItem_C* item1, TMenuItem_C* item2)
{
    if (!item1 || !item2) {
        return item1 ? item1 : item2;
    }
    
    TMenuItem* mi1 = reinterpret_cast<TMenuItem*>(item1);
    TMenuItem* mi2 = reinterpret_cast<TMenuItem*>(item2);
    
    // Use the operator+ overload
    TMenuItem& result = *mi1 + *mi2;
    return reinterpret_cast<TMenuItem_C*>(&result);
}

/*
 * TSubMenu wrapper implementations
 */

TSubMenu_C* c_submenu_new(
    const char* name,
    unsigned short key,
    unsigned short helpCtx
)
{
    TSubMenu* submenu = new TSubMenu(name, key, helpCtx);
    return reinterpret_cast<TSubMenu_C*>(submenu);
}

void c_submenu_destroy(TSubMenu_C* submenu)
{
    if (submenu) {
        TSubMenu* sub = reinterpret_cast<TSubMenu*>(submenu);
        delete sub;
    }
}

TSubMenu_C* c_submenu_add_item(TSubMenu_C* submenu, TMenuItem_C* item)
{
    if (!submenu || !item) {
        return submenu;
    }
    
    TSubMenu* sub = reinterpret_cast<TSubMenu*>(submenu);
    TMenuItem* mi = reinterpret_cast<TMenuItem*>(item);
    
    // Use the operator+ overload: TSubMenu& operator+(TSubMenu&, TMenuItem&)
    TSubMenu& result = *sub + *mi;
    return reinterpret_cast<TSubMenu_C*>(&result);
}

TSubMenu_C* c_submenu_add_submenu(TSubMenu_C* submenu1, TSubMenu_C* submenu2)
{
    if (!submenu1 || !submenu2) {
        return submenu1 ? submenu1 : submenu2;
    }
    
    TSubMenu* sub1 = reinterpret_cast<TSubMenu*>(submenu1);
    TSubMenu* sub2 = reinterpret_cast<TSubMenu*>(submenu2);
    
    // Use the operator+ overload: TSubMenu& operator+(TSubMenu&, TSubMenu&)
    TSubMenu& result = *sub1 + *sub2;
    return reinterpret_cast<TSubMenu_C*>(&result);
}

TMenuItem_C* c_submenu_to_menuitem(TSubMenu_C* submenu)
{
    if (!submenu) {
        return nullptr;
    }
    
    // TSubMenu inherits from TMenuItem, so we can safely cast
    TSubMenu* sub = reinterpret_cast<TSubMenu*>(submenu);
    TMenuItem* item = static_cast<TMenuItem*>(sub);
    return reinterpret_cast<TMenuItem_C*>(item);
}

/*
 * TMenu wrapper implementations
 */

TMenu_C* c_menu_new(TMenuItem_C* itemList)
{
    if (!itemList) {
        return nullptr;
    }
    
    TMenuItem* items = reinterpret_cast<TMenuItem*>(itemList);
    TMenu* menu = new TMenu(*items);
    return reinterpret_cast<TMenu_C*>(menu);
}

TMenu_C* c_menu_new_with_default(TMenuItem_C* itemList, TMenuItem_C* defaultItem)
{
    if (!itemList || !defaultItem) {
        return nullptr;
    }
    
    TMenuItem* items = reinterpret_cast<TMenuItem*>(itemList);
    TMenuItem* deflt = reinterpret_cast<TMenuItem*>(defaultItem);
    TMenu* menu = new TMenu(*items, *deflt);
    return reinterpret_cast<TMenu_C*>(menu);
}

void c_menu_destroy(TMenu_C* menu)
{
    if (menu) {
        TMenu* m = reinterpret_cast<TMenu*>(menu);
        delete m;
    }
}

void* c_menu_get_ptr(TMenu_C* menu)
{
    return reinterpret_cast<void*>(menu);
}

void* c_submenu_get_ptr(TSubMenu_C* submenu)
{
    return reinterpret_cast<void*>(submenu);
}

} // extern "C"

// Made with Bob
