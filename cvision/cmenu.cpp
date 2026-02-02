//
// Created by Jason Lee on 2/1/26.
//

/* Menu item helper functions */

#include "ctypes.h"
#include "cvision.h"
#include <tvision/tv.h>

extern "C" {
    tv_MenuItem *tv_menuitem_create(const char *name, tv_ushort command, tv_ushort key_code,
                                    const char *help_ctx, tv_MenuItem *next) {
        return reinterpret_cast<tv_MenuItem *>(
            new TMenuItem(name, command, key_code, hcNoContext, help_ctx, reinterpret_cast<TMenuItem *>(next))
        );
    }

    tv_SubMenu *tv_submenu_create(const char *name, tv_ushort key_code) {
        return reinterpret_cast<tv_SubMenu *>(new TSubMenu(name, key_code));
    }

    tv_SubMenu *tv_submenu_add_next(tv_SubMenu *submenu, tv_SubMenu *next) {
        *reinterpret_cast<TSubMenu *>(submenu) + *reinterpret_cast<TSubMenu *>(next);
        return submenu;
    }

    tv_SubMenu *tv_submenu_add_menuitem(tv_SubMenu *submenu, tv_MenuItem *item) {
        *reinterpret_cast<TSubMenu *>(submenu) + *reinterpret_cast<TMenuItem *>(item);
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

    tv_MenuBar *tv_menubar_create(tv_Rect bounds, tv_SubMenu *menu) {
        TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
        TMenu *tmenu = new TMenu(*reinterpret_cast<TSubMenu *>(menu));
        return reinterpret_cast<tv_MenuBar *>(new TMenuBar(rect, tmenu));
    }

    void tv_menubar_destroy(tv_MenuBar *menubar) {
        if (menubar) {
            TObject::destroy(reinterpret_cast<TMenuBar *>(menubar));
        }
    }
}
