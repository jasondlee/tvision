//
// C wrappers for Turbo Vision system classes
// Created following the pattern in cmenu.cpp
//

#include "csystem.h"
#include "cvision.h"
#include <tvision/tv.h>
#include <cstring>

extern "C" {

/* THWMouse functions - Note: THWMouse methods are protected, use TMouse instead */

void tv_hwmouse_show(void) {
    TMouse::show();
}

void tv_hwmouse_hide(void) {
    TMouse::hide();
}

void tv_hwmouse_set_range(tv_ushort rx, tv_ushort ry) {
    TMouse::setRange(rx, ry);
}

void tv_hwmouse_get_event(tv_MouseEventType *event) {
    if (event) {
        MouseEventType me;
        TMouse::getEvent(me);
        event->where.x = me.where.x;
        event->where.y = me.where.y;
        event->eventFlags = me.eventFlags;
        event->controlKeyState = me.controlKeyState;
        event->buttons = me.buttons;
        event->wheel = me.wheel;
    }
}

tv_bool tv_hwmouse_present(void) {
    return TMouse::present() ? 1 : 0;
}

void tv_hwmouse_suspend(void) {
    TMouse::suspend();
}

void tv_hwmouse_resume(void) {
    TMouse::resume();
}

void tv_hwmouse_inhibit(void) {
    // Note: inhibit() is protected in THWMouse, not accessible
}

/* TMouse functions */

tv_TMouse *tv_mouse_create(void) {
    return reinterpret_cast<tv_TMouse *>(new TMouse());
}

void tv_mouse_destroy(tv_TMouse *mouse) {
    if (mouse) {
        delete reinterpret_cast<TMouse *>(mouse);
    }
}

void tv_mouse_show(void) {
    TMouse::show();
}

void tv_mouse_hide(void) {
    TMouse::hide();
}

void tv_mouse_set_range(tv_ushort rx, tv_ushort ry) {
    TMouse::setRange(rx, ry);
}

void tv_mouse_get_event(tv_MouseEventType *event) {
    if (event) {
        MouseEventType me;
        TMouse::getEvent(me);
        event->where.x = me.where.x;
        event->where.y = me.where.y;
        event->eventFlags = me.eventFlags;
        event->controlKeyState = me.controlKeyState;
        event->buttons = me.buttons;
        event->wheel = me.wheel;
    }
}

tv_bool tv_mouse_present(void) {
    return TMouse::present() ? 1 : 0;
}

void tv_mouse_suspend(void) {
    TMouse::suspend();
}

void tv_mouse_resume(void) {
    TMouse::resume();
}

/* TEventQueue functions */

tv_TEventQueue *tv_eventqueue_create(void) {
    return reinterpret_cast<tv_TEventQueue *>(new TEventQueue());
}

void tv_eventqueue_destroy(tv_TEventQueue *queue) {
    if (queue) {
        delete reinterpret_cast<TEventQueue *>(queue);
    }
}

void tv_eventqueue_get_mouse_event(tv_TEvent *event) {
    if (event) {
        TEvent ev;
        TEventQueue::getMouseEvent(ev);
        event->what = ev.what;
        event->data.mouse.where.x = ev.mouse.where.x;
        event->data.mouse.where.y = ev.mouse.where.y;
        event->data.mouse.event_flags = ev.mouse.eventFlags;
        event->data.mouse.control_key_state = ev.mouse.controlKeyState;
        event->data.mouse.buttons = ev.mouse.buttons;
        event->data.mouse.wheel = ev.mouse.wheel;
    }
}

void tv_eventqueue_get_key_event(tv_TEvent *event) {
    if (event) {
        TEvent ev;
        TEventQueue::getKeyEvent(ev);
        event->what = ev.what;
        event->data.key.key_code = ev.keyDown.keyCode;
        event->data.key.control_key_state = ev.keyDown.controlKeyState;
        event->data.key.text_length = ev.keyDown.textLength;
        if (ev.keyDown.textLength > 0 && ev.keyDown.textLength <= 4) {
            memcpy(event->data.key.text, ev.keyDown.text, ev.keyDown.textLength);
        }
    }
}

void tv_eventqueue_suspend(void) {
    TEventQueue::suspend();
}

void tv_eventqueue_resume(void) {
    TEventQueue::resume();
}

void tv_eventqueue_wait_for_events(int timeoutMs) {
    TEventQueue::waitForEvents(timeoutMs);
}

void tv_eventqueue_wake_up(void) {
    TEventQueue::wakeUp();
}

void tv_eventqueue_set_paste_text(const char *text, size_t length) {
    if (text && length > 0) {
        TEventQueue::setPasteText(TStringView(text, length));
    }
}

/* TEvent functions */

void tv_event_get_mouse_event(tv_TEvent *event) {
    if (event) {
        TEvent ev;
        ev.getMouseEvent();
        event->what = ev.what;
        event->data.mouse.where.x = ev.mouse.where.x;
        event->data.mouse.where.y = ev.mouse.where.y;
        event->data.mouse.event_flags = ev.mouse.eventFlags;
        event->data.mouse.control_key_state = ev.mouse.controlKeyState;
        event->data.mouse.buttons = ev.mouse.buttons;
        event->data.mouse.wheel = ev.mouse.wheel;
    }
}

void tv_event_get_key_event(tv_TEvent *event) {
    if (event) {
        TEvent ev;
        ev.getKeyEvent();
        event->what = ev.what;
        event->data.key.key_code = ev.keyDown.keyCode;
        event->data.key.control_key_state = ev.keyDown.controlKeyState;
        event->data.key.text_length = ev.keyDown.textLength;
        if (ev.keyDown.textLength > 0 && ev.keyDown.textLength <= 4) {
            memcpy(event->data.key.text, ev.keyDown.text, ev.keyDown.textLength);
        }
    }
}

/* TTimerQueue functions */

tv_TTimerQueue *tv_timerqueue_create(void) {
    return reinterpret_cast<tv_TTimerQueue *>(new TTimerQueue());
}

tv_TTimerQueue *tv_timerqueue_create_with_func(tv_TTimePoint (*getTimeMs)(void)) {
    // Note: TTimerQueue expects a function reference, not a pointer
    // This wrapper is not directly compatible - users should use the default constructor
    return nullptr;
}

void tv_timerqueue_destroy(tv_TTimerQueue *queue) {
    if (queue) {
        delete reinterpret_cast<TTimerQueue *>(queue);
    }
}

tv_TTimerId tv_timerqueue_set_timer(tv_TTimerQueue *queue, uint32_t timeoutMs, int32_t periodMs) {
    if (queue) {
        return reinterpret_cast<TTimerQueue *>(queue)->setTimer(timeoutMs, periodMs);
    }
    return 0;
}

void tv_timerqueue_kill_timer(tv_TTimerQueue *queue, tv_TTimerId id) {
    if (queue) {
        reinterpret_cast<TTimerQueue *>(queue)->killTimer(id);
    }
}

void tv_timerqueue_collect_expired_timers(tv_TTimerQueue *queue, void (*func)(tv_TTimerId, void *), void *args) {
    // Note: collectExpiredTimers expects a function reference, not a pointer
    // This is not directly compatible with C function pointers
    // Users should implement this functionality differently in C
    (void)queue;
    (void)func;
    (void)args;
}

int32_t tv_timerqueue_time_until_next_timeout(tv_TTimerQueue *queue) {
    if (queue) {
        return reinterpret_cast<TTimerQueue *>(queue)->timeUntilNextTimeout();
    }
    return -1;
}

/* TClipboard functions */

void tv_clipboard_set_text(const char *text, size_t length) {
    if (text && length > 0) {
        TClipboard::setText(TStringView(text, length));
    }
}

void tv_clipboard_request_text(void) {
    TClipboard::requestText();
}

/* TDisplay functions */

void tv_display_clear_screen(tv_uchar w, tv_uchar h) {
    TDisplay::clearScreen(w, h);
}

void tv_display_set_cursor_type(tv_ushort cursorType) {
    TDisplay::setCursorType(cursorType);
}

tv_ushort tv_display_get_cursor_type(void) {
    return TDisplay::getCursorType();
}

tv_ushort tv_display_get_rows(void) {
    return TDisplay::getRows();
}

tv_ushort tv_display_get_cols(void) {
    return TDisplay::getCols();
}

void tv_display_set_crt_mode(tv_ushort mode) {
    TDisplay::setCrtMode(mode);
}

tv_ushort tv_display_get_crt_mode(void) {
    return TDisplay::getCrtMode();
}

/* TScreen functions */

tv_TScreen *tv_screen_create(void) {
    return reinterpret_cast<tv_TScreen *>(new TScreen());
}

void tv_screen_destroy(tv_TScreen *screen) {
    if (screen) {
        delete reinterpret_cast<TScreen *>(screen);
    }
}

void tv_screen_set_video_mode(tv_ushort mode) {
    TScreen::setVideoMode(mode);
}

void tv_screen_clear_screen(void) {
    TScreen::clearScreen();
}

void tv_screen_flush_screen(void) {
    TScreen::flushScreen();
}

void tv_screen_set_crt_data(void) {
    TScreen::setCrtData();
}

tv_ushort tv_screen_fix_crt_mode(tv_ushort mode) {
    return TScreen::fixCrtMode(mode);
}

void tv_screen_suspend(void) {
    TScreen::suspend();
}

void tv_screen_resume(void) {
    TScreen::resume();
}

/* TSystemError functions */

tv_TSystemError *tv_systemerror_create(void) {
    return reinterpret_cast<tv_TSystemError *>(new TSystemError());
}

void tv_systemerror_destroy(tv_TSystemError *error) {
    if (error) {
        delete reinterpret_cast<TSystemError *>(error);
    }
}

void tv_systemerror_suspend(void) {
    TSystemError::suspend();
}

void tv_systemerror_resume(void) {
    TSystemError::resume();
}

tv_bool tv_systemerror_get_ctrl_break_hit(void) {
    return TSystemError::ctrlBreakHit ? 1 : 0;
}

void tv_systemerror_set_ctrl_break_hit(tv_bool value) {
    TSystemError::ctrlBreakHit = value ? True : False;
}

} // extern "C"
