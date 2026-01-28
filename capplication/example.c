/*----------------------------------------------------------*/
/*                                                          */
/*   example.c - Example usage of capplication C API       */
/*                                                          */
/*   Demonstrates building a TApplication from C code      */
/*                                                          */
/*----------------------------------------------------------*/

#include "capplication.h"
#include "cmenuitem.h"
#include "cstatusline.h"
#include <stdio.h>
#include <string.h>

/*
 * This example demonstrates how to build a complete Turbo Vision
 * application similar to TEditorApp from tvedit1.cpp, but using
 * pure C code with the capplication builder API.
 */

/* Command constants */
#define cmOpen        100
#define cmNew         101
#define cmSave        102
#define cmSaveAs      103
#define cmChangeDrct  104
#define cmDosShell    105
#define cmUndo        200
#define cmCut         201
#define cmCopy        202
#define cmPaste       203
#define cmClear       204
#define cmFind        300
#define cmReplace     301
#define cmSearchAgain 302

/* Global application pointer for handlers */
static TApplication_C* g_app = NULL;

/*
 * Event handlers
 */

void handle_file_open(void* app, unsigned short command, void* userData)
{
    char fileName[256];
    unsigned short result;
    
    printf("File Open handler called\n");
    
    result = c_application_exec_file_dialog(
        (TApplication_C*)app,
        "*.*",
        "Open file",
        fileName,
        sizeof(fileName)
    );
    
    if (result != C_cmQuit && result != 0) {
        printf("Selected file: %s\n", fileName);
        /* In a real app, you would open the file here */
    }
}

void handle_file_new(void* app, unsigned short command, void* userData)
{
    printf("File New handler called\n");
    /* In a real app, you would create a new editor window here */
}

void handle_change_dir(void* app, unsigned short command, void* userData)
{
    printf("Change Directory handler called\n");
    c_application_exec_chdir_dialog((TApplication_C*)app);
}

void handle_dos_shell(void* app, unsigned short command, void* userData)
{
    printf("DOS Shell handler called\n");
    /* In a real app, you would suspend and run a shell */
}

/*
 * Build the menu bar
 */
TSubMenu_C* build_menubar(void)
{
    TSubMenu_C* fileMenu;
    TSubMenu_C* editMenu;
    TSubMenu_C* searchMenu;
    TSubMenu_C* windowsMenu;
    TMenuItem_C* item;
    
    /* File menu */
    fileMenu = c_submenu_new("~F~ile", C_kbAltF, C_hcNoContext);
    
    item = c_menuitem_new("~O~pen", cmOpen, C_kbF3, C_hcNoContext, "F3");
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    item = c_menuitem_new("~N~ew", cmNew, C_kbCtrlN, C_hcNoContext, "Ctrl-N");
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    item = c_menuitem_new("~S~ave", cmSave, C_kbF2, C_hcNoContext, "F2");
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    item = c_menuitem_new("S~a~ve as...", cmSaveAs, C_kbNoKey, C_hcNoContext, NULL);
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    item = c_menuitem_newline();
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    item = c_menuitem_new("~C~hange dir...", cmChangeDrct, C_kbNoKey, C_hcNoContext, NULL);
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    item = c_menuitem_new("~D~OS shell", cmDosShell, C_kbNoKey, C_hcNoContext, NULL);
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    item = c_menuitem_new("E~x~it", C_cmQuit, C_kbCtrlQ, C_hcNoContext, "Ctrl-Q");
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    /* Edit menu */
    editMenu = c_submenu_new("~E~dit", C_kbAltE, C_hcNoContext);
    
    item = c_menuitem_new("~U~ndo", cmUndo, C_kbCtrlU, C_hcNoContext, "Ctrl-U");
    editMenu = c_submenu_add_item(editMenu, item);
    
    item = c_menuitem_newline();
    editMenu = c_submenu_add_item(editMenu, item);
    
    item = c_menuitem_new("Cu~t~", cmCut, C_kbShiftDel, C_hcNoContext, "Shift-Del");
    editMenu = c_submenu_add_item(editMenu, item);
    
    item = c_menuitem_new("~C~opy", cmCopy, C_kbCtrlIns, C_hcNoContext, "Ctrl-Ins");
    editMenu = c_submenu_add_item(editMenu, item);
    
    item = c_menuitem_new("~P~aste", cmPaste, C_kbShiftIns, C_hcNoContext, "Shift-Ins");
    editMenu = c_submenu_add_item(editMenu, item);
    
    item = c_menuitem_newline();
    editMenu = c_submenu_add_item(editMenu, item);
    
    item = c_menuitem_new("~C~lear", cmClear, C_kbCtrlDel, C_hcNoContext, "Ctrl-Del");
    editMenu = c_submenu_add_item(editMenu, item);
    
    /* Search menu */
    searchMenu = c_submenu_new("~S~earch", C_kbAltS, C_hcNoContext);
    
    item = c_menuitem_new("~F~ind...", cmFind, C_kbNoKey, C_hcNoContext, NULL);
    searchMenu = c_submenu_add_item(searchMenu, item);
    
    item = c_menuitem_new("~R~eplace...", cmReplace, C_kbNoKey, C_hcNoContext, NULL);
    searchMenu = c_submenu_add_item(searchMenu, item);
    
    item = c_menuitem_new("~S~earch again", cmSearchAgain, C_kbNoKey, C_hcNoContext, NULL);
    searchMenu = c_submenu_add_item(searchMenu, item);
    
    /* Windows menu */
    windowsMenu = c_submenu_new("~W~indows", C_kbAltW, C_hcNoContext);
    
    item = c_menuitem_new("~S~ize/move", C_cmResize, C_kbCtrlF5, C_hcNoContext, "Ctrl-F5");
    windowsMenu = c_submenu_add_item(windowsMenu, item);
    
    item = c_menuitem_new("~Z~oom", C_cmZoom, C_kbF5, C_hcNoContext, "F5");
    windowsMenu = c_submenu_add_item(windowsMenu, item);
    
    item = c_menuitem_new("~N~ext", C_cmNext, C_kbF6, C_hcNoContext, "F6");
    windowsMenu = c_submenu_add_item(windowsMenu, item);
    
    item = c_menuitem_new("~P~revious", C_cmPrev, C_kbShiftF6, C_hcNoContext, "Shift-F6");
    windowsMenu = c_submenu_add_item(windowsMenu, item);
    
    item = c_menuitem_new("~C~lose", C_cmClose, C_kbCtrlW, C_hcNoContext, "Ctrl+W");
    windowsMenu = c_submenu_add_item(windowsMenu, item);
    
    /* Combine all menus */
    fileMenu = c_submenu_add_submenu(fileMenu, editMenu);
    fileMenu = c_submenu_add_submenu(fileMenu, searchMenu);
    fileMenu = c_submenu_add_submenu(fileMenu, windowsMenu);
    
    return fileMenu;
}

