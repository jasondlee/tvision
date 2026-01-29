//
// Created by Jason Lee on 1/28/26.
//

#include "ctypes.h"
#include "cvision.h"
#include <stdio.h>

/* Command constants */
#define CM_NEW_WINDOW   100
#define CM_LIST_DEMO    101
#define CM_EDITOR_DEMO  102
#define CM_ABOUT        103

tv_StatusLine* createStatusLine(const tv_Rect r) {
    tv_StatusItem* items =
        tv_statusitem_create("~F2~ New", kbF2, CM_NEW_WINDOW,
        tv_statusitem_create("~F3~ List", kbF3, CM_LIST_DEMO,
        tv_statusitem_create("~F4~ Editor", kbF4, CM_EDITOR_DEMO,
    tv_statusitem_create("~Alt+X~ Exit", 0, cmQuit, NULL))));

    return tv_statusline_create(r, items);
}

tv_MenuBar* createMenuBar(tv_Rect r) {
    /* Create menu items */
    tv_MenuItem* file_menu = tv_menuitem_create("~N~ew Window", CM_NEW_WINDOW, kbF2, NULL,
        tv_menuitem_create("~L~ist Demo", CM_LIST_DEMO, kbF3, NULL,
        tv_menuitem_create("~E~ditor Demo", CM_EDITOR_DEMO, kbF4, NULL,
        tv_menuitem_create("E~x~it", cmQuit, 0, NULL, NULL))));

    tv_MenuItem* help_menu = tv_menuitem_create("~A~bout", CM_ABOUT, 0, NULL, NULL);

    tv_SubMenu* menu = tv_submenu_create("~F~ile", kbAltF);
    tv_submenu_add_menuitem(menu, file_menu);
    tv_submenu_add_menuitem(menu, help_menu);

    /* Create menu bar */
    // tv_Rect r = tv_rect_make(0, 0, 80, 1);
    return tv_menubar_create(r, menu);
}


tv_Application* app;

void handleEvent(tv_Event e) {
    //printf("Handling event: %d\n", e.what);
    if (e.what == cmQuit) {
        tv_application_destroy(app);
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