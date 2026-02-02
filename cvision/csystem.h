//
// C wrappers for Turbo Vision system classes
// Created following the pattern in cmenu.cpp
//

#ifndef CVISION_CSYSTEM_H
#define CVISION_CSYSTEM_H

#include <stddef.h>
#include <stdint.h>
#include "cobjects.h"
#include "ctypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations for opaque types */
typedef struct tv_THWMouse tv_THWMouse;
typedef struct tv_TMouse tv_TMouse;
typedef struct tv_TEventQueue tv_TEventQueue;
typedef struct tv_TTimerQueue tv_TTimerQueue;
typedef struct tv_TClipboard tv_TClipboard;
typedef struct tv_TDisplay tv_TDisplay;
typedef struct tv_TScreen tv_TScreen;
typedef struct tv_TSystemError tv_TSystemError;
typedef struct tv_TTimer tv_TTimer;
    
/* Structs - Note: tv_TEvent and related types are defined in ctypes.h */
typedef struct tv_MouseEventType {
    tv_Point where;
    tv_ushort eventFlags;
    tv_ushort controlKeyState;
    tv_uchar buttons;
    tv_uchar wheel;
} tv_MouseEventType;

typedef tv_Event tv_TEvent;

/* THWMouse functions */
void tv_hwmouse_show(void);
void tv_hwmouse_hide(void);
void tv_hwmouse_set_range(tv_ushort rx, tv_ushort ry);
void tv_hwmouse_get_event(tv_MouseEventType *event);
tv_bool tv_hwmouse_present(void);
void tv_hwmouse_suspend(void);
void tv_hwmouse_resume(void);
void tv_hwmouse_inhibit(void);

/* TMouse functions */
tv_TMouse *tv_mouse_create(void);
void tv_mouse_destroy(tv_TMouse *mouse);
void tv_mouse_show(void);
void tv_mouse_hide(void);
void tv_mouse_set_range(tv_ushort rx, tv_ushort ry);
void tv_mouse_get_event(tv_MouseEventType *event);
tv_bool tv_mouse_present(void);
void tv_mouse_suspend(void);
void tv_mouse_resume(void);

/* TEventQueue functions */
tv_TEventQueue *tv_eventqueue_create(void);
void tv_eventqueue_destroy(tv_TEventQueue *queue);
void tv_eventqueue_get_mouse_event(tv_TEvent *event);
void tv_eventqueue_get_key_event(tv_TEvent *event);
void tv_eventqueue_suspend(void);
void tv_eventqueue_resume(void);
void tv_eventqueue_wait_for_events(int timeoutMs);
void tv_eventqueue_wake_up(void);
void tv_eventqueue_set_paste_text(const char *text, size_t length);

/* TEvent functions */
void tv_event_get_mouse_event(tv_TEvent *event);
void tv_event_get_key_event(tv_TEvent *event);

/* TTimerQueue functions */
typedef void* tv_TTimerId;
#ifdef __BORLANDC__
typedef uint32_t tv_TTimePoint;
#else
typedef uint64_t tv_TTimePoint;
#endif

tv_TTimerQueue *tv_timerqueue_create(void);
tv_TTimerQueue *tv_timerqueue_create_with_func(tv_TTimePoint (*getTimeMs)(void));
void tv_timerqueue_destroy(tv_TTimerQueue *queue);
tv_TTimerId tv_timerqueue_set_timer(tv_TTimerQueue *queue, uint32_t timeoutMs, int32_t periodMs);
void tv_timerqueue_kill_timer(tv_TTimerQueue *queue, tv_TTimerId id);
void tv_timerqueue_collect_expired_timers(tv_TTimerQueue *queue, void (*func)(tv_TTimerId, void *), void *args);
int32_t tv_timerqueue_time_until_next_timeout(tv_TTimerQueue *queue);

/* TClipboard functions */
void tv_clipboard_set_text(const char *text, size_t length);
void tv_clipboard_request_text(void);

/* TDisplay functions */
enum tv_VideoModes {
    TV_SM_BW80       = 0x0002,
    TV_SM_CO80       = 0x0003,
    TV_SM_MONO       = 0x0007,
    TV_SM_FONT8X8    = 0x0100,
    TV_SM_COLOR256   = 0x0200,
    TV_SM_COLOR_HIGH = 0x0400,
    TV_SM_UPDATE     = 0x8000
};

void tv_display_clear_screen(tv_uchar w, tv_uchar h);
void tv_display_set_cursor_type(tv_ushort cursorType);
tv_ushort tv_display_get_cursor_type(void);
tv_ushort tv_display_get_rows(void);
tv_ushort tv_display_get_cols(void);
void tv_display_set_crt_mode(tv_ushort mode);
tv_ushort tv_display_get_crt_mode(void);

/* TScreen functions */
tv_TScreen *tv_screen_create(void);
void tv_screen_destroy(tv_TScreen *screen);
void tv_screen_set_video_mode(tv_ushort mode);
void tv_screen_clear_screen(void);
void tv_screen_flush_screen(void);
void tv_screen_set_crt_data(void);
tv_ushort tv_screen_fix_crt_mode(tv_ushort mode);
void tv_screen_suspend(void);
void tv_screen_resume(void);

/* TSystemError functions */
tv_TSystemError *tv_systemerror_create(void);
void tv_systemerror_destroy(tv_TSystemError *error);
void tv_systemerror_suspend(void);
void tv_systemerror_resume(void);
tv_bool tv_systemerror_get_ctrl_break_hit(void);
void tv_systemerror_set_ctrl_break_hit(tv_bool value);

#ifdef __cplusplus
}
#endif

#endif /* CVISION_CSYSTEM_H */
