//
// Created by Jason Lee on 1/28/26.
//

#include "ctypes.h"
#include "cvision.h"
#include <stdio.h>

/* Command constants */
const ushort
        cmNewWindow = 100,
        cmListDemo = 101,
        cmEditorDemo = 102,
        cmAbout = 103;

tv_StatusLine* createStatusLine(const tv_Rect r) {
    tv_StatusItem* items =
        tv_statusitem_create("~F2~ New", kbF2, cmNewWindow,
        tv_statusitem_create("~F3~ List", kbF3, cmListDemo,
        tv_statusitem_create("~F4~ Editor", kbF4, cmEditorDemo,
    tv_statusitem_create("~Alt+X~ Exit", 0, cmQuit, NULL))));

    return tv_statusline_create(tv_rect_make(r.ax, r.by-1, r.bx, r.by ), items);
}

tv_MenuBar* createMenuBar(tv_Rect r) {
    /* Create menu items */
    tv_SubMenu* about_menu = tv_submenu_create("~\xF0~", kbAltSpace);
    tv_submenu_add_menuitem(about_menu, tv_menuitem_create("~A~bout...", cmAbout, kbAltA, NULL, NULL));


    tv_SubMenu* file_menu = tv_submenu_create("~F~ile", kbAltF);
    tv_submenu_add_menuitem(file_menu, tv_menuitem_create("~N~ew Window", cmNewWindow, kbF2, NULL, NULL));
    tv_submenu_add_menuitem(file_menu, tv_menuitem_create("~L~ist Demo", cmListDemo, kbF3, NULL, NULL));
    tv_submenu_add_menuitem(file_menu, tv_menuitem_create("~E~ditor Demo", cmEditorDemo, kbF4, NULL, NULL));
    tv_submenu_add_menuitem(file_menu, tv_menuitem_create("E~x~it", cmQuit, 0, NULL, NULL));


    tv_submenu_add_next(about_menu, file_menu);
    /* Create menu bar */
    return tv_menubar_create(tv_rect_make(r.ax, r.ay, r.bx, r.ay + 1 ), about_menu);
}


tv_Application* app;

void handleEvent(tv_Event e) {
    if (e.what == cmQuit) {
        tv_application_destroy(app);
    }

    switch( e.data.message.command ) {
        case cmNewWindow:
        case cmListDemo:
        case cmEditorDemo:
            break;
        case cmAbout:
           tv_message_box("This is a demo application of the C wrapper for magiblot's Turbo Vision library.", 0x0001 | 0x0400 );
            break;
        default:
            return ;
    }
}

int main(void) {
    app = tv_application_create(createStatusLine, createMenuBar, handleEvent);

    if (!app) {
        fprintf(stderr, "Failed to create application\n");
        return 1;
    }

    tv_application_run(app);

    /* Clean up application */
    tv_application_destroy(app);

    return 0;
}