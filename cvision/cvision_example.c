//
// Created by Jason Lee on 1/28/26.
//

#include "ctypes.h"
#include "cvision.h"
#include <stdio.h>

#include "ckeys.h"

/* Command constants */
#define CM_NEW_WINDOW   100
#define CM_LIST_DEMO    101
#define CM_EDITOR_DEMO  102
#define CM_ABOUT        103

/* Command codes */
#define TV_CM_VALID         0
#define TV_CM_QUIT          1
#define TV_CM_ERROR         2
#define TV_CM_MENU          3
#define TV_CM_CLOSE         4
#define TV_CM_ZOOM          5
#define TV_CM_RESIZE        6
#define TV_CM_NEXT          7
#define TV_CM_PREV          8
#define TV_CM_OK            10
#define TV_CM_CANCEL        11
#define TV_CM_YES           12
#define TV_CM_NO            13
#define TV_CM_DEFAULT       14


tv_StatusLine* createStatusLine(tv_Rect r) {
    printf("Creating status line\n");
    return NULL;
}

tv_MenuBar* createMenuBar(tv_Rect r) {
    /* Create menu items */
    tv_MenuItem* file_menu = tv_menuitem_create("~N~ew Window", CM_NEW_WINDOW, C_kbF2, NULL,
        tv_menuitem_create("~L~ist Demo", CM_LIST_DEMO, C_kbF3, NULL,
        tv_menuitem_create("~E~ditor Demo", CM_EDITOR_DEMO, C_kbF4, NULL,
        tv_menuitem_create("E~x~it", TV_CM_QUIT, 0, NULL, NULL))));

    tv_MenuItem* help_menu = tv_menuitem_create("~A~bout", CM_ABOUT, 0, NULL, NULL);

    tv_SubMenu* menu = tv_submenu_create("~F~ile", C_kbAltF);
    tv_submenu_add_menuitem(menu, file_menu);

    /* Create menu bar */
    // tv_Rect r = tv_rect_make(0, 0, 80, 1);
    return tv_menubar_create(r, menu);
}


tv_Application* app;

void handleEvent(tv_Event e) {
    //printf("Handling event: %d\n", e.what);
    if (e.what == TV_CM_QUIT) {
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