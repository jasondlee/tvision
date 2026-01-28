/*----------------------------------------------------------*/
/*                                                          */
/*   example.c - Example usage of capplication C wrappers  */
/*                                                          */
/*   Demonstrates building a TApplication from C code      */
/*                                                          */
/*----------------------------------------------------------*/

#include "capplication.h"
#include "../cmenuitem/cmenuitem.h"
#include "../cstatusline/cstatusline.h"
#include <stdio.h>

/*
 * This example recreates the TEditorApp from tvedit.cpp
 * using pure C code with the capplication, cmenuitem, and cstatusline wrappers.
 */

/* Build the menu bar (similar to TEditorApp::initMenuBar) */
TSubMenu_C* build_menubar(void)
{
    /* File menu */
    TMenuItem_C* file_open = c_menuitem_new("~O~pen", C_cmOpen, C_kbF3, C_hcNoContext, "F3");
    TMenuItem_C* file_new = c_menuitem_new("~N~ew", C_cmNew, C_kbCtrlN, C_hcNoContext, "Ctrl-N");
    TMenuItem_C* file_save = c_menuitem_new("~S~ave", C_cmSave, C_kbF2, C_hcNoContext, "F2");
    TMenuItem_C* file_saveas = c_menuitem_new("S~a~ve as...", C_cmSaveAs, C_kbNoKey, C_hcNoContext, NULL);
    TMenuItem_C* file_line1 = c_menuitem_newline();
    TMenuItem_C* file_chdir = c_menuitem_new("~C~hange dir...", C_cmChangeDrct, C_kbNoKey, C_hcNoContext, NULL);
    TMenuItem_C* file_dos = c_menuitem_new("~D~OS shell", C_cmDosShell, C_kbNoKey, C_hcNoContext, NULL);
    TMenuItem_C* file_exit = c_menuitem_new("E~x~it", C_cmQuit, C_kbCtrlQ, C_hcNoContext, "Ctrl-Q");
    
    TMenuItem_C* file_items = c_menuitem_append(file_open, file_new);
    file_items = c_menuitem_append(file_items, file_save);
    file_items = c_menuitem_append(file_items, file_saveas);
    file_items = c_menuitem_append(file_items, file_line1);
    file_items = c_menuitem_append(file_items, file_chdir);
    file_items = c_menuitem_append(file_items, file_dos);
    file_items = c_menuitem_append(file_items, file_exit);
    
    TSubMenu_C* file_menu = c_submenu_new("~F~ile", C_kbAltF, C_hcNoContext);
    file_menu = c_submenu_add_item(file_menu, file_items);
    
    /* Edit menu */
    TMenuItem_C* edit_undo = c_menuitem_new("~U~ndo", C_cmUndo, C_kbCtrlU, C_hcNoContext, "Ctrl-U");
    TMenuItem_C* edit_line1 = c_menuitem_newline();
    TMenuItem_C* edit_cut = c_menuitem_new("Cu~t~", C_cmCut, C_kbShiftDel, C_hcNoContext, "Shift-Del");
    TMenuItem_C* edit_copy = c_menuitem_new("~C~opy", C_cmCopy, C_kbCtrlIns, C_hcNoContext, "Ctrl-Ins");
    TMenuItem_C* edit_paste = c_menuitem_new("~P~aste", C_cmPaste, C_kbShiftIns, C_hcNoContext, "Shift-Ins");
    TMenuItem_C* edit_line2 = c_menuitem_newline();
    TMenuItem_C* edit_clear = c_menuitem_new("~C~lear", C_cmClear, C_kbCtrlDel, C_hcNoContext, "Ctrl-Del");
    
    TMenuItem_C* edit_items = c_menuitem_append(edit_undo, edit_line1);
    edit_items = c_menuitem_append(edit_items, edit_cut);
    edit_items = c_menuitem_append(edit_items, edit_copy);
    edit_items = c_menuitem_append(edit_items, edit_paste);
    edit_items = c_menuitem_append(edit_items, edit_line2);
    edit_items = c_menuitem_append(edit_items, edit_clear);
    
    TSubMenu_C* edit_menu = c_submenu_new("~E~dit", C_kbAltE, C_hcNoContext);
    edit_menu = c_submenu_add_item(edit_menu, edit_items);
    
    /* Search menu */
    TMenuItem_C* search_find = c_menuitem_new("~F~ind...", C_cmFind, C_kbNoKey, C_hcNoContext, NULL);
    TMenuItem_C* search_replace = c_menuitem_new("~R~eplace...", C_cmReplace, C_kbNoKey, C_hcNoContext, NULL);
    TMenuItem_C* search_again = c_menuitem_new("~S~earch again", C_cmSearchAgain, C_kbNoKey, C_hcNoContext, NULL);
    
    TMenuItem_C* search_items = c_menuitem_append(search_find, search_replace);
    search_items = c_menuitem_append(search_items, search_again);
    
    TSubMenu_C* search_menu = c_submenu_new("~S~earch", C_kbAltS, C_hcNoContext);
    search_menu = c_submenu_add_item(search_menu, search_items);
    
    /* Windows menu */
    TMenuItem_C* win_resize = c_menuitem_new("~S~ize/move", C_cmResize, C_kbCtrlF5, C_hcNoContext, "Ctrl-F5");
    TMenuItem_C* win_zoom = c_menuitem_new("~Z~oom", C_cmZoom, C_kbF5, C_hcNoContext, "F5");
    TMenuItem_C* win_tile = c_menuitem_new("~T~ile", C_cmTile, C_kbNoKey, C_hcNoContext, NULL);
    TMenuItem_C* win_cascade = c_menuitem_new("C~a~scade", C_cmCascade, C_kbNoKey, C_hcNoContext, NULL);
    TMenuItem_C* win_next = c_menuitem_new("~N~ext", C_cmNext, C_kbF6, C_hcNoContext, "F6");
    TMenuItem_C* win_prev = c_menuitem_new("~P~revious", C_cmPrev, C_kbShiftF6, C_hcNoContext, "Shift-F6");
    TMenuItem_C* win_close = c_menuitem_new("~C~lose", C_cmClose, C_kbCtrlW, C_hcNoContext, "Ctrl+W");
    
    TMenuItem_C* win_items = c_menuitem_append(win_resize, win_zoom);
    win_items = c_menuitem_append(win_items, win_tile);
    win_items = c_menuitem_append(win_items, win_cascade);
    win_items = c_menuitem_append(win_items, win_next);
    win_items = c_menuitem_append(win_items, win_prev);
    win_items = c_menuitem_append(win_items, win_close);
    
    TSubMenu_C* win_menu = c_submenu_new("~W~indows", C_kbAltW, C_hcNoContext);
    win_menu = c_submenu_add_item(win_menu, win_items);
    
    /* Combine all menus */
    TSubMenu_C* menubar = file_menu;
    menubar = c_submenu_add_submenu(menubar, edit_menu);
    menubar = c_submenu_add_submenu(menubar, search_menu);
    menubar = c_submenu_add_submenu(menubar, win_menu);
    
    return menubar;
}

