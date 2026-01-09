/*
 * advanced_demo.c - Advanced Turbo Vision C wrapper demonstration
 * 
 * This example demonstrates advanced features including:
 * - List boxes with string collections
 * - Text editors
 * - Helper functions (message boxes, file dialogs)
 * - Multiple windows
 */

#include <tvision_c/tvision_c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Command constants */
#define CM_NEW_WINDOW   100
#define CM_LIST_DEMO    101
#define CM_EDITOR_DEMO  102
#define CM_ABOUT        103

/* Create a list box demo dialog */
tv_Dialog* create_list_demo(void) {
    tv_Dialog* dialog = tv_create_centered_dialog(50, 18, "List Box Demo");
    
    /* Create a string collection */
    tv_Collection* list = tv_string_collection_create();
    tv_string_collection_insert(list, "Apple");
    tv_string_collection_insert(list, "Banana");
    tv_string_collection_insert(list, "Cherry");
    tv_string_collection_insert(list, "Date");
    tv_string_collection_insert(list, "Elderberry");
    tv_string_collection_insert(list, "Fig");
    tv_string_collection_insert(list, "Grape");
    
    /* Create scrollbar */
    tv_ScrollBar* scrollbar = tv_create_vertical_scrollbar(47, 3, 12);
    tv_group_insert(tv_dialog_to_group(dialog), tv_scrollbar_to_view(scrollbar));
    
    /* Create list box */
    tv_Rect r = tv_rect_make(3, 3, 47, 15);
    tv_ListBox* listbox = tv_listbox_create(r, 1, scrollbar);
    tv_listbox_new_list(listbox, list);
    tv_group_insert(tv_dialog_to_group(dialog), tv_listbox_to_view(listbox));
    
    /* Add label */
    r = tv_rect_make(3, 1, 30, 2);
    tv_Label* label = tv_label_create(r, "Select a fruit:", tv_listbox_to_view(listbox));
    tv_group_insert(tv_dialog_to_group(dialog), tv_label_to_view(label));
    
    /* Add OK/Cancel buttons */
    tv_dialog_add_ok_cancel(dialog);
    
    return dialog;
}

/* Create an editor demo window */
tv_Window* create_editor_demo(void) {
    tv_Rect r = tv_rect_make(5, 2, 70, 20);
    tv_Window* window = tv_window_create(r, "Text Editor Demo", 1);
    
    /* Create indicator */
    r = tv_rect_make(0, 0, 10, 1);
    tv_Indicator* indicator = tv_indicator_create(r);
    tv_group_insert(tv_window_to_group(window), tv_indicator_to_view(indicator));
    
    /* Create scrollbars */
    tv_Rect bounds = tv_window_to_view(window)->getBounds();
    tv_ScrollBar* vscroll = tv_create_vertical_scrollbar(bounds.bx - 1, 1, bounds.by - 2);
    tv_ScrollBar* hscroll = tv_create_horizontal_scrollbar(1, bounds.by - 1, bounds.bx - 2);
    tv_group_insert(tv_window_to_group(window), tv_scrollbar_to_view(vscroll));
    tv_group_insert(tv_window_to_group(window), tv_scrollbar_to_view(hscroll));
    
    /* Create editor */
    r = tv_rect_make(1, 1, bounds.bx - 1, bounds.by - 1);
    tv_Editor* editor = tv_editor_create(r, hscroll, vscroll, indicator, 4096);
    
    /* Insert some sample text */
    const char* sample = 
        "Welcome to the Turbo Vision C Wrapper!\n\n"
        "This is a fully functional text editor.\n"
        "You can:\n"
        "- Type and edit text\n"
        "- Use Ctrl+C to copy\n"
        "- Use Ctrl+V to paste\n"
        "- Use Ctrl+X to cut\n"
        "- Use arrow keys to navigate\n\n"
        "Try editing this text!";
    
    tv_editor_insert_text(editor, sample, strlen(sample), TV_FALSE);
    tv_group_insert(tv_window_to_group(window), tv_editor_to_view(editor));
    
    return window;
}

/* Create menu bar */
tv_MenuBar* create_menu(void) {
    /* Create menu items */
    tv_MenuItem* file_menu = tv_menuitem_create("~N~ew Window", CM_NEW_WINDOW, TV_KB_F2, NULL,
        tv_menuitem_create("~L~ist Demo", CM_LIST_DEMO, TV_KB_F3, NULL,
        tv_menuitem_create("~E~ditor Demo", CM_EDITOR_DEMO, TV_KB_F4, NULL,
        tv_menuitem_create_separator(
        tv_menuitem_create("E~x~it", TV_CM_QUIT, 0, NULL, NULL)))));
    
    tv_MenuItem* help_menu = tv_menuitem_create("~A~bout", CM_ABOUT, 0, NULL, NULL);
    
    tv_MenuItem* menu = tv_menuitem_create_submenu("~F~ile", file_menu,
        tv_menuitem_create_submenu("~H~elp", help_menu, NULL));
    
    /* Create menu bar */
    tv_Rect r = tv_rect_make(0, 0, 80, 1);
    return tv_menubar_create(r, menu);
}

/* Create status line */
tv_StatusLine* create_status_line(void) {
    tv_StatusItem* items = 
        tv_statusitem_create("~F2~ New", TV_KB_F2, CM_NEW_WINDOW,
        tv_statusitem_create("~F3~ List", TV_KB_F3, CM_LIST_DEMO,
        tv_statusitem_create("~F4~ Editor", TV_KB_F4, CM_EDITOR_DEMO,
        tv_statusitem_create("~Alt+X~ Exit", 0, TV_CM_QUIT, NULL))));
    
    tv_Rect r = tv_rect_make(0, 24, 80, 25);
    return tv_statusline_create(r, items);
}

/* Custom application with event handling */
void run_application(void) {
    /* Create application using TCApplication internally.
     * TCApplication is a minimal subclass that exposes TApplication's
     * protected constructor, allowing the C wrapper to instantiate it.
     * This is transparent and provides full TApplication functionality.
     */
    tv_Application* app = tv_application_create();
    tv_Program* program = tv_application_to_program(app);
    
    /* Create and insert menu bar */
    tv_MenuBar* menu = create_menu();
    tv_Group* prog_group = tv_program_to_group(program);
    tv_group_insert(prog_group, tv_menubar_to_view(menu));
    
    /* Create and insert status line */
    tv_StatusLine* status = create_status_line();
    tv_group_insert(prog_group, tv_statusline_to_view(status));
    
    /* Show welcome message */
    tv_message_box(
        "\003Advanced C Wrapper Demo\n\n"
        "Press F2 for new window\n"
        "Press F3 for list demo\n"
        "Press F4 for editor demo\n"
        "Press Alt+X to exit",
        TV_MF_INFORMATION | TV_MF_OK_BUTTON
    );
    
    /* Run the application */
    tv_application_run(app);
    
    /* Cleanup */
    tv_application_destroy(app);
}

int main(void) {
    run_application();
    return 0;
}

// Made with Bob
