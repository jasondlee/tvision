/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_APP.CPP                                                            */
/*                                                                         */
/*   C wrapper implementation for Turbo Vision application framework      */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_TApplication
#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TMenuBar
#define Uses_TStatusLine
#define Uses_TMenuItem
#define Uses_TSubMenu
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TRect
#define Uses_TEvent
#define Uses_TDialog
#define Uses_TWindow
#include <tvision/tv.h>

#include "tvision_c/tv_app.h"
#include <cstring>

extern "C" {

/* TProgram functions */

tv_Program* tv_program_create(void) {
    return reinterpret_cast<tv_Program*>(new TProgram());
}

void tv_program_destroy(tv_Program* program) {
    if (program) {
        delete reinterpret_cast<TProgram*>(program);
    }
}

void tv_program_run(tv_Program* program) {
    reinterpret_cast<TProgram*>(program)->run();
}

void tv_program_quit(tv_Program* program) {
    TEvent event;
    event.what = evCommand;
    event.message.command = cmQuit;
    event.message.infoPtr = nullptr;
    reinterpret_cast<TProgram*>(program)->putEvent(event);
}

tv_DeskTop* tv_program_get_desktop(tv_Program* program) {
    return reinterpret_cast<tv_DeskTop*>(TProgram::deskTop);
}

tv_MenuBar* tv_program_get_menubar(tv_Program* program) {
    return reinterpret_cast<tv_MenuBar*>(TProgram::menuBar);
}

tv_StatusLine* tv_program_get_statusline(tv_Program* program) {
    return reinterpret_cast<tv_StatusLine*>(TProgram::statusLine);
}

tv_Window* tv_program_insert_window(tv_Program* program, tv_Window* window) {
    return reinterpret_cast<tv_Window*>(
        reinterpret_cast<TProgram*>(program)->insertWindow(
            reinterpret_cast<TWindow*>(window)
        )
    );
}

tv_ushort tv_program_execute_dialog(tv_Program* program, tv_Dialog* dialog, void* data) {
    return reinterpret_cast<TProgram*>(program)->executeDialog(
        reinterpret_cast<TDialog*>(dialog),
        data
    );
}

tv_View* tv_program_valid_view(tv_Program* program, tv_View* view) {
    return reinterpret_cast<tv_View*>(
        reinterpret_cast<TProgram*>(program)->validView(
            reinterpret_cast<TView*>(view)
        )
    );
}

void tv_program_get_event(tv_Program* program, tv_EventHandle* event) {
    reinterpret_cast<TProgram*>(program)->getEvent(*reinterpret_cast<TEvent*>(event));
}

void tv_program_put_event(tv_Program* program, tv_EventHandle* event) {
    reinterpret_cast<TProgram*>(program)->putEvent(*reinterpret_cast<TEvent*>(event));
}

void tv_program_set_screen_mode(tv_Program* program, tv_ushort mode) {
    reinterpret_cast<TProgram*>(program)->setScreenMode(mode);
}

/* Cast functions for TProgram */

tv_View* tv_program_to_view(tv_Program* program) {
    return reinterpret_cast<tv_View*>(program);
}

tv_Group* tv_program_to_group(tv_Program* program) {
    return reinterpret_cast<tv_Group*>(program);
}

/* TApplication functions */

tv_Application* tv_application_create(void) {
    return reinterpret_cast<tv_Application*>(new TApplication());
}

void tv_application_destroy(tv_Application* app) {
    if (app) {
        delete reinterpret_cast<TApplication*>(app);
    }
}

void tv_application_run(tv_Application* app) {
    reinterpret_cast<TApplication*>(app)->run();
}

void tv_application_quit(tv_Application* app) {
    TEvent event;
    event.what = evCommand;
    event.message.command = cmQuit;
    event.message.infoPtr = nullptr;
    reinterpret_cast<TApplication*>(app)->putEvent(event);
}

void tv_application_suspend(tv_Application* app) {
    reinterpret_cast<TApplication*>(app)->suspend();
}

void tv_application_resume(tv_Application* app) {
    reinterpret_cast<TApplication*>(app)->resume();
}

int tv_application_get_palette(tv_Application* app) {
    return TProgram::appPalette;
}

void tv_application_set_palette(tv_Application* app, int palette) {
    TProgram::appPalette = palette;
}

/* Cast functions for TApplication */

tv_Program* tv_application_to_program(tv_Application* app) {
    return reinterpret_cast<tv_Program*>(app);
}

tv_View* tv_application_to_view(tv_Application* app) {
    return reinterpret_cast<tv_View*>(app);
}

tv_Group* tv_application_to_group(tv_Application* app) {
    return reinterpret_cast<tv_Group*>(app);
}

/* TDeskTop functions */

tv_DeskTop* tv_desktop_create(tv_Rect bounds) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_DeskTop*>(new TDeskTop(rect));
}

