# cmenuitem - C Wrappers for Turbo Vision Menu Classes

This library provides C language wrappers for Turbo Vision's `TMenuItem` and `TSubMenu` classes, allowing you to build menu structures from C code.

## Overview

The cmenuitem library wraps the C++ classes `TMenuItem`, `TSubMenu`, and `TMenu` with a C-compatible interface using `extern "C"` directives. This enables C programs to create complex menu structures that can be used with Turbo Vision's `TMenuBar` class.

## Features

- **C-compatible API**: All functions use C linkage and opaque pointers
- **Operator overload wrappers**: Exposes C++ operator+ functionality through C functions
- **Complete menu building**: Create menu items, submenus, and separators
- **Type-safe**: Uses opaque handle types to maintain type safety

## Files

- `cmenuitem.h` - C header with function declarations and constants
- `cmenuitem.cpp` - C++ implementation with extern "C" wrappers
- `example.c` - Example demonstrating menu construction from C
- `CMakeLists.txt` - Build configuration

## API Reference

### Types

```c
typedef struct TMenuItem_C TMenuItem_C;  // Opaque handle for TMenuItem
typedef struct TSubMenu_C TSubMenu_C;    // Opaque handle for TSubMenu
typedef struct TMenu_C TMenu_C;          // Opaque handle for TMenu
```

### Key Constants

Common key codes are provided with `C_` prefix:
- `C_kbNoKey`, `C_kbF1`-`C_kbF10`, `C_kbCtrlN`, `C_kbCtrlQ`, etc.
- `C_hcNoContext` - No help context constant

### TMenuItem Functions

#### Create menu item with command
```c
TMenuItem_C* c_menuitem_new(
    const char* name,
    unsigned short command,
    unsigned short key,
    unsigned short helpCtx,
    const char* param
);
```

#### Create menu item with submenu
```c
TMenuItem_C* c_menuitem_new_submenu(
    const char* name,
    unsigned short key,
    TMenu_C* subMenu,
    unsigned short helpCtx
);
```

#### Create separator line
```c
TMenuItem_C* c_menuitem_newline(void);
```

#### Append menu items (wraps operator+)
```c
TMenuItem_C* c_menuitem_append(TMenuItem_C* item1, TMenuItem_C* item2);
```

#### Destroy menu item
```c
void c_menuitem_destroy(TMenuItem_C* item);
```

### TSubMenu Functions

#### Create submenu
```c
TSubMenu_C* c_submenu_new(
    const char* name,
    unsigned short key,
    unsigned short helpCtx
);
```

#### Add menu item to submenu (wraps operator+)
```c
TSubMenu_C* c_submenu_add_item(TSubMenu_C* submenu, TMenuItem_C* item);
```

#### Add submenu to submenu (wraps operator+)
```c
TSubMenu_C* c_submenu_add_submenu(TSubMenu_C* submenu1, TSubMenu_C* submenu2);
```

#### Convert submenu to menu item
```c
TMenuItem_C* c_submenu_to_menuitem(TSubMenu_C* submenu);
```

#### Get underlying pointer for TMenuBar
```c
void* c_submenu_get_ptr(TSubMenu_C* submenu);
```

#### Destroy submenu
```c
void c_submenu_destroy(TSubMenu_C* submenu);
```

### TMenu Functions

#### Create menu from item list
```c
TMenu_C* c_menu_new(TMenuItem_C* itemList);
```

#### Create menu with default item
```c
TMenu_C* c_menu_new_with_default(TMenuItem_C* itemList, TMenuItem_C* defaultItem);
```

#### Get underlying pointer
```c
void* c_menu_get_ptr(TMenu_C* menu);
```

#### Destroy menu
```c
void c_menu_destroy(TMenu_C* menu);
```

## Usage Example

Here's a simple example of building a File menu:

```c
#include "cmenuitem.h"

#define cmOpen  100
#define cmSave  101
#define cmQuit  102

void build_file_menu(void)
{
    TSubMenu_C* fileMenu;
    TMenuItem_C* item;
    
    // Create File submenu
    fileMenu = c_submenu_new("~F~ile", C_kbAltF, C_hcNoContext);
    
    // Add Open item
    item = c_menuitem_new("~O~pen", cmOpen, C_kbF3, C_hcNoContext, "F3");
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    // Add Save item
    item = c_menuitem_new("~S~ave", cmSave, C_kbF2, C_hcNoContext, "F2");
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    // Add separator
    item = c_menuitem_newline();
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    // Add Exit item
    item = c_menuitem_new("E~x~it", cmQuit, C_kbCtrlQ, C_hcNoContext, "Ctrl-Q");
    fileMenu = c_submenu_add_item(fileMenu, item);
    
    // Use with TMenuBar (in C++ code):
    // TMenuBar* menuBar = new TMenuBar(rect, *((TSubMenu*)c_submenu_get_ptr(fileMenu)));
    
    // Clean up
    c_submenu_destroy(fileMenu);
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
- `libcmenuitem.a` - Static library
- `cmenuitem_example` - Example program

## Integration with Turbo Vision

To use the C-built menus in a Turbo Vision application:

1. Build your menu structure using the C API
2. Get the underlying pointer with `c_submenu_get_ptr()`
3. Cast and dereference in C++ code:

```cpp
// In your C++ TApplication::initMenuBar():
extern "C" TSubMenu_C* build_my_menu(void);  // Your C function

TMenuBar* TMyApp::initMenuBar(TRect r)
{
    TSubMenu_C* menu = build_my_menu();
    r.b.y = r.a.y + 1;
    return new TMenuBar(r, *((TSubMenu*)c_submenu_get_ptr(menu)));
}
```

## Comparison with C++ Code

The C wrapper API closely mirrors the C++ operator overload syntax:

**C++ (from tvedit3.cpp):**
```cpp
TSubMenu& sub1 = *new TSubMenu("~F~ile", kbAltF) +
    *new TMenuItem("~O~pen", cmOpen, kbF3, hcNoContext, "F3") +
    *new TMenuItem("~S~ave", cmSave, kbF2, hcNoContext, "F2");
```

**C (using cmenuitem):**
```c
TSubMenu_C* sub1 = c_submenu_new("~F~ile", C_kbAltF, C_hcNoContext);
TMenuItem_C* item = c_menuitem_new("~O~pen", cmOpen, C_kbF3, C_hcNoContext, "F3");
sub1 = c_submenu_add_item(sub1, item);
item = c_menuitem_new("~S~ave", cmSave, C_kbF2, C_hcNoContext, "F2");
sub1 = c_submenu_add_item(sub1, item);
```

## Notes

- The library uses opaque pointers to hide C++ implementation details
- Memory management follows C conventions - you must call destroy functions
- The operator+ wrappers return the modified first operand (matching C++ behavior)
- All string parameters should be null-terminated C strings
- The `~` character in menu names indicates keyboard shortcuts (Turbo Vision convention)

## License

This wrapper library follows the same license as Turbo Vision.