/* Build the status line (similar to TEditorApp::initStatusLine) */
TStatusDef_C* build_statusline(void)
{
    TStatusItem_C* item1 = c_statusitem_new(NULL, C_kbAltX, C_cmQuit);
    TStatusItem_C* item2 = c_statusitem_new("~F2~ Save", C_kbF2, C_cmSave);
    TStatusItem_C* item3 = c_statusitem_new("~F3~ Open", C_kbF3, C_cmOpen);
    TStatusItem_C* item4 = c_statusitem_new("~Ctrl-W~ Close", C_kbAltF3, C_cmClose);
    TStatusItem_C* item5 = c_statusitem_new("~F5~ Zoom", C_kbF5, C_cmZoom);
    TStatusItem_C* item6 = c_statusitem_new("~F6~ Next", C_kbF6, C_cmNext);
    TStatusItem_C* item7 = c_statusitem_new("~F10~ Menu", C_kbF10, C_cmMenu);
    TStatusItem_C* item8 = c_statusitem_new(NULL, C_kbShiftDel, C_cmCut);
    TStatusItem_C* item9 = c_statusitem_new(NULL, C_kbCtrlIns, C_cmCopy);
    TStatusItem_C* item10 = c_statusitem_new(NULL, C_kbShiftIns, C_cmPaste);
    TStatusItem_C* item11 = c_statusitem_new(NULL, C_kbCtrlF5, C_cmResize);
    
    TStatusItem_C* items = c_statusitem_append(item1, item2);
    items = c_statusitem_append(items, item3);
    items = c_statusitem_append(items, item4);
    items = c_statusitem_append(items, item5);
    items = c_statusitem_append(items, item6);
    items = c_statusitem_append(items, item7);
    items = c_statusitem_append(items, item8);
    items = c_statusitem_append(items, item9);
    items = c_statusitem_append(items, item10);
    items = c_statusitem_append(items, item11);
    
    TStatusDef_C* statusdef = c_statusdef_new(0, 0xFFFF, items);
    
    return statusdef;
}

int main(int argc, char** argv)
{
    printf("=== capplication C Wrapper Example ===\n\n");
    printf("This example demonstrates building a Turbo Vision application\n");
    printf("from C code using the capplication, cmenuitem, and cstatusline wrappers.\n\n");
    printf("Creating an editor-like application similar to TEditorApp...\n\n");
    
    /* Build the menu bar */
    TSubMenu_C* menubar = build_menubar();
    
    /* Build the status line */
    TStatusDef_C* statusline = build_statusline();
    
    /* Create the application using the builder pattern */
    TApplicationBuilder_C* builder = c_application_builder_new();
    
    /* Configure the application */
    builder = c_application_builder_set_menubar(builder, menubar);
    builder = c_application_builder_set_statusline(builder, statusline);
    
    /* Disable editor commands initially (like TEditorApp does) */
    // builder = c_application_builder_disable_command(builder, C_cmSave);
    // builder = c_application_builder_disable_command(builder, C_cmSaveAs);
    // builder = c_application_builder_disable_command(builder, C_cmCut);
    // builder = c_application_builder_disable_command(builder, C_cmCopy);
    // builder = c_application_builder_disable_command(builder, C_cmPaste);
    // builder = c_application_builder_disable_command(builder, C_cmClear);
    // builder = c_application_builder_disable_command(builder, C_cmUndo);
    // builder = c_application_builder_disable_command(builder, C_cmFind);
    // builder = c_application_builder_disable_command(builder, C_cmReplace);
    // builder = c_application_builder_disable_command(builder, C_cmSearchAgain);
    
    /* Build the application (this consumes the builder) */
    TApplication_C* app = c_application_builder_build(builder);
    
    if (app) {
        /* Run the application */
        c_application_run(app);
        
        /* Shut down and clean up */
        c_application_shutdown(app);
        c_application_destroy(app);
        
        printf("\nApplication terminated successfully.\n");
        return 0;
    } else {
        printf("ERROR: Failed to create application!\n");
        return 1;
    }
}

// Made with Bob