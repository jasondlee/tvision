//
// Created by Jason Lee on 2/1/26.
//

#include "ctypes.h"
#include "cvision.h"
#include <tvision/tv.h>

extern "C" {
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
        TRect rect(bounds.a.x, bounds.a.y, bounds.b.x, bounds.b.y);
        TStatusDef* def = new TStatusDef(0, 0xFFFF, reinterpret_cast<TStatusItem*>(items));
        return reinterpret_cast<tv_StatusLine*>(new TStatusLine(rect, *def));
    }

    void tv_statusline_destroy(tv_StatusLine* statusline) {
        if (statusline) {
            TObject::destroy(reinterpret_cast<TStatusLine*>(statusline));
        }
    }
}