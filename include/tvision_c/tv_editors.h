/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_EDITORS.H                                                          */
/*                                                                         */
/*   C wrapper for Turbo Vision editor classes                            */
/*   (TEditor, TFileEditor, TMemo, TIndicator)                            */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_EDITORS_H
#define TV_EDITORS_H

#include "tv_types.h"
#include "tv_view.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque pointers */
typedef struct tv_Editor tv_Editor;
typedef struct tv_FileEditor tv_FileEditor;
typedef struct tv_Memo tv_Memo;
typedef struct tv_Indicator tv_Indicator;

/* Editor flags */
#define TV_EF_CASE_SENSITIVE    0x0001
#define TV_EF_WHOLE_WORDS_ONLY  0x0002
#define TV_EF_PROMPT_ON_REPLACE 0x0004
#define TV_EF_REPLACE_ALL       0x0008
#define TV_EF_DO_REPLACE        0x0010
#define TV_EF_BACKWARD_SEARCH   0x0020

/* Editor commands */
#define TV_CM_FIND              82
#define TV_CM_REPLACE           83
#define TV_CM_SEARCH_AGAIN      84

/* Editor status flags */
#define TV_EF_MODIFIED          0x01
#define TV_EF_INSERT_MODE       0x02
#define TV_EF_AUTO_INDENT       0x04

/* TIndicator functions */
tv_Indicator* tv_indicator_create(tv_Rect bounds);
void tv_indicator_destroy(tv_Indicator* indicator);
void tv_indicator_set_value(tv_Indicator* indicator, tv_Point location, tv_bool modified);

/* Cast functions */
tv_View* tv_indicator_to_view(tv_Indicator* indicator);
tv_Indicator* tv_view_to_indicator(tv_View* view);

/* TEditor functions */
tv_Editor* tv_editor_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar, 
                            tv_ScrollBar* v_scrollbar, tv_Indicator* indicator, int buf_size);
void tv_editor_destroy(tv_Editor* editor);

/* Text operations */
void tv_editor_insert_text(tv_Editor* editor, const char* text, int length, tv_bool select);
void tv_editor_delete_select(tv_Editor* editor);
void tv_editor_set_select(tv_Editor* editor, int new_start, int new_end, tv_bool cursor_at_start);
tv_bool tv_editor_has_selection(tv_Editor* editor);
void tv_editor_get_selection(tv_Editor* editor, int* start, int* end);

/* Clipboard operations */
void tv_editor_clipboard_cut(tv_Editor* editor);
void tv_editor_clipboard_copy(tv_Editor* editor);
void tv_editor_clipboard_paste(tv_Editor* editor);
void tv_editor_clipboard_clear(tv_Editor* editor);

/* Search and replace */
tv_bool tv_editor_search(tv_Editor* editor, const char* find_str, tv_ushort options);
void tv_editor_replace(tv_Editor* editor, const char* find_str, const char* replace_str, tv_ushort options);

/* File operations */
tv_bool tv_editor_save(tv_Editor* editor);
tv_bool tv_editor_save_as(tv_Editor* editor, const char* filename);
tv_bool tv_editor_load(tv_Editor* editor, const char* filename);

/* Editor state */
tv_bool tv_editor_is_modified(tv_Editor* editor);
void tv_editor_set_modified(tv_Editor* editor, tv_bool modified);
tv_bool tv_editor_is_insert_mode(tv_Editor* editor);
void tv_editor_set_insert_mode(tv_Editor* editor, tv_bool insert);
int tv_editor_get_cursor_pos(tv_Editor* editor);
void tv_editor_set_cursor_pos(tv_Editor* editor, int pos);

/* Buffer access */
const char* tv_editor_get_buffer(tv_Editor* editor);
int tv_editor_get_buffer_len(tv_Editor* editor);
void tv_editor_set_buffer(tv_Editor* editor, const char* text, int length);

/* Undo/Redo */
void tv_editor_undo(tv_Editor* editor);
tv_bool tv_editor_can_undo(tv_Editor* editor);

/* Cast functions */
tv_View* tv_editor_to_view(tv_Editor* editor);
tv_Scroller* tv_editor_to_scroller(tv_Editor* editor);
tv_Editor* tv_view_to_editor(tv_View* view);

/* TFileEditor functions */
tv_FileEditor* tv_fileeditor_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar,
                                     tv_ScrollBar* v_scrollbar, tv_Indicator* indicator,
                                     const char* filename);
void tv_fileeditor_destroy(tv_FileEditor* editor);
const char* tv_fileeditor_get_filename(tv_FileEditor* editor);
void tv_fileeditor_set_filename(tv_FileEditor* editor, const char* filename);
tv_bool tv_fileeditor_save(tv_FileEditor* editor);
tv_bool tv_fileeditor_save_as(tv_FileEditor* editor);
tv_bool tv_fileeditor_load_file(tv_FileEditor* editor);

/* Cast functions */
tv_View* tv_fileeditor_to_view(tv_FileEditor* editor);
tv_Editor* tv_fileeditor_to_editor(tv_FileEditor* editor);
tv_FileEditor* tv_view_to_fileeditor(tv_View* view);
tv_FileEditor* tv_editor_to_fileeditor(tv_Editor* editor);

/* TMemo functions */
tv_Memo* tv_memo_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar,
                        tv_ScrollBar* v_scrollbar, tv_Indicator* indicator, int buf_size);
void tv_memo_destroy(tv_Memo* memo);
void tv_memo_set_data(tv_Memo* memo, const char* text);
void tv_memo_get_data(tv_Memo* memo, char* buffer, int buffer_size);

/* Cast functions */
tv_View* tv_memo_to_view(tv_Memo* memo);
tv_Editor* tv_memo_to_editor(tv_Memo* memo);
tv_Memo* tv_view_to_memo(tv_View* view);
tv_Memo* tv_editor_to_memo(tv_Editor* editor);

#ifdef __cplusplus
}
#endif

#endif /* TV_EDITORS_H */

// Made with Bob
