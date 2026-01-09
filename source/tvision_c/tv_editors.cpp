/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_EDITORS.CPP                                                        */
/*                                                                         */
/*   C wrapper implementation for editor classes                          */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_TEditor
#define Uses_TFileEditor
#define Uses_TMemo
#define Uses_TIndicator
#define Uses_TScrollBar
#define Uses_TRect
#define Uses_TPoint
#include <tvision/tv.h>

#include "tvision_c/tv_editors.h"
#include <cstring>

extern "C" {

/* TIndicator functions */

tv_Indicator* tv_indicator_create(tv_Rect bounds) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Indicator*>(new TIndicator(rect));
}

void tv_indicator_destroy(tv_Indicator* indicator) {
    if (indicator) {
        TObject::destroy(reinterpret_cast<TIndicator*>(indicator));
    }
}

void tv_indicator_set_value(tv_Indicator* indicator, tv_Point location, tv_bool modified) {
    TIndicator* ind = reinterpret_cast<TIndicator*>(indicator);
    TPoint loc;
    loc.x = location.x;
    loc.y = location.y;
    ind->setValue(loc, modified ? True : False);
}

tv_View* tv_indicator_to_view(tv_Indicator* indicator) {
    return reinterpret_cast<tv_View*>(indicator);
}

tv_Indicator* tv_view_to_indicator(tv_View* view) {
    return reinterpret_cast<tv_Indicator*>(view);
}

/* TEditor functions */

tv_Editor* tv_editor_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar,
                            tv_ScrollBar* v_scrollbar, tv_Indicator* indicator, int buf_size) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Editor*>(
        new TEditor(rect,
                   reinterpret_cast<TScrollBar*>(h_scrollbar),
                   reinterpret_cast<TScrollBar*>(v_scrollbar),
                   reinterpret_cast<TIndicator*>(indicator),
                   buf_size)
    );
}

void tv_editor_destroy(tv_Editor* editor) {
    if (editor) {
        TObject::destroy(reinterpret_cast<TEditor*>(editor));
    }
}

/* Text operations */

void tv_editor_insert_text(tv_Editor* editor, const char* text, int length, tv_bool select) {
    if (text && length > 0) {
        reinterpret_cast<TEditor*>(editor)->insertText(text, length, select ? True : False);
    }
}

void tv_editor_delete_select(tv_Editor* editor) {
    reinterpret_cast<TEditor*>(editor)->deleteSelect();
}

void tv_editor_set_select(tv_Editor* editor, int new_start, int new_end, tv_bool cursor_at_start) {
    reinterpret_cast<TEditor*>(editor)->setSelect(new_start, new_end, cursor_at_start ? True : False);
}

tv_bool tv_editor_has_selection(tv_Editor* editor) {
    return reinterpret_cast<TEditor*>(editor)->hasSelection() ? TV_TRUE : TV_FALSE;
}

void tv_editor_get_selection(tv_Editor* editor, int* start, int* end) {
    TEditor* ed = reinterpret_cast<TEditor*>(editor);
    if (start) *start = ed->selStart;
    if (end) *end = ed->selEnd;
}

/* Clipboard operations */

void tv_editor_clipboard_cut(tv_Editor* editor) {
    reinterpret_cast<TEditor*>(editor)->clipCut();
}

void tv_editor_clipboard_copy(tv_Editor* editor) {
    reinterpret_cast<TEditor*>(editor)->clipCopy();
}

void tv_editor_clipboard_paste(tv_Editor* editor) {
    reinterpret_cast<TEditor*>(editor)->clipPaste();
}

void tv_editor_clipboard_clear(tv_Editor* editor) {
    reinterpret_cast<TEditor*>(editor)->clipClear();
}

/* Search and replace */

tv_bool tv_editor_search(tv_Editor* editor, const char* find_str, tv_ushort options) {
    if (!find_str) return TV_FALSE;
    return reinterpret_cast<TEditor*>(editor)->search(find_str, options) ? TV_TRUE : TV_FALSE;
}

