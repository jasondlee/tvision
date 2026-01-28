/*----------------------------------------------------------*/
/*                                                          */
/*   capplication.h - C builder API for TApplication       */
/*                                                          */
/*   C interface for creating Turbo Vision applications    */
/*                                                          */
/*----------------------------------------------------------*/

#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations from other C wrapper libraries */
typedef struct TSubMenu_C TSubMenu_C;
typedef struct TStatusDef_C TStatusDef_C;

/* Opaque handle for C application */
typedef struct TApplication_C TApplication_C;

/* Command constants - common commands */
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

/* Event handler callback type */
typedef void (*CEventHandler)(void* app, unsigned short command, void* userData);

/*
 * Application Builder API
 */

/* Create a new application builder */
TApplication_C* c_application_new(void);

/* Set the menu bar using a TSubMenu from cmenuitem */
void c_application_set_menubar(TApplication_C* app, TSubMenu_C* menu);

/* Set the status line using a TStatusDef from cstatusline */
void c_application_set_statusline(TApplication_C* app, TStatusDef_C* statusDef);

/* Register an event handler for a specific command */
void c_application_register_handler(
    TApplication_C* app,
    unsigned short command,
    CEventHandler handler,
    void* userData
);

/* Enable a command */
void c_application_enable_command(TApplication_C* app, unsigned short command);

/* Disable a command */
void c_application_disable_command(TApplication_C* app, unsigned short command);

/* Enable multiple commands */
void c_application_enable_commands(TApplication_C* app, const unsigned short* commands, int count);

/* Disable multiple commands */
void c_application_disable_commands(TApplication_C* app, const unsigned short* commands, int count);

/* Run the application (blocks until quit) */
void c_application_run(TApplication_C* app);

/* Shutdown and destroy the application */
void c_application_destroy(TApplication_C* app);

/* Get the underlying TApplication pointer (for advanced use) */
void* c_application_get_ptr(TApplication_C* app);

/*
 * Desktop operations
 */

/* Cascade windows */
void c_application_cascade(TApplication_C* app);

/* Tile windows */
void c_application_tile(TApplication_C* app);

/*
 * Dialog execution helpers
 */

/* Execute a file open dialog - returns command result */
unsigned short c_application_exec_file_dialog(
    TApplication_C* app,
    const char* wildcard,
    const char* title,
    char* resultBuffer,
    int bufferSize
);

/* Execute a change directory dialog */
void c_application_exec_chdir_dialog(TApplication_C* app);

#ifdef __cplusplus
}
#endif

#endif /* CAPPLICATION_H */

// Made with Bob
