# capplication - C Wrappers for Turbo Vision TApplication

A C-compatible wrapper library for creating Turbo Vision applications using a builder pattern. This library enables C programs to create full-featured TUI applications with menus and status lines.

## Overview

The `capplication` library wraps the C++ class `TApplication` with a C-compatible interface using `extern "C"` directives and a builder pattern. This enables C programs to create Turbo Vision applications similar to the `TEditorApp` example from the Turbo Vision distribution.

## Features

- **Builder Pattern**: Fluent API for constructing TApplication instances
- **Menu Bar Support**: Integrates with `cmenuitem` library for menu creation
- **Status Line Support**: Integrates with `cstatusline` library for status line creation
- **Command Management**: Enable/disable commands programmatically
- **Type-safe**: Uses opaque handle types to maintain type safety
- **Pure C API**: Can be used from C code without C++ knowledge

## Files

- `capplication.h` - C header with function declarations and constants
- `capplication.cpp` - C++ implementation with extern "C" wrappers
- `example.c` - Example demonstrating application construction from C
- `CMakeLists.txt` - Build configuration

## API Reference

### Types

```c
typedef struct TApplication_C TApplication_C;
typedef struct TApplicationBuilder_C TApplicationBuilder_C;
```

Opaque handles representing TApplication and its builder.

### Builder Functions

#### `c_application_builder_new`
```c
TApplicationBuilder_C* c_application_builder_new(void);
```
Creates a new application builder instance.

#### `c_application_builder_set_menubar`
```c
TApplicationBuilder_C* c_application_builder_set_menubar(
    TApplicationBuilder_C* builder,
    TSubMenu_C* menu
);
```
Sets the menu bar for the application. Returns the builder for chaining.

#### `c_application_builder_set_statusline`
```c
TApplicationBuilder_C* c_application_builder_set_statusline(
    TApplicationBuilder_C* builder,
    TStatusDef_C* statusDef
);
```
Sets the status line for the application. Returns the builder for chaining.

#### `c_application_builder_enable_command`
```c
TApplicationBuilder_C* c_application_builder_enable_command(
    TApplicationBuilder_C* builder,
    unsigned short command
);
```
Enables a command in the application. Returns the builder for chaining.

#### `c_application_builder_disable_command`
```c
TApplicationBuilder_C* c_application_builder_disable_command(
    TApplicationBuilder_C* builder,
    unsigned short command
);
```
Disables a command in the application. Returns the builder for chaining.

#### `c_application_builder_build`
```c
TApplication_C* c_application_builder_build(TApplicationBuilder_C* builder);
```
Builds and creates the TApplication instance. This consumes the builder (automatically destroys it).