void tv_editor_replace(tv_Editor* editor, const char* find_str, const char* replace_str, tv_ushort options) {
    if (find_str && replace_str) {
        reinterpret_cast<TEditor*>(editor)->doSearchReplace();
    }
}

/* File operations */

tv_bool tv_editor_save(tv_Editor* editor) {
    return reinterpret_cast<TEditor*>(editor)->save() ? TV_TRUE : TV_FALSE;
}

tv_bool tv_editor_save_as(tv_Editor* editor, const char* filename) {
    if (!filename) return TV_FALSE;
    TEditor* ed = reinterpret_cast<TEditor*>(editor);
    return ed->saveAs() ? TV_TRUE : TV_FALSE;
}

tv_bool tv_editor_load(tv_Editor* editor, const char* filename) {
    if (!filename) return TV_FALSE;
    TEditor* ed = reinterpret_cast<TEditor*>(editor);
    ed->setBufLen(0);
    return ed->insertFrom(filename) ? TV_TRUE : TV_FALSE;
}

/* Editor state */

tv_bool tv_editor_is_modified(tv_Editor* editor) {
    return reinterpret_cast<TEditor*>(editor)->isClipboard() ? TV_FALSE : 
           (reinterpret_cast<TEditor*>(editor)->modified ? TV_TRUE : TV_FALSE);
}

void tv_editor_set_modified(tv_Editor* editor, tv_bool modified) {
    reinterpret_cast<TEditor*>(editor)->modified = modified ? True : False;
}

tv_bool tv_editor_is_insert_mode(tv_Editor* editor) {
    return reinterpret_cast<TEditor*>(editor)->overwrite ? TV_FALSE : TV_TRUE;
}

void tv_editor_set_insert_mode(tv_Editor* editor, tv_bool insert) {
    reinterpret_cast<TEditor*>(editor)->overwrite = insert ? False : True;
}

int tv_editor_get_cursor_pos(tv_Editor* editor) {
    return reinterpret_cast<TEditor*>(editor)->curPtr;
}

void tv_editor_set_cursor_pos(tv_Editor* editor, int pos) {
    TEditor* ed = reinterpret_cast<TEditor*>(editor);
    if (pos >= 0 && pos <= ed->bufLen) {
        ed->curPtr = pos;
        ed->update(ufView);
    }
}

/* Buffer access */

const char* tv_editor_get_buffer(tv_Editor* editor) {
    return reinterpret_cast<TEditor*>(editor)->buffer;
}

int tv_editor_get_buffer_len(tv_Editor* editor) {
    return reinterpret_cast<TEditor*>(editor)->bufLen;
}

void tv_editor_set_buffer(tv_Editor* editor, const char* text, int length) {
    TEditor* ed = reinterpret_cast<TEditor*>(editor);
    ed->setBufLen(0);
    if (text && length > 0) {
        ed->insertText(text, length, False);
    }
}

/* Undo/Redo */

void tv_editor_undo(tv_Editor* editor) {
    reinterpret_cast<TEditor*>(editor)->undo();
}

tv_bool tv_editor_can_undo(tv_Editor* editor) {
    return reinterpret_cast<TEditor*>(editor)->canUndo ? TV_TRUE : TV_FALSE;
}

/* Cast functions */

tv_View* tv_editor_to_view(tv_Editor* editor) {
    return reinterpret_cast<tv_View*>(editor);
}

tv_Scroller* tv_editor_to_scroller(tv_Editor* editor) {
    return reinterpret_cast<tv_Scroller*>(editor);
}

tv_Editor* tv_view_to_editor(tv_View* view) {
    return reinterpret_cast<tv_Editor*>(view);
}

/* TFileEditor functions */

tv_FileEditor* tv_fileeditor_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar,
                                     tv_ScrollBar* v_scrollbar, tv_Indicator* indicator,
                                     const char* filename) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_FileEditor*>(
        new TFileEditor(rect,
                       reinterpret_cast<TScrollBar*>(h_scrollbar),
                       reinterpret_cast<TScrollBar*>(v_scrollbar),
                       reinterpret_cast<TIndicator*>(indicator),
                       filename)
    );
}

