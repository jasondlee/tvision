# cstatusline - C Wrappers for Turbo Vision Status Line Classes

This library provides C language wrappers for Turbo Vision's `TStatusLine`, `TStatusDef`, and `TStatusItem` classes, allowing you to build status line structures from C code.

## Overview

The cstatusline library wraps the C++ classes `TStatusItem`, `TStatusDef`, and `TStatusLine` with a C-compatible interface using `extern "C"` directives. This enables C programs to create status lines that can be used with Turbo Vision applications.

## Features

- **C-compatible API**: All functions use C linkage and opaque pointers
- **Operator overload wrappers**: Exposes C++ operator+ functionality through C functions
- **Complete status line building**: Create status items, definitions, and status lines
- **Type-safe**: Uses opaque handle types to maintain type safety
- **Reuses key constants**: Compatible with cmenuitem library key definitions

## Files

- `cstatusline.h` - C header with function declarations and constants
- `cstatusline.cpp` - C++ implementation with extern "C" wrappers
- `example.c` - Example demonstrating status line construction from C
- `CMakeLists.txt` - Build configuration

## API Reference

### Types

```c
typedef struct TStatusItem_C TStatusItem_C;  // Opaque handle for TStatusItem
typedef struct TStatusDef_C TStatusDef_C;    // Opaque handle for TStatusDef
typedef struct TStatusLine_C TStatusLine_C;  // Opaque handle for TStatusLine
```

### Key Constants

The library reuses key codes from cmenuitem if available, or defines them:
- `C_kbNoKey`, `C_kbF1`-`C_kbF10`, `C_kbCtrlN`, `C_kbAltX`, etc.
- `C_hcNoContext` - No help context constant

### TStatusItem Functions

#### Create status item
```c
TStatusItem_C* c_statusitem_new(
    const char* text,
    unsigned short key,
    unsigned short command
);
```
Creates a status item with display text, key binding, and command. Pass `NULL` for text to create a hidden key binding.

#### Append status items
```c
TStatusItem_C* c_statusitem_append(TStatusItem_C* item1, TStatusItem_C* item2);
```
Chains two status items together. Returns the first item with the second appended.

#### Destroy status item
```c
void c_statusitem_destroy(TStatusItem_C* item);
```

### TStatusDef Functions

#### Create status definition
```c
TStatusDef_C* c_statusdef_new(
    unsigned short min,
    unsigned short max,
    TStatusItem_C* items
);
```
Creates a status definition for a help context range. Items can be `NULL` and added later.

#### Add status item to definition (wraps operator+)
```c
TStatusDef_C* c_statusdef_add_item(TStatusDef_C* def, TStatusItem_C* item);
```

#### Add status definition to definition (wraps operator+)
```c
TStatusDef_C* c_statusdef_add_def(TStatusDef_C* def1, TStatusDef_C* def2);
```
Combines multiple status definitions for different help contexts.

#### Get underlying pointer
```c
void* c_statusdef_get_ptr(TStatusDef_C* def);
```

#### Destroy status definition
```c
void c_statusdef_destroy(TStatusDef_C* def);
```

### TStatusLine Functions

#### Create status line
```c
TStatusLine_C* c_statusline_new(
    short ax, short ay, short bx, short by,
    TStatusDef_C* defs
);
```
Creates a status line with the specified rectangle bounds and status definitions.

#### Get underlying pointer
```c
void* c_statusline_get_ptr(TStatusLine_C* statusLine);
```

#### Destroy status line
```c
void c_statusline_destroy(TStatusLine_C* statusLine);
```

## Usage Example

Here's a simple example of building a status line:

```c
#include "cstatusline.h"

#define cmQuit  106
#define cmSave  102
#define cmOpen  100

void build_status_line(void)
{
    TStatusDef_C* statusDef;
    TStatusItem_C* item;
    TStatusLine_C* statusLine;
    
    // Create status definition for all contexts (0-0xFFFF)
    statusDef = c_statusdef_new(0, 0xFFFF, NULL);
    
    // Add visible status items
    item = c_statusitem_new("~F2~ Save", C_kbF2, cmSave);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~F3~ Open", C_kbF3, cmOpen);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~Alt-X~ Exit", C_kbAltX, cmQuit);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    // Add hidden key binding (no text)
    item = c_statusitem_new(NULL, C_kbCtrlQ, cmQuit);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    // Create status line at bottom of 80x25 screen
    statusLine = c_statusline_new(0, 24, 80, 25, statusDef);
    
    // Use with TApplication (in C++ code):
    // return (TStatusLine*)c_statusline_get_ptr(statusLine);
    
    // Clean up
    c_statusline_destroy(statusLine);
}
```

