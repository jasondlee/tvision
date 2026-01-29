//
// Created by Jason Lee on 1/28/26.
//

#include "ctypes.h"
#include "cvision.h"
#include <tvision/tv.h>

TCApplication::TCApplication(TStatusLine *(*statusLineFunc)(TRect),
                  TMenuBar *(*menuBarFunc)(TRect),
                  void (*handleEventFunc)(TEvent)) :
    TProgInit( statusLineFunc,
               menuBarFunc,
               TCApplication::initDeskTop
             ),
    TApplication(),
    cHandleEvent(handleEventFunc) {

}

void TCApplication::handleEvent(TEvent& event) {
    TApplication::handleEvent(event);

    if( event.what != evCommand ) {
        return;
    } else {
        if (cHandleEvent) {
            cHandleEvent(event);
        }
    }
}

extern "C" {
    /* TApplication functions */

    /* Create a new TApplication instance using TCApplication subclass.
     *
     * Note: TApplication has a protected constructor in the original Turbo Vision
     * library. To work around this, we use TCApplication, a minimal subclass that
     * exposes a public constructor. This allows the C wrapper to instantiate the
     * application object while maintaining full compatibility with TApplication's
     * interface and behavior.
     *
     * The function pointers are cast from C wrapper types to C++ types using
     * reinterpret_cast. This is safe because the wrapper types (tv_StatusLine*,
     * tv_MenuBar*, tv_Rect, tv_Event) are binary-compatible with their C++
     * counterparts (TStatusLine*, TMenuBar*, TRect, TEvent).
     */
    tv_Application* tv_application_create(tv_StatusLine *(*cStatusLine)(tv_Rect),
                                          tv_MenuBar *(*cMenuBar)(tv_Rect),
                                          void (*handleEventFunc)(tv_Event)) {
        // Cast function pointers from C wrapper types to C++ types
        auto statusLineFunc = reinterpret_cast<TStatusLine *(*)(TRect)>(cStatusLine);
        auto menuBarFunc = reinterpret_cast<TMenuBar *(*)(TRect)>(cMenuBar);
        auto eventFunc = reinterpret_cast<void (*)(TEvent)>(handleEventFunc);

        return reinterpret_cast<tv_Application*>(
            new TCApplication(statusLineFunc, menuBarFunc, eventFunc)
        );
    }

    void tv_application_destroy(tv_Application* app) {
        if (app) {
            delete reinterpret_cast<TCApplication*>(app);
        }
    }

    void tv_application_run(tv_Application* app) {
        reinterpret_cast<TApplication*>(app)->run();
    }

    /* Menu item helper functions */

    tv_MenuItem* tv_menuitem_create(const char* name, tv_ushort command, tv_ushort key_code,
                                     const char* help_ctx, tv_MenuItem* next) {
        return reinterpret_cast<tv_MenuItem*>(
            new TMenuItem(name, command, key_code, hcNoContext, help_ctx,
                         reinterpret_cast<TMenuItem*>(next))
        );
    }

    tv_SubMenu* tv_submenu_create(const char* name, tv_ushort key_code) {
        return reinterpret_cast<tv_SubMenu*>(new TSubMenu(name, key_code));
    }

    tv_SubMenu* tv_submenu_add_menuitem(tv_SubMenu* submenu, tv_MenuItem* item) {
        *reinterpret_cast<TSubMenu*>(submenu) + *reinterpret_cast<TMenuItem*>(item);
        return submenu;
    }

    /*
    tv_MenuItem* tv_menuitem_create_submenu(const char* name, tv_MenuItem* submenu, tv_MenuItem* next) {
        auto* menu = new TMenu(*reinterpret_cast<TMenuItem*>(submenu));
        return reinterpret_cast<tv_MenuItem*>(
            new TSubMenu(name, menu, reinterpret_cast<TMenuItem*>(next))
            //TSubMenu( TStringView nm, TKey key, ushort helpCtx = hcNoContext ) noexcept;
        );
    }
    */

    /* TMenuBar functions */

    tv_MenuBar* tv_menubar_create(tv_Rect bounds, tv_SubMenu* menu) {
        TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
        TMenu* tmenu = new TMenu(*reinterpret_cast<TSubMenu*>(menu));
        return reinterpret_cast<tv_MenuBar*>(new TMenuBar(rect, tmenu));
    }

    void tv_menubar_destroy(tv_MenuBar* menubar) {
        if (menubar) {
            TObject::destroy(reinterpret_cast<TMenuBar*>(menubar));
        }
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

    /* TRect functions */

    tv_Rect tv_rect_make(int ax, int ay, int bx, int by) {
        tv_Rect r;
        r.ax = ax;
        r.ay = ay;
        r.bx = bx;
        r.by = by;
        return r;
    }
}