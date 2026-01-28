/*----------------------------------------------------------*/
/*                                                          */
/*   capplication.h - C wrappers for TApplication          */
/*                                                          */
/*   C interface for building Turbo Vision applications    */
/*                                                          */
/*----------------------------------------------------------*/

#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations from other C wrapper libraries */
typedef struct TMenuItem_C TMenuItem_C;
typedef struct TSubMenu_C TSubMenu_C;
typedef struct TStatusDef_C TStatusDef_C;

/* Help context constant */
#ifndef C_hcNoContext
#define C_hcNoContext 0
#endif

/* Opaque handle for C code */
typedef struct TApplication_C TApplication_C;

/* Builder handle for constructing TApplication */
typedef struct TApplicationBuilder_C TApplicationBuilder_C;

/*
 * TApplicationBuilder functions - Builder pattern for TApplication
 */

/* Create a new application builder */
TApplicationBuilder_C* c_application_builder_new(void);

/* Set the menu bar using a submenu (like TEditorApp::initMenuBar) */
TApplicationBuilder_C* c_application_builder_set_menubar(
    TApplicationBuilder_C* builder,
    TSubMenu_C* menu
);

/* Set the status line using a status definition (like TEditorApp::initStatusLine) */
TApplicationBuilder_C* c_application_builder_set_statusline(
    TApplicationBuilder_C* builder,
    TStatusDef_C* statusDef
);

/* Enable a command in the application */
TApplicationBuilder_C* c_application_builder_enable_command(
    TApplicationBuilder_C* builder,
    unsigned short command
);

/* Disable a command in the application */
TApplicationBuilder_C* c_application_builder_disable_command(
    TApplicationBuilder_C* builder,
    unsigned short command
);

/* Build and create the TApplication instance */
TApplication_C* c_application_builder_build(TApplicationBuilder_C* builder);

/* Destroy the builder (automatically called by build) */
void c_application_builder_destroy(TApplicationBuilder_C* builder);

/*
 * TApplication functions
 */

/* Run the application event loop */
void c_application_run(TApplication_C* app);

/* Shut down the application */
void c_application_shutdown(TApplication_C* app);

/* Destroy the application */
void c_application_destroy(TApplication_C* app);

/* Get the underlying TApplication pointer (for advanced use) */
void* c_application_get_ptr(TApplication_C* app);

/*
 * Common command constants (from tvedit.h and standard TV commands)
 */
#define C_cmQuit        0x0001
#define C_cmMenu        0x0100
#define C_cmClose       0x0101
#define C_cmZoom        0x0102
#define C_cmResize      0x0103
#define C_cmNext        0x0104
#define C_cmPrev        0x0105
#define C_cmTile        0x0106
#define C_cmCascade     0x0107

/* Editor commands */
#define C_cmSave        0x0070
#define C_cmSaveAs      0x0071
#define C_cmCut         0x0072
#define C_cmCopy        0x0073
#define C_cmPaste       0x0074
#define C_cmUndo        0x0075
#define C_cmClear       0x0076
#define C_cmFind        0x0077
#define C_cmReplace     0x0078
#define C_cmSearchAgain 0x0079

/* File commands */
#define C_cmOpen        0x0080
#define C_cmNew         0x0081
#define C_cmChangeDrct  0x0066
#define C_cmDosShell    0x0067

#ifdef __cplusplus
}
#endif

#endif /* CAPPLICATION_H */

// Made with Bob