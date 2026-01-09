# Turbo Vision C Wrapper Library

This directory contains C wrapper headers for the Turbo Vision C++ library, enabling the use of Turbo Vision from pure C code.

## Overview

The C wrapper provides a clean C API that wraps the core Turbo Vision C++ classes using opaque pointers and standard C calling conventions. This allows C programs to create text-based user interfaces using Turbo Vision without requiring C++ knowledge.

## Architecture

### Design Principles

1. **Opaque Pointers**: All C++ objects are represented as opaque pointers (e.g., `tv_View*`, `tv_Window*`)
2. **Naming Convention**: 
   - Types: `tv_ClassName` (e.g., `tv_View`, `tv_Window`)
   - Functions: `tv_classname_method` (e.g., `tv_view_draw`, `tv_window_close`)
   - Constants: `TV_CONSTANT_NAME` (e.g., `TV_EV_MOUSE_DOWN`)
3. **Memory Management**: Caller owns returned objects; use `_destroy()` functions to free
4. **Error Handling**: Returns `NULL` for allocation failures, `-1` or `0` for operation failures

## Header Files

### Core Headers

- **`tvision_c.h`** - Main header that includes all others
- **`tv_types.h`** - Basic types (TPoint, TRect)
- **`tv_events.h`** - Event system (TEvent)
- **`tv_view.h`** - Base view class (TView)
- **`tv_window.h`** - Window classes (TWindow, TDialog, TGroup)
- **`tv_widgets.h`** - UI widgets (TButton, TInputLine, TLabel, etc.)
- **`tv_lists.h`** - List/viewer classes (TListBox, TListViewer, TScroller)
- **`tv_editors.h`** - Editor classes (TEditor, TFileEditor, TMemo)
- **`tv_app.h`** - Application framework (TApplication, TProgram)
- **`tv_helpers.h`** - Helper functions for common operations

## Quick Start

### Basic Example

```c
#include <tvision_c/tvision_c.h>

int main(void) {
    /* Create application */
    tv_Application* app = tv_application_create();
    
    /* Create a dialog */
    tv_Rect r = tv_rect_make(0, 0, 40, 12);
    tv_Dialog* dialog = tv_dialog_create(r, "Hello World");
    
    /* Add a button */
    r = tv_rect_make(15, 9, 25, 11);
    tv_Button* button = tv_button_create(r, "OK", TV_CM_OK, TV_BF_DEFAULT);
    tv_group_insert(tv_dialog_to_group(dialog), tv_button_to_view(button));
    
    /* Execute dialog */
    tv_Program* program = tv_application_to_program(app);
    tv_program_execute_dialog(program, dialog, NULL);
    
    /* Cleanup */
    tv_dialog_destroy(dialog);
    tv_application_destroy(app);
    
    return 0;
}
```

## API Reference

### Types and Structures

#### Basic Types

```c
typedef struct tv_Point {
    int x, y;
} tv_Point;

typedef struct tv_Rect {
    int ax, ay;  /* Top-left corner */
    int bx, by;  /* Bottom-right corner */
} tv_Rect;
```

#### Event System

```c
typedef struct tv_Event {
    tv_ushort what;
    union {
        tv_MouseEvent mouse;
        tv_KeyEvent key;
        tv_MessageEvent message;
    } data;
} tv_Event;
```

### Core Classes

#### TView - Base View Class

All visual elements inherit from TView.

```c
/* Lifecycle */
tv_View* tv_view_create(tv_Rect bounds);
void tv_view_destroy(tv_View* view);

/* Properties */
tv_Rect tv_view_get_bounds(tv_View* view);
void tv_view_set_bounds(tv_View* view, tv_Rect bounds);
void tv_view_move_to(tv_View* view, int x, int y);

/* State */
void tv_view_show(tv_View* view);
void tv_view_hide(tv_View* view);
tv_bool tv_view_focus(tv_View* view);

/* Drawing */
void tv_view_draw(tv_View* view);

/* Events */
void tv_view_handle_event(tv_View* view, tv_EventHandle* event);
```

#### TWindow - Window Class

```c
tv_Window* tv_window_create(tv_Rect bounds, const char* title, int number);
void tv_window_destroy(tv_Window* window);
void tv_window_close(tv_Window* window);
void tv_window_zoom(tv_Window* window);
```

#### TDialog - Dialog Class

```c
tv_Dialog* tv_dialog_create(tv_Rect bounds, const char* title);
void tv_dialog_destroy(tv_Dialog* dialog);
tv_bool tv_dialog_valid(tv_Dialog* dialog, tv_ushort command);
```

### Widgets

#### TButton

```c
tv_Button* tv_button_create(tv_Rect bounds, const char* title, 
                            tv_ushort command, tv_ushort flags);
void tv_button_destroy(tv_Button* button);
void tv_button_make_default(tv_Button* button, tv_bool enable);
```

#### TInputLine

```c
tv_InputLine* tv_inputline_create(tv_Rect bounds, int max_len);
void tv_inputline_destroy(tv_InputLine* input);
void tv_inputline_set_data(tv_InputLine* input, const char* text);
void tv_inputline_get_data(tv_InputLine* input, char* buffer, int buffer_size);
```

#### TLabel

```c
tv_Label* tv_label_create(tv_Rect bounds, const char* text, tv_View* link);
void tv_label_destroy(tv_Label* label);
```

### Application Framework

#### TApplication

```c
tv_Application* tv_application_create(void);
void tv_application_destroy(tv_Application* app);
void tv_application_run(tv_Application* app);
void tv_application_quit(tv_Application* app);
```

#### TProgram

```c
tv_ushort tv_program_execute_dialog(tv_Program* program, tv_Dialog* dialog, void* data);
tv_Window* tv_program_insert_window(tv_Program* program, tv_Window* window);
```

