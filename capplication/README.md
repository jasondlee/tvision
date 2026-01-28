# capplication - C Builder API for Turbo Vision Applications

This library provides a C language builder API for creating complete Turbo Vision applications, integrating the cmenuitem and cstatusline libraries to provide a comprehensive C interface for TApplication.

## Overview

The capplication library wraps the C++ `TApplication` class with a builder-style C API that allows you to:
- Create complete Turbo Vision applications from C code
- Configure menu bars using cmenuitem
- Configure status lines using cstatusline
- Register event handlers as C function callbacks
- Enable/disable commands dynamically
- Execute built-in dialogs (file open, change directory)

## Features

- **Builder-style API**: Fluent interface for configuring applications
- **Event handler callbacks**: Register C functions to handle commands
- **Command management**: Enable/disable commands dynamically
- **Dialog helpers**: Built-in support for common dialogs
- **Desktop operations**: Cascade and tile windows
- **Full integration**: Works seamlessly with cmenuitem and cstatusline

## Files

- `capplication.h` - C header with builder API declarations
- `capplication.cpp` - C++ implementation with custom TApplication subclass
- `example.c` - Complete example replicating TEditorApp from tvedit1.cpp
- `CMakeLists.txt` - Build configuration

## API Reference

### Types

```c
typedef struct TApplication_C TApplication_C;  // Opaque handle for application
typedef void (*CEventHandler)(void* app, unsigned short command, void* userData);
```

### Application Lifecycle

#### Create application
```c
TApplication_C* c_application_new(void);
```
Creates a new application instance.

#### Run application
```c
void c_application_run(TApplication_C* app);
```
Runs the application event loop (blocks until quit).

#### Destroy application
```c
void c_application_destroy(TApplication_C* app);
```
Shuts down and destroys the application.

### Configuration

#### Set menu bar
```c
void c_application_set_menubar(TApplication_C* app, TSubMenu_C* menu);
```
Sets the application's menu bar using a TSubMenu from cmenuitem.

#### Set status line
```c
void c_application_set_statusline(TApplication_C* app, TStatusDef_C* statusDef);
```
Sets the application's status line using a TStatusDef from cstatusline.

### Event Handling

#### Register event handler
```c
void c_application_register_handler(
    TApplication_C* app,
    unsigned short command,
    CEventHandler handler,
    void* userData
);
```
Registers a C function to handle a specific command. The handler signature is:
```c
void handler(void* app, unsigned short command, void* userData);
```

### Command Management

#### Enable/disable single command
```c
void c_application_enable_command(TApplication_C* app, unsigned short command);
void c_application_disable_command(TApplication_C* app, unsigned short command);
```

#### Enable/disable multiple commands
```c
void c_application_enable_commands(TApplication_C* app, const unsigned short* commands, int count);
void c_application_disable_commands(TApplication_C* app, const unsigned short* commands, int count);
```

### Desktop Operations

#### Cascade windows
```c
void c_application_cascade(TApplication_C* app);
```

#### Tile windows
```c
void c_application_tile(TApplication_C* app);
```

### Dialog Helpers

#### File open dialog
```c
unsigned short c_application_exec_file_dialog(
    TApplication_C* app,
    const char* wildcard,
    const char* title,
    char* resultBuffer,
    int bufferSize
);
```
Executes a file open dialog. Returns command result (cmCancel if cancelled).

#### Change directory dialog
```c
void c_application_exec_chdir_dialog(TApplication_C* app);
```

### Advanced

#### Get underlying pointer
```c
void* c_application_get_ptr(TApplication_C* app);
```
Returns the underlying TApplication pointer for advanced use.

## Usage Example

Here's a complete example building an editor application:

