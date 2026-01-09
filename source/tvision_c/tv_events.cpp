/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_EVENTS.CPP                                                         */
/*                                                                         */
/*   C wrapper implementation for Turbo Vision event system               */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_TEvent
#include <tvision/tv.h>

#include "tvision_c/tv_events.h"
#include <cstring>

extern "C" {

/* Convert C++ TEvent to C tv_Event */
tv_Event tv_event_from_handle(tv_EventHandle* handle) {
    TEvent* cpp_event = reinterpret_cast<TEvent*>(handle);
    tv_Event c_event;
    
    c_event.what = cpp_event->what;
    
    if (cpp_event->what & evMouse) {
        c_event.data.mouse.where.x = cpp_event->mouse.where.x;
        c_event.data.mouse.where.y = cpp_event->mouse.where.y;
        c_event.data.mouse.event_flags = cpp_event->mouse.eventFlags;
        c_event.data.mouse.control_key_state = cpp_event->mouse.controlKeyState;
        c_event.data.mouse.buttons = cpp_event->mouse.buttons;
        c_event.data.mouse.wheel = cpp_event->mouse.wheel;
    } else if (cpp_event->what & evKeyboard) {
        c_event.data.key.key_code = cpp_event->keyDown.keyCode;
        c_event.data.key.control_key_state = cpp_event->keyDown.controlKeyState;
        
        /* Copy text data */
        size_t text_len = 0;
        for (size_t i = 0; i < sizeof(cpp_event->keyDown.text) && 
             cpp_event->keyDown.text[i] != '\0'; ++i) {
            if (i < TV_MAX_CHAR_SIZE) {
                c_event.data.key.text[i] = cpp_event->keyDown.text[i];
                text_len = i + 1;
            }
        }
        c_event.data.key.text_length = static_cast<tv_uchar>(text_len);
    } else if (cpp_event->what & evMessage) {
        c_event.data.message.command = cpp_event->message.command;
        c_event.data.message.info_ptr = cpp_event->message.infoPtr;
    }
    
    return c_event;
}

/* Convert C tv_Event to C++ TEvent */
void tv_event_to_handle(tv_Event event, tv_EventHandle* handle) {
    TEvent* cpp_event = reinterpret_cast<TEvent*>(handle);
    
    cpp_event->what = event.what;
    
    if (event.what & evMouse) {
        cpp_event->mouse.where.x = event.data.mouse.where.x;
        cpp_event->mouse.where.y = event.data.mouse.where.y;
        cpp_event->mouse.eventFlags = event.data.mouse.event_flags;
        cpp_event->mouse.controlKeyState = event.data.mouse.control_key_state;
        cpp_event->mouse.buttons = event.data.mouse.buttons;
        cpp_event->mouse.wheel = event.data.mouse.wheel;
    } else if (event.what & evKeyboard) {
        cpp_event->keyDown.keyCode = event.data.key.key_code;
        cpp_event->keyDown.controlKeyState = event.data.key.control_key_state;
        
        /* Copy text data */
        std::memset(cpp_event->keyDown.text, 0, sizeof(cpp_event->keyDown.text));
        for (size_t i = 0; i < event.data.key.text_length && 
             i < TV_MAX_CHAR_SIZE && i < sizeof(cpp_event->keyDown.text); ++i) {
            cpp_event->keyDown.text[i] = event.data.key.text[i];
        }
    } else if (event.what & evMessage) {
        cpp_event->message.command = event.data.message.command;
        cpp_event->message.infoPtr = event.data.message.info_ptr;
    }
}

/* Clear an event */
void tv_event_clear(tv_Event* event) {
    if (event) {
        event->what = TV_EV_NOTHING;
        std::memset(&event->data, 0, sizeof(event->data));
    }
}

/* Check if event is a mouse event */
tv_bool tv_event_is_mouse(tv_Event event) {
    return (event.what & TV_EV_MOUSE) ? TV_TRUE : TV_FALSE;
}

/* Check if event is a keyboard event */
tv_bool tv_event_is_key(tv_Event event) {
    return (event.what & TV_EV_KEYBOARD) ? TV_TRUE : TV_FALSE;
}

/* Check if event is a command event */
tv_bool tv_event_is_command(tv_Event event) {
    return (event.what & TV_EV_COMMAND) ? TV_TRUE : TV_FALSE;
}

} /* extern "C" */

// Made with Bob
