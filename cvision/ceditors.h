//
// Created by Bob on 2/1/26.
//

#ifndef TVISION_CEDITORS_H
#define TVISION_CEDITORS_H

#include "ctypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations for editor types */
typedef struct tv_Indicator tv_Indicator;
typedef struct tv_Editor tv_Editor;
typedef struct tv_Memo tv_Memo;
typedef struct tv_FileEditor tv_FileEditor;
typedef struct tv_EditWindow tv_EditWindow;

/* Editor command codes */
#define TV_UF_UPDATE  0x01
#define TV_UF_LINE    0x02
#define TV_UF_VIEW    0x04

/* Selection modes */
#define TV_SM_EXTEND  0x01
#define TV_SM_DOUBLE  0x02
#define TV_SM_TRIPLE  0x04

/* Search flags */
#define TV_SF_SEARCH_FAILED  ((unsigned)-0x01)

/* Editor commands */
#define TV_CM_FIND          82
#define TV_CM_REPLACE       83
#define TV_CM_SEARCH_AGAIN  84

/* Navigation commands */
#define TV_CM_CHAR_LEFT     500
#define TV_CM_CHAR_RIGHT    501
#define TV_CM_WORD_LEFT     502
#define TV_CM_WORD_RIGHT    503
#define TV_CM_LINE_START    504
#define TV_CM_LINE_END      505
#define TV_CM_LINE_UP       506
#define TV_CM_LINE_DOWN     507
#define TV_CM_PAGE_UP       508
#define TV_CM_PAGE_DOWN     509
#define TV_CM_TEXT_START    510
#define TV_CM_TEXT_END      511
#define TV_CM_NEW_LINE      512
#define TV_CM_BACK_SPACE    513
#define TV_CM_DEL_CHAR      514
#define TV_CM_DEL_WORD      515
#define TV_CM_DEL_START     516
#define TV_CM_DEL_END       517
#define TV_CM_DEL_LINE      518
#define TV_CM_INS_MODE      519
#define TV_CM_START_SELECT  520
#define TV_CM_HIDE_SELECT   521
#define TV_CM_INDENT_MODE   522
#define TV_CM_UPDATE_TITLE  523
#define TV_CM_SELECT_ALL    524
#define TV_CM_DEL_WORD_LEFT 525
#define TV_CM_ENCODING      526

/* Editor dialog codes */
#define TV_ED_OUT_OF_MEMORY    0
#define TV_ED_READ_ERROR       1
#define TV_ED_WRITE_ERROR      2
#define TV_ED_CREATE_ERROR     3
#define TV_ED_SAVE_MODIFY      4
#define TV_ED_SAVE_UNTITLED    5
#define TV_ED_SAVE_AS          6
#define TV_ED_FIND             7
#define TV_ED_SEARCH_FAILED    8
#define TV_ED_REPLACE          9
#define TV_ED_REPLACE_PROMPT   10

/* Editor flags */
#define TV_EF_CASE_SENSITIVE    0x0001
#define TV_EF_WHOLE_WORDS_ONLY  0x0002
#define TV_EF_PROMPT_ON_REPLACE 0x0004
#define TV_EF_REPLACE_ALL       0x0008
#define TV_EF_DO_REPLACE        0x0010
#define TV_EF_BACKUP_FILES      0x0100

/* Constants */
#define TV_MAX_LINE_LENGTH  256
#define TV_MAX_PATH         260

/* Line ending types */
typedef enum {
    TV_EOL_CRLF = 0,
    TV_EOL_LF = 1,
    TV_EOL_CR = 2
} tv_LineEndingType;

/* Encoding types */
typedef enum {
    TV_ENC_DEFAULT = 0,
    TV_ENC_SINGLE_BYTE = 1
} tv_Encoding;

/* TMemoData structure */
typedef struct tv_MemoData {
    tv_ushort length;
    char buffer[1];
} tv_MemoData;

/* TIndicator functions */
tv_Indicator* tv_indicator_create(tv_Rect bounds);
void tv_indicator_destroy(tv_Indicator* indicator);
void tv_indicator_set_value(tv_Indicator* indicator, tv_Point location, tv_bool modified);

/* TEditor functions */
tv_Editor* tv_editor_create(tv_Rect bounds, tv_ScrollBar* hscrollbar, 
                            tv_ScrollBar* vscrollbar, tv_Indicator* indicator, 
                            tv_uint buf_size);