#### `c_application_builder_destroy`
```c
void c_application_builder_destroy(TApplicationBuilder_C* builder);
```
Manually destroys a builder (only needed if you don't call `build`).

### Application Functions

#### `c_application_run`
```c
void c_application_run(TApplication_C* app);
```
Runs the application event loop.

#### `c_application_shutdown`
```c
void c_application_shutdown(TApplication_C* app);
```
Shuts down the application.

#### `c_application_destroy`
```c
void c_application_destroy(TApplication_C* app);
```
Destroys the application and frees resources.

#### `c_application_get_ptr`
```c
void* c_application_get_ptr(TApplication_C* app);
```
Gets the underlying TApplication pointer for advanced use.

### Command Constants

The library provides constants for common Turbo Vision commands:

**Application Commands:**
- `C_cmQuit` - Quit application
- `C_cmMenu` - Activate menu
- `C_cmClose` - Close window
- `C_cmZoom` - Zoom window
- `C_cmResize` - Resize window
- `C_cmNext` - Next window
- `C_cmPrev` - Previous window
- `C_cmTile` - Tile windows
- `C_cmCascade` - Cascade windows

**Editor Commands:**
- `C_cmSave` - Save file
- `C_cmSaveAs` - Save file as
- `C_cmCut` - Cut text
- `C_cmCopy` - Copy text
- `C_cmPaste` - Paste text
- `C_cmUndo` - Undo
- `C_cmClear` - Clear
- `C_cmFind` - Find text
- `C_cmReplace` - Replace text
- `C_cmSearchAgain` - Search again

**File Commands:**
- `C_cmOpen` - Open file
- `C_cmNew` - New file
- `C_cmChangeDrct` - Change directory
- `C_cmDosShell` - DOS shell

## Usage Example

Here's a complete example creating an editor-like application:

```c
#include "capplication.h"
#include "../cmenuitem/cmenuitem.h"
#include "../cstatusline/cstatusline.h"

int main(int argc, char** argv)
{
    /* Build menu bar */
    TMenuItem_C* file_open = c_menuitem_new("~O~pen", C_cmOpen, C_kbF3, 
                                            C_hcNoContext, "F3");
    TMenuItem_C* file_exit = c_menuitem_new("E~x~it", C_cmQuit, C_kbCtrlQ, 
                                            C_hcNoContext, "Ctrl-Q");
    TMenuItem_C* file_items = c_menuitem_append(file_open, file_exit);
    
    TSubMenu_C* file_menu = c_submenu_new("~F~ile", C_kbAltF, C_hcNoContext);
    file_menu = c_submenu_add_item(file_menu, file_items);
    
    /* Build status line */
    TStatusItem_C* status1 = c_statusitem_new("~F3~ Open", C_kbF3, C_cmOpen);
    TStatusItem_C* status2 = c_statusitem_new("~Alt-X~ Exit", C_kbAltX, C_cmQuit);
    TStatusItem_C* status_items = c_statusitem_append(status1, status2);
    
    TStatusDef_C* statusdef = c_statusdef_new(0, 0xFFFF, status_items);
    
    /* Build application */
    TApplicationBuilder_C* builder = c_application_builder_new();
    builder = c_application_builder_set_menubar(builder, file_menu);
    builder = c_application_builder_set_statusline(builder, statusdef);
    builder = c_application_builder_disable_command(builder, C_cmSave);
    
    TApplication_C* app = c_application_builder_build(builder);
    
    /* Run application */
    c_application_run(app);
    c_application_shutdown(app);
    c_application_destroy(app);
    
    return 0;
}
```

## Building

The library is built as part of the main project:

```bash
mkdir build
cd build
cmake ..
make
```

This will create:
- `libcapplication.a` - Static library
- `capplication_example` - Example program

To run the example:
```bash
./capplication/capplication_example
```

## Integration with Other Libraries

The `capplication` library is designed to work with:
- **cmenuitem**: For creating menu bars
- **cstatusline**: For creating status lines

All three libraries share compatible key constant definitions and work together seamlessly.

## Comparison: C++ vs C

**C++ (TEditorApp):**
```cpp
class TEditorApp : public TApplication {
public:
    TEditorApp() : 
        TProgInit(TEditorApp::initStatusLine,
                  TEditorApp::initMenuBar,
                  TEditorApp::initDeskTop),
        TApplication() {
        // Disable commands
        TCommandSet ts;
        ts.enableCmd(cmSave);
        disableCommands(ts);
    }
    
    static TMenuBar* initMenuBar(TRect r);
    static TStatusLine* initStatusLine(TRect r);
};
```

**C (using capplication):**
```c
TSubMenu_C* menubar = build_menubar();
TStatusDef_C* statusline = build_statusline();

TApplicationBuilder_C* builder = c_application_builder_new();
builder = c_application_builder_set_menubar(builder, menubar);
builder = c_application_builder_set_statusline(builder, statusline);
builder = c_application_builder_disable_command(builder, C_cmSave);

TApplication_C* app = c_application_builder_build(builder);
```

## Implementation Details

The library creates a custom `CApplication` class that inherits from `TApplication` and uses static callbacks to provide the menu bar and status line. The builder pattern collects all configuration before constructing the application instance.

## License

This library follows the same license as Turbo Vision.

## See Also

- [cmenuitem](../cmenuitem/README.md) - Menu creation library
- [cstatusline](../cstatusline/README.md) - Status line creation library
- [Turbo Vision Documentation](https://github.com/magiblot/tvision)

---

Made with Bob