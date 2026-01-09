/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_APP.H                                                              */
/*                                                                         */
/*   C wrapper for Turbo Vision application framework                     */
/*   (TApplication, TProgram, TDeskTop, TMenuBar, TStatusLine)            */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_APP_H
#define TV_APP_H

#include "tv_types.h"
#include "tv_view.h"
#include "tv_window.h"

#ifdef __cplusplus
#include <tvision/tv.h>

class TCApplication : public TApplication
{
public:
    // Constructor with custom callbacks for status line, menu bar, and event handling
    TCApplication(TStatusLine *(*statusLineFunc)(TRect),
                  TMenuBar *(*menuBarFunc)(TRect),
                  void (*handleEventFunc)(TEvent));

    virtual void handleEvent(TEvent& event);

private:
    // TStatusLine *(*cStatusLine)(TRect);
    // TMenuBar *(*cMenuBar)(TRect);
    void (*cHandleEvent)(TEvent);

};

extern "C" {
#endif

/* Opaque pointers */
typedef struct tv_Application tv_Application;
typedef struct tv_Program tv_Program;
typedef struct tv_DeskTop tv_DeskTop;
typedef struct tv_MenuBar tv_MenuBar;
typedef struct tv_StatusLine tv_StatusLine;
typedef struct tv_MenuItem tv_MenuItem;
typedef struct tv_StatusItem tv_StatusItem;

/* Application palette constants */
#define TV_APP_GRAY     0
#define TV_APP_BLUE     1
#define TV_APP_CYAN     2
#define TV_APP_BLACK    3

/* TProgram functions */
tv_Program* tv_program_create(void);
void tv_program_destroy(tv_Program* program);
void tv_program_run(tv_Program* program);
void tv_program_quit(tv_Program* program);
tv_DeskTop* tv_program_get_desktop(tv_Program* program);
tv_MenuBar* tv_program_get_menubar(tv_Program* program);
tv_StatusLine* tv_program_get_statusline(tv_Program* program);
tv_Window* tv_program_insert_window(tv_Program* program, tv_Window* window);
tv_ushort tv_program_execute_dialog(tv_Program* program, tv_Dialog* dialog, void* data);
tv_View* tv_program_valid_view(tv_Program* program, tv_View* view);
void tv_program_get_event(tv_Program* program, tv_EventHandle* event);
void tv_program_put_event(tv_Program* program, tv_EventHandle* event);
void tv_program_set_screen_mode(tv_Program* program, tv_ushort mode);

/* Cast functions */
tv_View* tv_program_to_view(tv_Program* program);
tv_Group* tv_program_to_group(tv_Program* program);

/* TApplication functions
 *
 * Note: tv_application_create() uses TCApplication internally, a minimal
 * subclass that exposes TApplication's protected constructor. This is
 * transparent to C wrapper users and maintains full TApplication compatibility.
 */
tv_Application* tv_application_create(tv_StatusLine *(*cStatusLine)(tv_Rect),
                                      tv_MenuBar *(*cMenuBar)(tv_Rect),
                                      void (*handleEventFunc)(tv_Event));
void tv_application_destroy(tv_Application* app);
void tv_application_run(tv_Application* app);
void tv_application_quit(tv_Application* app);
void tv_application_suspend(tv_Application* app);
void tv_application_resume(tv_Application* app);
int tv_application_get_palette(tv_Application* app);
void tv_application_set_palette(tv_Application* app, int palette);

/* Cast functions */
tv_Program* tv_application_to_program(tv_Application* app);
tv_View* tv_application_to_view(tv_Application* app);
tv_Group* tv_application_to_group(tv_Application* app);

/* TDeskTop functions */
tv_DeskTop* tv_desktop_create(tv_Rect bounds);
void tv_desktop_destroy(tv_DeskTop* desktop);
// void tv_desktop_tile(tv_DeskTop* desktop);
// void tv_desktop_cascade(tv_DeskTop* desktop);

/* Cast functions */
tv_View* tv_desktop_to_view(tv_DeskTop* desktop);
tv_Group* tv_desktop_to_group(tv_DeskTop* desktop);

/* Menu item helper functions */
tv_MenuItem* tv_menuitem_create(const char* name, tv_ushort command, tv_ushort key_code, 
                                 const char* help_ctx, tv_MenuItem* next);
// tv_MenuItem* tv_menuitem_create_submenu(const char* name, tv_MenuItem* submenu, tv_MenuItem* next);
// tv_MenuItem* tv_menuitem_create_separator(tv_MenuItem* next);
void tv_menuitem_destroy(tv_MenuItem* item);

/* TMenuBar functions */
tv_MenuBar* tv_menubar_create(tv_Rect bounds, tv_MenuItem* menu);
void tv_menubar_destroy(tv_MenuBar* menubar);

/* Cast functions */
tv_View* tv_menubar_to_view(tv_MenuBar* menubar);

/* Status item helper functions */
tv_StatusItem* tv_statusitem_create(const char* text, tv_ushort key_code, tv_ushort command,
                                     tv_StatusItem* next);
void tv_statusitem_destroy(tv_StatusItem* item);

/* TStatusLine functions */
tv_StatusLine* tv_statusline_create(tv_Rect bounds, tv_StatusItem* items);
void tv_statusline_destroy(tv_StatusLine* statusline);

/* Cast functions */
tv_View* tv_statusline_to_view(tv_StatusLine* statusline);

/* Global application instance */
tv_Application* tv_get_application(void);

#ifdef __cplusplus
}
#endif

#endif /* TV_APP_H */

// Made with Bob
