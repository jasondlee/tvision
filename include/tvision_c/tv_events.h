/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_EVENTS.H                                                           */
/*                                                                         */
/*   C wrapper for Turbo Vision event system (TEvent)                     */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_EVENTS_H
#define TV_EVENTS_H

#include "tv_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Event codes */
#define TV_EV_MOUSE_DOWN    0x0001
#define TV_EV_MOUSE_UP      0x0002
#define TV_EV_MOUSE_MOVE    0x0004
#define TV_EV_MOUSE_AUTO    0x0008
#define TV_EV_MOUSE_WHEEL   0x0020
#define TV_EV_KEY_DOWN      0x0010
#define TV_EV_COMMAND       0x0100
#define TV_EV_BROADCAST     0x0200

/* Event masks */
#define TV_EV_NOTHING       0x0000
#define TV_EV_MOUSE         0x002f
#define TV_EV_KEYBOARD      0x0010
#define TV_EV_MESSAGE       0xFF00

/* Mouse button state masks */
#define TV_MB_LEFT_BUTTON   0x01
#define TV_MB_RIGHT_BUTTON  0x02
#define TV_MB_MIDDLE_BUTTON 0x04

/* Mouse wheel state masks */
#define TV_MW_UP            0x01
#define TV_MW_DOWN          0x02
#define TV_MW_LEFT          0x04
#define TV_MW_RIGHT         0x08

/* Mouse event flags */
#define TV_ME_MOUSE_MOVED   0x01
#define TV_ME_DOUBLE_CLICK  0x02
#define TV_ME_TRIPLE_CLICK  0x04

/* Maximum text size for key events */
#define TV_MAX_CHAR_SIZE    4

/* Mouse event structure */
typedef struct tv_MouseEvent {
    tv_Point where;
    tv_ushort event_flags;
    tv_ushort control_key_state;
    tv_uchar buttons;
    tv_uchar wheel;
} tv_MouseEvent;

/* Key event structure */
typedef struct tv_KeyEvent {
    tv_ushort key_code;
    tv_ushort control_key_state;
    char text[TV_MAX_CHAR_SIZE];
    tv_uchar text_length;
} tv_KeyEvent;

/* Message event structure */
typedef struct tv_MessageEvent {
    tv_ushort command;
    void* info_ptr;
} tv_MessageEvent;

/* Main event structure */
typedef struct tv_Event {
    tv_ushort what;
    union {
        tv_MouseEvent mouse;
        tv_KeyEvent key;
        tv_MessageEvent message;
    } data;
} tv_Event;

/* Opaque handle to C++ TEvent */
typedef struct tv_EventHandle tv_EventHandle;

/* Event functions */
tv_Event tv_event_from_handle(tv_EventHandle* handle);
void tv_event_to_handle(tv_Event event, tv_EventHandle* handle);
void tv_event_clear(tv_Event* event);
tv_bool tv_event_is_mouse(tv_Event event);
tv_bool tv_event_is_key(tv_Event event);
tv_bool tv_event_is_command(tv_Event event);

#ifdef __cplusplus
}
#endif

#endif /* TV_EVENTS_H */

// Made with Bob