void tv_desktop_destroy(tv_DeskTop* desktop) {
    if (desktop) {
        TObject::destroy(reinterpret_cast<TDeskTop*>(desktop));
    }
}

void tv_desktop_tile(tv_DeskTop* desktop) {
    reinterpret_cast<TDeskTop*>(desktop)->tile();
}

void tv_desktop_cascade(tv_DeskTop* desktop) {
    reinterpret_cast<TDeskTop*>(desktop)->cascade();
}

/* Cast functions for TDeskTop */

tv_View* tv_desktop_to_view(tv_DeskTop* desktop) {
    return reinterpret_cast<tv_View*>(desktop);
}

tv_Group* tv_desktop_to_group(tv_DeskTop* desktop) {
    return reinterpret_cast<tv_Group*>(desktop);
}

/* Menu item helper functions */

tv_MenuItem* tv_menuitem_create(const char* name, tv_ushort command, tv_ushort key_code,
                                 const char* help_ctx, tv_MenuItem* next) {
    return reinterpret_cast<tv_MenuItem*>(
        new TMenuItem(name, command, key_code, hcNoContext, help_ctx,
                     reinterpret_cast<TMenuItem*>(next))
    );
}

tv_MenuItem* tv_menuitem_create_submenu(const char* name, tv_MenuItem* submenu, tv_MenuItem* next) {
    TMenu* menu = new TMenu(*reinterpret_cast<TMenuItem*>(submenu));
    return reinterpret_cast<tv_MenuItem*>(
        new TSubMenu(name, menu, reinterpret_cast<TMenuItem*>(next))
    );
}

tv_MenuItem* tv_menuitem_create_separator(tv_MenuItem* next) {
    return reinterpret_cast<tv_MenuItem*>(
        newLine(reinterpret_cast<TMenuItem*>(next))
    );
}

void tv_menuitem_destroy(tv_MenuItem* item) {
    if (item) {
        delete reinterpret_cast<TMenuItem*>(item);
    }
}

/* TMenuBar functions */

tv_MenuBar* tv_menubar_create(tv_Rect bounds, tv_MenuItem* menu) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    TMenu* tmenu = new TMenu(*reinterpret_cast<TMenuItem*>(menu));
    return reinterpret_cast<tv_MenuBar*>(new TMenuBar(rect, tmenu));
}

void tv_menubar_destroy(tv_MenuBar* menubar) {
    if (menubar) {
        TObject::destroy(reinterpret_cast<TMenuBar*>(menubar));
    }
}

/* Cast functions for TMenuBar */

tv_View* tv_menubar_to_view(tv_MenuBar* menubar) {
    return reinterpret_cast<tv_View*>(menubar);
}

/* Status item helper functions */

tv_StatusItem* tv_statusitem_create(const char* text, tv_ushort key_code, tv_ushort command,
                                     tv_StatusItem* next) {
    return reinterpret_cast<tv_StatusItem*>(
        new TStatusItem(text, key_code, command, reinterpret_cast<TStatusItem*>(next))
    );
}

void tv_statusitem_destroy(tv_StatusItem* item) {
    if (item) {
        delete reinterpret_cast<TStatusItem*>(item);
    }
}

/* TStatusLine functions */

tv_StatusLine* tv_statusline_create(tv_Rect bounds, tv_StatusItem* items) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    TStatusDef* def = new TStatusDef(0, 0xFFFF, reinterpret_cast<TStatusItem*>(items));
    return reinterpret_cast<tv_StatusLine*>(new TStatusLine(rect, *def));
}

void tv_statusline_destroy(tv_StatusLine* statusline) {
    if (statusline) {
        TObject::destroy(reinterpret_cast<TStatusLine*>(statusline));
    }
}

/* Cast functions for TStatusLine */

tv_View* tv_statusline_to_view(tv_StatusLine* statusline) {
    return reinterpret_cast<tv_View*>(statusline);
}

/* Global application instance */

tv_Application* tv_get_application(void) {
    return reinterpret_cast<tv_Application*>(TProgram::application);
}

} /* extern "C" */

// Made with Bob
