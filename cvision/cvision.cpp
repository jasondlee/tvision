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
}