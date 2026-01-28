/*----------------------------------------------------------*/
/*                                                          */
/*   example.c - Example usage of cmenuitem C wrappers     */
/*                                                          */
/*   Demonstrates building TMenuBar from C code            */
/*                                                          */
/*----------------------------------------------------------*/

#include "cmenuitem.h"
#include <stdio.h>

/*
 * This example demonstrates how to build a menu structure
 * similar to the one in tvedit3.cpp's initMenuBar function,
 * but using pure C code with the cmenuitem wrappers.
 */

/* Command constants (would normally be in a header) */
#define cmOpen        100
#define cmNew         101
#define cmSave        102
#define cmSaveAs      103
#define cmChangeDrct  104
#define cmDosShell    105
#define cmQuit        106
#define cmUndo        200
#define cmCut         201
#define cmCopy        202
#define cmPaste       203
#define cmClear       204
#define cmFind        300
#define cmReplace     301
#define cmSearchAgain 302
#define cmResize      400
#define cmZoom        401
#define cmTile        402
#define cmCascade     403
#define cmNext        404
#define cmPrev        405
#define cmClose       406

void example_build_menu(void)
{
    TSubMenu_C* sub1;
    TSubMenu_C* sub2;
    TSubMenu_C* sub3;
    TSubMenu_C* sub4;
    TMenuItem_C* item;
    
    printf("Building File submenu...\n");
    
    /* Build File submenu */
    sub1 = c_submenu_new("~F~ile", C_kbAltF, C_hcNoContext);
    
    item = c_menuitem_new("~O~pen", cmOpen, C_kbF3, C_hcNoContext, "F3");
    sub1 = c_submenu_add_item(sub1, item);
    
    item = c_menuitem_new("~N~ew", cmNew, C_kbCtrlN, C_hcNoContext, "Ctrl-N");
    sub1 = c_submenu_add_item(sub1, item);
    
    item = c_menuitem_new("~S~ave", cmSave, C_kbF2, C_hcNoContext, "F2");
    sub1 = c_submenu_add_item(sub1, item);
    
    item = c_menuitem_new("S~a~ve as...", cmSaveAs, C_kbNoKey, C_hcNoContext, NULL);
    sub1 = c_submenu_add_item(sub1, item);
    
    item = c_menuitem_newline();
    sub1 = c_submenu_add_item(sub1, item);
    
    item = c_menuitem_new("~C~hange dir...", cmChangeDrct, C_kbNoKey, C_hcNoContext, NULL);
    sub1 = c_submenu_add_item(sub1, item);
    
    item = c_menuitem_new("~D~OS shell", cmDosShell, C_kbNoKey, C_hcNoContext, NULL);
    sub1 = c_submenu_add_item(sub1, item);
    
    item = c_menuitem_new("E~x~it", cmQuit, C_kbCtrlQ, C_hcNoContext, "Ctrl-Q");
    sub1 = c_submenu_add_item(sub1, item);
    
    printf("Building Edit submenu...\n");
    
    /* Build Edit submenu */
    sub2 = c_submenu_new("~E~dit", C_kbAltE, C_hcNoContext);
    
    item = c_menuitem_new("~U~ndo", cmUndo, C_kbCtrlU, C_hcNoContext, "Ctrl-U");
    sub2 = c_submenu_add_item(sub2, item);
    
    item = c_menuitem_newline();
    sub2 = c_submenu_add_item(sub2, item);
    
    item = c_menuitem_new("Cu~t~", cmCut, C_kbShiftDel, C_hcNoContext, "Shift-Del");
    sub2 = c_submenu_add_item(sub2, item);
    
    item = c_menuitem_new("~C~opy", cmCopy, C_kbCtrlIns, C_hcNoContext, "Ctrl-Ins");
    sub2 = c_submenu_add_item(sub2, item);
    
    item = c_menuitem_new("~P~aste", cmPaste, C_kbShiftIns, C_hcNoContext, "Shift-Ins");
    sub2 = c_submenu_add_item(sub2, item);
    
    item = c_menuitem_newline();
    sub2 = c_submenu_add_item(sub2, item);
    
    item = c_menuitem_new("~C~lear", cmClear, C_kbCtrlDel, C_hcNoContext, "Ctrl-Del");
    sub2 = c_submenu_add_item(sub2, item);
    
    printf("Building Search submenu...\n");
    
    /* Build Search submenu */
    sub3 = c_submenu_new("~S~earch", C_kbAltS, C_hcNoContext);
    
    item = c_menuitem_new("~F~ind...", cmFind, C_kbNoKey, C_hcNoContext, NULL);
    sub3 = c_submenu_add_item(sub3, item);
    
    item = c_menuitem_new("~R~eplace...", cmReplace, C_kbNoKey, C_hcNoContext, NULL);
    sub3 = c_submenu_add_item(sub3, item);
    
    item = c_menuitem_new("~S~earch again", cmSearchAgain, C_kbNoKey, C_hcNoContext, NULL);
    sub3 = c_submenu_add_item(sub3, item);
    
    printf("Building Windows submenu...\n");
    
    /* Build Windows submenu */
    sub4 = c_submenu_new("~W~indows", C_kbAltW, C_hcNoContext);
    
    item = c_menuitem_new("~S~ize/move", cmResize, C_kbCtrlF5, C_hcNoContext, "Ctrl-F5");
    sub4 = c_submenu_add_item(sub4, item);
    
    item = c_menuitem_new("~Z~oom", cmZoom, C_kbF5, C_hcNoContext, "F5");
    sub4 = c_submenu_add_item(sub4, item);
    
    item = c_menuitem_new("~T~ile", cmTile, C_kbNoKey, C_hcNoContext, NULL);
    sub4 = c_submenu_add_item(sub4, item);
    
    item = c_menuitem_new("C~a~scade", cmCascade, C_kbNoKey, C_hcNoContext, NULL);
    sub4 = c_submenu_add_item(sub4, item);
    
    item = c_menuitem_new("~N~ext", cmNext, C_kbF6, C_hcNoContext, "F6");
    sub4 = c_submenu_add_item(sub4, item);
    
    item = c_menuitem_new("~P~revious", cmPrev, C_kbShiftF6, C_hcNoContext, "Shift-F6");
    sub4 = c_submenu_add_item(sub4, item);
    
    item = c_menuitem_new("~C~lose", cmClose, C_kbCtrlW, C_hcNoContext, "Ctrl+W");
    sub4 = c_submenu_add_item(sub4, item);
    
    printf("Combining submenus...\n");
    
    /* Combine all submenus using operator+ */
    sub1 = c_submenu_add_submenu(sub1, sub2);
    sub1 = c_submenu_add_submenu(sub1, sub3);
    sub1 = c_submenu_add_submenu(sub1, sub4);
    
    printf("Menu structure built successfully!\n");
    printf("\nTo use this in a TMenuBar constructor:\n");
    printf("  TMenuBar* menuBar = new TMenuBar(rect, *((TSubMenu*)c_submenu_get_ptr(sub1)));\n");
    
    /* Clean up */
    c_submenu_destroy(sub1);
}

int main(void)
{
    printf("=== cmenuitem C Wrapper Example ===\n\n");
    printf("This example demonstrates building a Turbo Vision menu\n");
    printf("structure from C code using the cmenuitem wrappers.\n\n");
    
    example_build_menu();
    
    printf("\nExample completed successfully!\n");
    return 0;
}

// Made with Bob
