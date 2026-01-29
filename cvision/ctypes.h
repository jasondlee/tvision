//
// Created by Jason Lee on 1/28/26.
//

#ifndef TVISION_CTYPES_H
#define TVISION_CTYPES_H

#define Uses_TApplication
#define Uses_TProgram
#define Uses_TDeskTop
#define Uses_TMenuBar
#define Uses_TStatusLine
#define Uses_TMenu
#define Uses_TMenuItem
#define Uses_TSubMenu
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TRect
#define Uses_TEvent
#define Uses_TDialog
#define Uses_TWindow

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

#define TV_FALSE 0
#define TV_TRUE 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tv_Application tv_Application;
typedef struct tv_MenuBar tv_MenuBar;
typedef struct tv_StatusLine tv_StatusLine;
typedef struct tv_MenuItem tv_MenuItem;
typedef struct tv_SubMenu tv_SubMenu;
typedef struct tv_StatusItem tv_StatusItem;

/* Basic type definitions */
typedef unsigned short tv_ushort;
typedef unsigned char tv_uchar;
typedef unsigned int tv_uint;

/* Boolean type */
typedef int tv_bool;

/* TPoint wrapper - simple struct, direct mapping */
typedef struct tv_Point {
    int x;
    int y;
} tv_Point;

/* TRect wrapper - simple struct, direct mapping */
typedef struct tv_Rect {
    int ax, ay; /* Top-left corner */
    int bx, by; /* Bottom-right corner */
} tv_Rect;

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
    void *info_ptr;
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

#ifdef __cplusplus
}
#endif

#endif //TVISION_CTYPES_H
