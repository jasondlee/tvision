/*
 * hello_c.c - Simple Turbo Vision C wrapper demonstration
 * 
 * This example shows how to use the Turbo Vision C wrapper library
 * to create a simple dialog-based application in pure C.
 */

#include <tvision_c/tvision_c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Command constants */
#define CM_HELLO_DIALOG 100

/* Create a simple "Hello World" dialog */
tv_Dialog* create_hello_dialog(void) {
    tv_Rect r = tv_rect_make(0, 0, 40, 12);
    tv_Dialog* dialog = tv_dialog_create(r, "Hello from C!");
    
    /* Center the dialog */
    tv_View* dialog_view = tv_dialog_to_view(dialog);
    tv_ushort options = tv_view_get_options(dialog_view);
    tv_view_set_options(dialog_view, TV_OF_CENTER_X | TV_OF_CENTER_Y, TV_TRUE);
    
    /* Add a static text label */
    r = tv_rect_make(3, 3, 37, 6);
    tv_StaticText* text = tv_statictext_create(r, 
        "\003Welcome to Turbo Vision!\n"
        "\003C Wrapper Demo\n"
        "\003Press OK to continue");
    tv_group_insert(tv_dialog_to_group(dialog), tv_statictext_to_view(text));
    
    /* Add an input line */
    r = tv_rect_make(3, 7, 37, 8);
    tv_InputLine* input = tv_inputline_create(r, 80);
    tv_inputline_set_data(input, "Type something here...");
    tv_group_insert(tv_dialog_to_group(dialog), tv_inputline_to_view(input));
    
    /* Add OK button */
    r = tv_rect_make(15, 9, 25, 11);
    tv_Button* ok_button = tv_button_create(r, "~O~K", TV_CM_OK, TV_BF_DEFAULT);
    tv_group_insert(tv_dialog_to_group(dialog), tv_button_to_view(ok_button));
    
    return dialog;
}

/* Simple application with menu */
int main(void) {
    /* Create the application */
    tv_Application* app = tv_application_create();
    
    if (!app) {
        fprintf(stderr, "Failed to create application\n");
        return 1;
    }
    
    /* Show a dialog */
    tv_Dialog* dialog = create_hello_dialog();
    tv_Program* program = tv_application_to_program(app);
    
    /* Execute the dialog */
    tv_ushort result = tv_program_execute_dialog(program, dialog, NULL);
    
    /* Clean up */
    tv_dialog_destroy(dialog);
    
    /* Show result */
    if (result == TV_CM_OK) {
        printf("Dialog closed with OK\n");
    } else {
        printf("Dialog cancelled\n");
    }
    
    /* Clean up application */
    tv_application_destroy(app);
    
    return 0;
}

// Made with Bob