void tv_editor_destroy(tv_Editor* editor);
tv_bool tv_editor_set_buf_size(tv_Editor* editor, tv_uint new_size);
void tv_editor_scroll_to(tv_Editor* editor, int x, int y);
tv_bool tv_editor_search(tv_Editor* editor, const char* text, tv_ushort flags);
tv_bool tv_editor_insert_text(tv_Editor* editor, const void* text, tv_uint length, tv_bool select);
void tv_editor_delete_select(tv_Editor* editor);
void tv_editor_set_select(tv_Editor* editor, tv_uint start, tv_uint end, tv_bool cursor_at_start);
tv_bool tv_editor_has_selection(tv_Editor* editor);
void tv_editor_undo(tv_Editor* editor);
tv_bool tv_editor_clip_copy(tv_Editor* editor);
void tv_editor_clip_cut(tv_Editor* editor);
void tv_editor_clip_paste(tv_Editor* editor);
void tv_editor_find(tv_Editor* editor);
void tv_editor_replace(tv_Editor* editor);
tv_bool tv_editor_is_clipboard(tv_Editor* editor);
tv_bool tv_editor_cursor_visible(tv_Editor* editor);
void tv_editor_track_cursor(tv_Editor* editor, tv_bool center);
void tv_editor_start_select(tv_Editor* editor);
void tv_editor_hide_select(tv_Editor* editor);
void tv_editor_toggle_ins_mode(tv_Editor* editor);
void tv_editor_toggle_encoding(tv_Editor* editor);

/* TEditor accessors */
tv_uint tv_editor_get_buf_len(tv_Editor* editor);
tv_uint tv_editor_get_sel_start(tv_Editor* editor);
tv_uint tv_editor_get_sel_end(tv_Editor* editor);
tv_uint tv_editor_get_cur_ptr(tv_Editor* editor);
tv_Point tv_editor_get_cur_pos(tv_Editor* editor);
tv_bool tv_editor_get_modified(tv_Editor* editor);
void tv_editor_set_modified(tv_Editor* editor, tv_bool modified);
tv_bool tv_editor_get_overwrite(tv_Editor* editor);
void tv_editor_set_overwrite(tv_Editor* editor, tv_bool overwrite);
tv_bool tv_editor_get_auto_indent(tv_Editor* editor);
void tv_editor_set_auto_indent(tv_Editor* editor, tv_bool auto_indent);
tv_LineEndingType tv_editor_get_line_ending_type(tv_Editor* editor);
void tv_editor_set_line_ending_type(tv_Editor* editor, tv_LineEndingType type);
tv_Encoding tv_editor_get_encoding(tv_Editor* editor);
void tv_editor_set_encoding(tv_Editor* editor, tv_Encoding encoding);

/* TMemo functions */
tv_Memo* tv_memo_create(tv_Rect bounds, tv_ScrollBar* hscrollbar,
                        tv_ScrollBar* vscrollbar, tv_Indicator* indicator,
                        tv_ushort buf_size);
void tv_memo_destroy(tv_Memo* memo);
void tv_memo_get_data(tv_Memo* memo, void* rec);
void tv_memo_set_data(tv_Memo* memo, void* rec);
tv_ushort tv_memo_data_size(tv_Memo* memo);

/* TFileEditor functions */
tv_FileEditor* tv_fileeditor_create(tv_Rect bounds, tv_ScrollBar* hscrollbar,
                                    tv_ScrollBar* vscrollbar, tv_Indicator* indicator,
                                    const char* filename);
void tv_fileeditor_destroy(tv_FileEditor* fileeditor);
tv_bool tv_fileeditor_load_file(tv_FileEditor* fileeditor);
tv_bool tv_fileeditor_save(tv_FileEditor* fileeditor);
tv_bool tv_fileeditor_save_as(tv_FileEditor* fileeditor);
tv_bool tv_fileeditor_save_file(tv_FileEditor* fileeditor);
const char* tv_fileeditor_get_filename(tv_FileEditor* fileeditor);
void tv_fileeditor_set_filename(tv_FileEditor* fileeditor, const char* filename);

/* TEditWindow functions */
tv_EditWindow* tv_editwindow_create(tv_Rect bounds, const char* filename, int number);
void tv_editwindow_destroy(tv_EditWindow* editwindow);
tv_FileEditor* tv_editwindow_get_editor(tv_EditWindow* editwindow);
const char* tv_editwindow_get_title(tv_EditWindow* editwindow, short max_size);

#ifdef __cplusplus
}
#endif

#endif //TVISION_CEDITORS_H

// Made with Bob
