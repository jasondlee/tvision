/*----------------------------------------------------------*/
/*                                                          */
/*   example.c - Example usage of cstatusline C wrappers   */
/*                                                          */
/*   Demonstrates building TStatusLine from C code         */
/*                                                          */
/*----------------------------------------------------------*/

#include "../capplication/cstatusline.h"
#include <stdio.h>

/*
 * This example demonstrates how to build a status line structure
 * similar to the one in tvedit3.cpp's initStatusLine function,
 * but using pure C code with the cstatusline wrappers.
 */

/* Command constants (would normally be in a header) */
#define cmQuit        106
#define cmSave        102
#define cmOpen        100
#define cmClose       406
#define cmZoom        401
#define cmNext        404
#define cmMenu        500
#define cmCut         201
#define cmCopy        202
#define cmPaste       203
#define cmResize      400

void example_build_statusline(void)
{
    TStatusDef_C* statusDef;
    TStatusItem_C* item;
    
    printf("Building status line...\n");
    
    /* Create the status definition for range 0 to 0xFFFF (all contexts) */
    statusDef = c_statusdef_new(0, 0xFFFF, NULL);
    
    /* Add status items using the operator+ wrapper */
    
    /* First item with no text (just key binding) */
    item = c_statusitem_new(NULL, C_kbAltX, cmQuit);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    /* F2 Save */
    item = c_statusitem_new("~F2~ Save", C_kbF2, cmSave);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    /* F3 Open */
    item = c_statusitem_new("~F3~ Open", C_kbF3, cmOpen);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    /* Ctrl-W Close */
    item = c_statusitem_new("~Ctrl-W~ Close", C_kbAltF3, cmClose);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    /* F5 Zoom */
    item = c_statusitem_new("~F5~ Zoom", C_kbF5, cmZoom);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    /* F6 Next */
    item = c_statusitem_new("~F6~ Next", C_kbF6, cmNext);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    /* F10 Menu */
    item = c_statusitem_new("~F10~ Menu", C_kbF10, cmMenu);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    /* Hidden items (no text, just key bindings) */
    item = c_statusitem_new(NULL, C_kbShiftDel, cmCut);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new(NULL, C_kbCtrlIns, cmCopy);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new(NULL, C_kbShiftIns, cmPaste);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new(NULL, C_kbCtrlF5, cmResize);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    printf("Status line structure built successfully!\n");
    printf("\nStatus items added:\n");
    printf("  - Alt-X (Quit)\n");
    printf("  - F2 Save\n");
    printf("  - F3 Open\n");
    printf("  - Ctrl-W Close\n");
    printf("  - F5 Zoom\n");
    printf("  - F6 Next\n");
    printf("  - F10 Menu\n");
    printf("  - Shift-Del (Cut)\n");
    printf("  - Ctrl-Ins (Copy)\n");
    printf("  - Shift-Ins (Paste)\n");
    printf("  - Ctrl-F5 (Resize)\n");
    
    printf("\nTo use this in a TStatusLine constructor:\n");
    printf("  TRect r(0, 24, 80, 25);  // Bottom line of screen\n");
    printf("  TStatusLine* statusLine = new TStatusLine(r, *((TStatusDef*)c_statusdef_get_ptr(statusDef)));\n");
    
    /* Clean up */
    c_statusdef_destroy(statusDef);
}

void example_build_statusline_with_rect(void)
{
    TStatusDef_C* statusDef;
    TStatusItem_C* item;
    TStatusLine_C* statusLine;
    
    printf("\n\n=== Building status line with TRect ===\n");
    
    /* Create the status definition */
    statusDef = c_statusdef_new(0, 0xFFFF, NULL);
    
    /* Add a few items */
    item = c_statusitem_new("~F10~ Menu", C_kbF10, cmMenu);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    item = c_statusitem_new("~Alt-X~ Exit", C_kbAltX, cmQuit);
    statusDef = c_statusdef_add_item(statusDef, item);
    
    /* Create the status line with a rectangle (bottom line of 80x25 screen) */
    statusLine = c_statusline_new(0, 24, 80, 25, statusDef);
    
    if (statusLine) {
        printf("Status line created successfully!\n");
        printf("Rectangle: (0, 24) to (80, 25)\n");
        
        /* Clean up */
        c_statusline_destroy(statusLine);
    } else {
        printf("Failed to create status line!\n");
    }
}

void example_multiple_statusdefs(void)
{
    TStatusDef_C* def1;
    TStatusDef_C* def2;
    TStatusItem_C* item;
    
    printf("\n\n=== Building status line with multiple definitions ===\n");
    printf("(Different status items for different help contexts)\n\n");
    
    /* Create first status definition for context 0-100 */
    def1 = c_statusdef_new(0, 100, NULL);
    
    item = c_statusitem_new("~F1~ Help", C_kbF1, 1);
    def1 = c_statusdef_add_item(def1, item);
    
    item = c_statusitem_new("~Alt-X~ Exit", C_kbAltX, cmQuit);
    def1 = c_statusdef_add_item(def1, item);
    
    printf("Definition 1 (context 0-100):\n");
    printf("  - F1 Help\n");
    printf("  - Alt-X Exit\n");
    
    /* Create second status definition for context 101-200 */
    def2 = c_statusdef_new(101, 200, NULL);
    
    item = c_statusitem_new("~F2~ Save", C_kbF2, cmSave);
    def2 = c_statusdef_add_item(def2, item);
    
    item = c_statusitem_new("~F3~ Load", C_kbF3, cmOpen);
    def2 = c_statusdef_add_item(def2, item);
    
    printf("\nDefinition 2 (context 101-200):\n");
    printf("  - F2 Save\n");
    printf("  - F3 Load\n");
    
    /* Combine the definitions using operator+ */
    def1 = c_statusdef_add_def(def1, def2);
    
    printf("\nCombined definitions successfully!\n");
    printf("The status line will show different items based on help context.\n");
    
    /* Clean up */
    c_statusdef_destroy(def1);
}

int main(void)
{
    printf("=== cstatusline C Wrapper Example ===\n\n");
    printf("This example demonstrates building a Turbo Vision status line\n");
    printf("structure from C code using the cstatusline wrappers.\n\n");
    
    example_build_statusline();
    example_build_statusline_with_rect();
    example_multiple_statusdefs();
    
    printf("\n\nExample completed successfully!\n");
    return 0;
}

// Made with Bob