void tv_fileeditor_destroy(tv_FileEditor* editor) {
    if (editor) {
        TObject::destroy(reinterpret_cast<TFileEditor*>(editor));
    }
}

const char* tv_fileeditor_get_filename(tv_FileEditor* editor) {
    return reinterpret_cast<TFileEditor*>(editor)->fileName;
}

void tv_fileeditor_set_filename(tv_FileEditor* editor, const char* filename) {
    TFileEditor* ed = reinterpret_cast<TFileEditor*>(editor);
    if (ed->fileName) {
        delete[] ed->fileName;
    }
    if (filename) {
        size_t len = std::strlen(filename);
        char* new_name = new char[len + 1];
        std::strcpy(new_name, filename);
        ed->fileName = new_name;
    } else {
        ed->fileName = nullptr;
    }
}

tv_bool tv_fileeditor_save(tv_FileEditor* editor) {
    return reinterpret_cast<TFileEditor*>(editor)->save() ? TV_TRUE : TV_FALSE;
}

tv_bool tv_fileeditor_save_as(tv_FileEditor* editor) {
    return reinterpret_cast<TFileEditor*>(editor)->saveAs() ? TV_TRUE : TV_FALSE;
}

tv_bool tv_fileeditor_load_file(tv_FileEditor* editor) {
    TFileEditor* ed = reinterpret_cast<TFileEditor*>(editor);
    if (ed->fileName) {
        ed->setBufLen(0);
        return ed->insertFrom(ed->fileName) ? TV_TRUE : TV_FALSE;
    }
    return TV_FALSE;
}

/* Cast functions */

tv_View* tv_fileeditor_to_view(tv_FileEditor* editor) {
    return reinterpret_cast<tv_View*>(editor);
}

tv_Editor* tv_fileeditor_to_editor(tv_FileEditor* editor) {
    return reinterpret_cast<tv_Editor*>(editor);
}

tv_FileEditor* tv_view_to_fileeditor(tv_View* view) {
    return reinterpret_cast<tv_FileEditor*>(view);
}

tv_FileEditor* tv_editor_to_fileeditor(tv_Editor* editor) {
    return reinterpret_cast<tv_FileEditor*>(editor);
}

/* TMemo functions */

tv_Memo* tv_memo_create(tv_Rect bounds, tv_ScrollBar* h_scrollbar,
                        tv_ScrollBar* v_scrollbar, tv_Indicator* indicator, int buf_size) {
    TRect rect(bounds.ax, bounds.ay, bounds.bx, bounds.by);
    return reinterpret_cast<tv_Memo*>(
        new TMemo(rect,
                 reinterpret_cast<TScrollBar*>(h_scrollbar),
                 reinterpret_cast<TScrollBar*>(v_scrollbar),
                 reinterpret_cast<TIndicator*>(indicator),
                 buf_size)
    );
}

void tv_memo_destroy(tv_Memo* memo) {
    if (memo) {
        TObject::destroy(reinterpret_cast<TMemo*>(memo));
    }
}

void tv_memo_set_data(tv_Memo* memo, const char* text) {
    if (text) {
        reinterpret_cast<TMemo*>(memo)->setData(const_cast<char*>(text));
    }
}

void tv_memo_get_data(tv_Memo* memo, char* buffer, int buffer_size) {
    if (buffer && buffer_size > 0) {
        TMemo* m = reinterpret_cast<TMemo*>(memo);
        m->getData(buffer);
        buffer[buffer_size - 1] = '\0';  // Ensure null termination
    }
}

/* Cast functions */

tv_View* tv_memo_to_view(tv_Memo* memo) {
    return reinterpret_cast<tv_View*>(memo);
}

tv_Editor* tv_memo_to_editor(tv_Memo* memo) {
    return reinterpret_cast<tv_Editor*>(memo);
}

tv_Memo* tv_view_to_memo(tv_View* view) {
    return reinterpret_cast<tv_Memo*>(view);
}

tv_Memo* tv_editor_to_memo(tv_Editor* editor) {
    return reinterpret_cast<tv_Memo*>(editor);
}

} /* extern "C" */

// Made with Bob
