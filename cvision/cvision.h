//
// Created by Jason Lee on 1/28/26.
//

#ifndef TVISION_CVISION_H
#define TVISION_CVISION_H

#ifdef __cplusplus
#include "ctypes.h"
#include <tvision/tv.h>

class TCApplication : public TApplication {
public:
    // Constructor with custom callbacks for status line, menu bar, and event handling
    TCApplication(TStatusLine * (*statusLineFunc)(TRect),
                  TMenuBar * (*menuBarFunc)(TRect),
                  void (*handleEventFunc)(TEvent));

    virtual void handleEvent(TEvent &event);

private:
    // TStatusLine *(*cStatusLine)(TRect);
    // TMenuBar *(*cMenuBar)(TRect);
    void (*cHandleEvent)(TEvent);
};

extern "C" {
#endif

/* TApplication functions
 *
 * Note: tv_application_create() uses TCApplication internally, a minimal
 * subclass that exposes TApplication's protected constructor. This is
 * transparent to C wrapper users and maintains full TApplication compatibility.
 */
tv_Application *tv_application_create(tv_StatusLine *(*cStatusLine)(tv_Rect),
                                      tv_MenuBar *(*cMenuBar)(tv_Rect),
                                      void (*handleEventFunc)(tv_Event));

void tv_application_destroy(tv_Application *app);

void tv_application_run(tv_Application *app);

/* Menu item helper functions */
tv_MenuItem *tv_menuitem_create(const char *name, tv_ushort command, tv_ushort key_code,
                                const char *help_ctx, tv_MenuItem *next);
tv_SubMenu* tv_submenu_create(const char* name, tv_ushort key_code);
tv_SubMenu* tv_submenu_add_menuitem(tv_SubMenu* submenu, tv_MenuItem* item);
// tv_MenuItem* tv_menuitem_create_submenu(const char* name, tv_MenuItem* submenu, tv_MenuItem* next);
// tv_MenuItem* tv_menuitem_create_separator(tv_MenuItem* next);

/* TMenuBar functions */
tv_MenuBar* tv_menubar_create(tv_Rect bounds, tv_SubMenu* menu);
void tv_menubar_destroy(tv_MenuBar* menubar);

/* TRect functions */
tv_Rect tv_rect_make(int ax, int ay, int bx, int by);

#endif //TVISION_CVISION_H

#ifdef __cplusplus
}
#endif