/*
 * Build the status line
 */
TStatusDef_C* build_statusline(void)
{
    TStatusDef_C* statusDef;
    TStatusItem_C* item;
    
    statusDef = c_statusdef_new(0, 0xFFFF, NULL);
    
    item = c_statusitem_new(NULL, C_kbAltX, C_cmQuit);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~F2~ Save", C_kbF2, cmSave);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~F3~ Open", C_kbF3, cmOpen);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~Ctrl-W~ Close", C_kbAltF3, C_cmClose);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~F5~ Zoom", C_kbF5, C_cmZoom);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~F6~ Next", C_kbF6, C_cmNext);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~F10~ Menu", C_kbF10, C_cmMenu);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new(NULL, C_kbShiftDel, cmCut);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new(NULL, C_kbCtrlIns, cmCopy);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new(NULL, C_kbShiftIns, cmPaste);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new(NULL, C_kbCtrlF5, C_cmResize);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    return statusDef;
}

/*
 * Main application
 */
int main(int argc, char** argv)
{
    TApplication_C* app;
    TSubMenu_C* menu;
    TStatusDef_C* statusDef;
    
    /* Commands to disable initially (like TEditorApp does) */
    unsigned short disabledCommands[] = {
        cmSave, cmSaveAs, cmCut, cmCopy, cmPaste,
        cmClear, cmUndo, cmFind, cmReplace, cmSearchAgain
    };
    
    printf("=== Turbo Vision Application from C ===\n");
    printf("Building application...\n");
    
    /* Create the application */
    app = c_application_new();
    g_app = app;
    
    /* Build and set menu bar */
    printf("Building menu bar...\n");
    menu = build_menubar();
    c_application_set_menubar(app, menu);
    
    /* Build and set status line */
    printf("Building status line...\n");
    statusDef = build_statusline();
    c_application_set_statusline(app, statusDef);
    
    /* Register event handlers */
    printf("Registering event handlers...\n");
    c_application_register_handler(app, cmOpen, handle_file_open, NULL);
    c_application_register_handler(app, cmNew, handle_file_new, NULL);
    c_application_register_handler(app, cmChangeDrct, handle_change_dir, NULL);
    c_application_register_handler(app, cmDosShell, handle_dos_shell, NULL);
    
    /* Disable editor commands initially (no document open) */
    printf("Disabling editor commands...\n");
    c_application_disable_commands(app, disabledCommands, 
        sizeof(disabledCommands) / sizeof(disabledCommands[0]));
    
    /* Run the application */
    printf("Starting application...\n");
    printf("Press Alt-X or Ctrl-Q to quit\n\n");
    
    c_application_run(app);
    
    /* Clean up */
    printf("\nShutting down...\n");
    c_application_destroy(app);
    
    printf("Application terminated successfully.\n");
    return 0;
}

// Made with Bob
