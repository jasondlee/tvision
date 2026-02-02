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

#endif //TVISION_CVISION_H

#ifdef __cplusplus
}
#endif
