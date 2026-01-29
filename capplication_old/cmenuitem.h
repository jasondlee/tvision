/*----------------------------------------------------------*/
/*                                                          */
/*   cmenuitem.h - C wrappers for TMenuItem and TSubMenu   */
/*                                                          */
/*   C interface for building Turbo Vision menus from C    */
/*                                                          */
/*----------------------------------------------------------*/

#ifndef CMENUITEM_H
#define CMENUITEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque handles for C code */
typedef struct TMenuItem_C TMenuItem_C;
typedef struct TSubMenu_C TSubMenu_C;
typedef struct TMenu_C TMenu_C;

/*
 * TMenuItem functions
 */

/* Create a new menu item with command */
TMenuItem_C* c_menuitem_new(
    const char* name,
    unsigned short command,
    unsigned short key,
    unsigned short helpCtx,
    const char* param
);

/* Create a new menu item with submenu */
TMenuItem_C* c_menuitem_new_submenu(
    const char* name,
    unsigned short key,
    TMenu_C* subMenu,
    unsigned short helpCtx
);

/* Create a separator line */
TMenuItem_C* c_menuitem_newline(void);

/* Destroy a menu item (and its chain) */
void c_menuitem_destroy(TMenuItem_C* item);

/* Append one menu item to another (operator +) */
TMenuItem_C* c_menuitem_append(TMenuItem_C* item1, TMenuItem_C* item2);

/*
 * TSubMenu functions
 */

/* Create a new submenu */
TSubMenu_C* c_submenu_new(
    const char* name,
    unsigned short key,
    unsigned short helpCtx
);

/* Destroy a submenu */
void c_submenu_destroy(TSubMenu_C* submenu);

/* Add a menu item to a submenu (operator +) */
TSubMenu_C* c_submenu_add_item(TSubMenu_C* submenu, TMenuItem_C* item);

/* Add a submenu to another submenu (operator +) */
TSubMenu_C* c_submenu_add_submenu(TSubMenu_C* submenu1, TSubMenu_C* submenu2);

/* Convert TSubMenu to TMenuItem (for chaining) */
TMenuItem_C* c_submenu_to_menuitem(TSubMenu_C* submenu);

/*
 * TMenu functions
 */

/* Create a new menu from a menu item */
TMenu_C* c_menu_new(TMenuItem_C* itemList);

/* Create a new menu with default item */
TMenu_C* c_menu_new_with_default(TMenuItem_C* itemList, TMenuItem_C* defaultItem);

/* Destroy a menu */
void c_menu_destroy(TMenu_C* menu);

/* Get the underlying TMenu pointer (for use with TMenuBar constructor) */
void* c_menu_get_ptr(TMenu_C* menu);

/* Get the underlying TSubMenu reference (for use with TMenuBar constructor) */
void* c_submenu_get_ptr(TSubMenu_C* submenu);

#ifdef __cplusplus
}
#endif

#endif /* CMENUITEM_H */

// Made with Bob