```c
#include "capplication.h"
#include "cmenuitem.h"
#include "cstatusline.h"

#define cmOpen  100
#define cmNew   101
#define cmQuit  C_cmQuit

/* Event handler for File Open */
void handle_open(void* app, unsigned short command, void* userData)
{
    char fileName[256];
    unsigned short result;
    
    result = c_application_exec_file_dialog(
        (TApplication_C*)app,
        "*.*",
        "Open file",
        fileName,
        sizeof(fileName)
    );
    
    if (result != C_cmQuit) {
        printf("Opening: %s\n", fileName);
        /* Open the file... */
    }
}

/* Event handler for File New */
void handle_new(void* app, unsigned short command, void* userData)
{
    printf("Creating new file\n");
    /* Create new editor... */
}

int main(void)
{
    TApplication_C* app;
    TSubMenu_C* menu;
    TStatusDef_C* statusDef;
    TMenuItem_C* item;
    
    /* Create application */
    app = c_application_new();
    
    /* Build menu */
    menu = c_submenu_new("~F~ile", C_kbAltF, C_hcNoContext);
    item = c_menuitem_new("~O~pen", cmOpen, C_kbF3, C_hcNoContext, "F3");
    menu = c_submenu_add_item(menu, item);
    item = c_menuitem_new("~N~ew", cmNew, C_kbCtrlN, C_hcNoContext, "Ctrl-N");
    menu = c_submenu_add_item(menu, item);
    item = c_menuitem_new("E~x~it", cmQuit, C_kbCtrlQ, C_hcNoContext, "Ctrl-Q");
    menu = c_submenu_add_item(menu, item);
    
    c_application_set_menubar(app, menu);
    
    /* Build status line */
    statusDef = c_statusdef_new(0, 0xFFFF, NULL);
    item = c_statusitem_new("~F3~ Open", C_kbF3, cmOpen);
    statusDef = c_statusdef_add_item(statusDef, item);
    item = c_statusitem_new("~Alt-X~ Exit", C_kbAltX, cmQuit);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    c_application_set_statusline(app, statusDef);
    
    /* Register handlers */
    c_application_register_handler(app, cmOpen, handle_open, NULL);
    c_application_register_handler(app, cmNew, handle_new, NULL);
    
    /* Run */
    c_application_run(app);
    
    /* Clean up */
    c_application_destroy(app);
    
    return 0;
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
- `libcapplication.a` - Static library
- `capplication_example` - Complete example application

## Command Constants

The library defines common command constants with `C_` prefix:

```c
#define C_cmValid   0
#define C_cmQuit    1
#define C_cmError   2
#define C_cmMenu    3
#define C_cmClose   4
#define C_cmZoom    5
#define C_cmResize  6
#define C_cmNext    7
#define C_cmPrev    8
#define C_cmHelp    9
```

Define your own application-specific commands starting from 100+.

## Event Handler Pattern

Event handlers receive three parameters:

1. **app**: The application instance (cast to `TApplication_C*`)
2. **command**: The command that triggered the handler
3. **userData**: User-defined data passed during registration

Example:
```c
void my_handler(void* app, unsigned short command, void* userData)
{
    TApplication_C* myApp = (TApplication_C*)app;
    int* myData = (int*)userData;
    
    /* Handle the command... */
}

/* Register with user data */
int myValue = 42;
c_application_register_handler(app, cmMyCommand, my_handler, &myValue);
```

## Command Management Pattern

Disable commands that shouldn't be available initially:

```c
/* Commands to disable when no document is open */
unsigned short editorCommands[] = {
    cmSave, cmSaveAs, cmCut, cmCopy, cmPaste, cmUndo
};

c_application_disable_commands(app, editorCommands, 
    sizeof(editorCommands) / sizeof(editorCommands[0]));

/* Later, when a document is opened, enable them */
c_application_enable_commands(app, editorCommands,
    sizeof(editorCommands) / sizeof(editorCommands[0]));
```

## Integration with TEditorApp

The example.c file demonstrates how to replicate the TEditorApp from tvedit1.cpp:

**C++ (tvedit1.cpp):**
```cpp
class TEditorApp : public TApplication {
    TEditorApp(int argc, char** argv);
    void handleEvent(TEvent& event);
    void fileOpen();
    void fileNew();
};

int main(int argc, char** argv) {
    TEditorApp app(argc, argv);
    app.run();
    return 0;
}
```

**C (using capplication):**
```c
void handle_file_open(void* app, unsigned short cmd, void* data) { /* ... */ }
void handle_file_new(void* app, unsigned short cmd, void* data) { /* ... */ }

int main(void) {
    TApplication_C* app = c_application_new();
    c_application_set_menubar(app, build_menubar());
    c_application_set_statusline(app, build_statusline());
    c_application_register_handler(app, cmOpen, handle_file_open, NULL);
    c_application_register_handler(app, cmNew, handle_file_new, NULL);
    c_application_run(app);
    c_application_destroy(app);
    return 0;
}
```

## Architecture

The library uses a custom `CApplication` class that:
- Inherits from `TApplication`
- Stores menu and status line configurations
- Maintains a map of command handlers
- Overrides `handleEvent()` to dispatch to C callbacks
- Provides command enable/disable functionality

This design allows complete control from C while maintaining full compatibility with Turbo Vision's architecture.

## Dependencies

- **tvision**: Core Turbo Vision library
- **cmenuitem**: C wrappers for menu building
- **cstatusline**: C wrappers for status line building

## Notes

- The application takes ownership of the menu and status line objects
- Event handlers are called after TApplication processes the event
- Use `clearEvent()` is called automatically after handler execution
- The application must be destroyed with `c_application_destroy()` to properly shut down
- All C callbacks should be thread-safe if using multi-threaded features

## License

This wrapper library follows the same license as Turbo Vision.