## Type Casting

The wrapper provides safe casting functions between related types:

```c
/* View conversions */
tv_View* tv_window_to_view(tv_Window* window);
tv_View* tv_dialog_to_view(tv_Dialog* dialog);
tv_View* tv_button_to_view(tv_Button* button);

/* Group conversions */
tv_Group* tv_window_to_group(tv_Window* window);
tv_Group* tv_dialog_to_group(tv_Dialog* dialog);

/* Window conversions */
tv_Window* tv_dialog_to_window(tv_Dialog* dialog);
```

## Constants

### Event Codes

```c
#define TV_EV_MOUSE_DOWN    0x0001
#define TV_EV_MOUSE_UP      0x0002
#define TV_EV_KEY_DOWN      0x0010
#define TV_EV_COMMAND       0x0100
```

### View State Flags

```c
#define TV_SF_VISIBLE       0x0001
#define TV_SF_ACTIVE        0x0010
#define TV_SF_SELECTED      0x0020
#define TV_SF_FOCUSED       0x0040
#define TV_SF_DISABLED      0x0100
```

### Command Codes

```c
#define TV_CM_QUIT          1
#define TV_CM_CLOSE         4
#define TV_CM_OK            10
#define TV_CM_CANCEL        11
#define TV_CM_YES           12
#define TV_CM_NO            13
```

## Building

### With CMake

The C wrapper library is built automatically when you build Turbo Vision:

```bash
mkdir build && cd build
cmake ..
make
```

This creates `libtvision_c.a` (or `tvision_c.lib` on Windows).

### Linking Your Application

```cmake
target_link_libraries(your_app tvision_c)
```

Or manually:

```bash
gcc -o myapp myapp.c -ltvision_c -ltvision -lncursesw
```

## Examples

See `examples/c_wrapper_demo/hello_c.c` for a complete working example.

## Memory Management

### Rules

1. **Creation**: Functions ending in `_create()` allocate memory
2. **Destruction**: Always call corresponding `_destroy()` function
3. **Ownership**: Caller owns returned objects unless documented otherwise
4. **Insertion**: When inserting views into groups, the group takes ownership

### Example

```c
/* Create and insert - group takes ownership */
tv_Button* button = tv_button_create(r, "OK", TV_CM_OK, TV_BF_DEFAULT);
tv_group_insert(group, tv_button_to_view(button));
/* Don't call tv_button_destroy(button) - group will handle it */

/* Create and don't insert - must destroy manually */
tv_Button* button = tv_button_create(r, "OK", TV_CM_OK, TV_BF_DEFAULT);
/* ... decide not to use it ... */
tv_button_destroy(button);  /* Must destroy manually */
```

## Thread Safety

The C wrapper is **not thread-safe**. All calls must be made from the same thread that created the application.

### TListBox - List Box

```c
tv_ListBox* tv_listbox_create(tv_Rect bounds, tv_ushort num_cols, tv_ScrollBar* scrollbar);
void tv_listbox_destroy(tv_ListBox* listbox);
void tv_listbox_new_list(tv_ListBox* listbox, tv_Collection* list);
int tv_listbox_get_selection(tv_ListBox* listbox);
void tv_listbox_set_selection(tv_ListBox* listbox, int index);
```

### TEditor - Text Editor

```c
tv_Editor* tv_editor_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar,
                            tv_ScrollBar* v_scrollbar, tv_Indicator* indicator, int buf_size);
void tv_editor_destroy(tv_Editor* editor);
void tv_editor_insert_text(tv_Editor* editor, const char* text, int length, tv_bool select);
void tv_editor_clipboard_cut(tv_Editor* editor);
void tv_editor_clipboard_copy(tv_Editor* editor);
void tv_editor_clipboard_paste(tv_Editor* editor);
tv_bool tv_editor_search(tv_Editor* editor, const char* find_str, tv_ushort options);
```

### Helper Functions

```c
/* Message boxes */
tv_ushort tv_message_box(const char* msg, tv_ushort flags);
tv_bool tv_input_box(const char* title, const char* label, char* buffer, int buffer_size);

/* Dialog helpers */
tv_Dialog* tv_create_centered_dialog(int width, int height, const char* title);
void tv_dialog_add_ok_cancel(tv_Dialog* dialog);

/* File dialogs */
tv_bool tv_open_file_dialog(const char* wildcard, const char* title, char* filename, int filename_size);
tv_bool tv_save_file_dialog(const char* wildcard, const char* title, char* filename, int filename_size);

/* Desktop operations */
void tv_tile_desktop(void);
void tv_cascade_desktop(void);
```

## Feature Coverage

The C wrapper provides comprehensive coverage of Turbo Vision features:

- ✅ Basic types (TPoint, TRect, TEvent)
- ✅ Views and windows
- ✅ All common widgets (buttons, input lines, labels, checkboxes, radio buttons)
- ✅ List boxes and viewers with collections
- ✅ Full-featured text editors (TEditor, TFileEditor, TMemo)
- ✅ Application framework (TApplication, TProgram, TDeskTop)
- ✅ Menus and status lines
- ✅ Dialogs and groups
- ✅ Helper functions for common operations
- ✅ Event handling and key codes
- ✅ Color management
- ❌ Streaming/persistence (not wrapped - rarely needed)
- ❌ Advanced validators (can be added if needed)

The wrapper covers all essential features for building complete TUI applications.

## Contributing

To add new wrappers:

1. Add header declarations in `include/tvision_c/`
2. Add implementations in `source/tvision_c/`
3. Update `source/tvision_c/CMakeLists.txt`
4. Add examples and documentation

## License

The C wrapper follows the same license as Turbo Vision itself.