## Building

The library is built as part of the project using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

This will create:
- `libcstatusline.a` - Static library
- `cstatusline_example` - Example program

## Integration with Turbo Vision

To use the C-built status line in a Turbo Vision application:

1. Build your status line structure using the C API
2. Get the underlying pointer with `c_statusline_get_ptr()`
3. Cast and return in C++ code:

```cpp
// In your C++ TApplication::initStatusLine():
extern "C" TStatusLine_C* build_my_statusline(TRect r);  // Your C function

TStatusLine* TMyApp::initStatusLine(TRect r)
{
    r.a.y = r.b.y - 1;  // Bottom line
    TStatusLine_C* statusLine = build_my_statusline(r);
    return (TStatusLine*)c_statusline_get_ptr(statusLine);
}
```

Alternatively, build just the TStatusDef in C:

```cpp
extern "C" TStatusDef_C* build_my_statusdef(void);

TStatusLine* TMyApp::initStatusLine(TRect r)
{
    r.a.y = r.b.y - 1;
    TStatusDef_C* defs = build_my_statusdef();
    return new TStatusLine(r, *((TStatusDef*)c_statusdef_get_ptr(defs)));
}
```

## Comparison with C++ Code

The C wrapper API closely mirrors the C++ operator overload syntax:

**C++ (from tvedit3.cpp):**
```cpp
return new TStatusLine(r,
    *new TStatusDef(0, 0xFFFF) +
        *new TStatusItem(0, kbAltX, cmQuit) +
        *new TStatusItem("~F2~ Save", kbF2, cmSave) +
        *new TStatusItem("~F3~ Open", kbF3, cmOpen)
);
```

**C (using cstatusline):**
```c
TStatusDef_C* def = c_statusdef_new(0, 0xFFFF, NULL);
TStatusItem_C* item;

item = c_statusitem_new(NULL, C_kbAltX, cmQuit);
def = c_statusdef_add_item(def, item);

item = c_statusitem_new("~F2~ Save", C_kbF2, cmSave);
def = c_statusdef_add_item(def, item);

item = c_statusitem_new("~F3~ Open", C_kbF3, cmOpen);
def = c_statusdef_add_item(def, item);

TStatusLine_C* statusLine = c_statusline_new(0, 24, 80, 25, def);
```

## Status Line Concepts

### Status Items
Individual items displayed in the status line. Each has:
- **Text**: Display text (use `~` for hotkey highlighting, or `NULL` for hidden bindings)
- **Key**: Keyboard shortcut
- **Command**: Command to execute when activated

### Status Definitions
Groups of status items for specific help context ranges. Allows different status items to appear based on the current help context (e.g., different items for different dialogs).

### Status Line
The visual component that displays status items at the bottom of the screen.

## Multiple Context Example

```c
// Status items for main window (context 0-100)
TStatusDef_C* mainDef = c_statusdef_new(0, 100, NULL);
item = c_statusitem_new("~F1~ Help", C_kbF1, cmHelp);
mainDef = c_statusdef_add_item(mainDef, item);

// Status items for editor (context 101-200)
TStatusDef_C* editorDef = c_statusdef_new(101, 200, NULL);
item = c_statusitem_new("~F2~ Save", C_kbF2, cmSave);
editorDef = c_statusdef_add_item(editorDef, item);

// Combine definitions
mainDef = c_statusdef_add_def(mainDef, editorDef);

// Create status line with both definitions
TStatusLine_C* statusLine = c_statusline_new(0, 24, 80, 25, mainDef);
```

## Notes

- The library uses opaque pointers to hide C++ implementation details
- Memory management follows C conventions - you must call destroy functions
- The operator+ wrappers return the modified first operand (matching C++ behavior)
- All string parameters should be null-terminated C strings
- The `~` character in status text indicates keyboard shortcuts (Turbo Vision convention)
- Pass `NULL` for text to create hidden key bindings (shortcuts without display)
- Status definitions can overlap in context ranges; the first matching definition is used

## Compatibility

This library is designed to work alongside the cmenuitem library and shares the same key constant definitions for consistency.

## License

This wrapper library follows the same license as Turbo Vision.