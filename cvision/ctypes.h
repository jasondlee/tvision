//
// Created by Jason Lee on 1/28/26.
//

#ifndef TVISION_CTYPES_H
#define TVISION_CTYPES_H

#define Uses_EventCodes
#define Uses_fpbase
#define Uses_fpstream
#define Uses_ifpstream
#define Uses_iopstream
#define Uses_ipstream
#define Uses_MsgBox
#define Uses_ofpstream
#define Uses_opstream
#define Uses_otstream
#define Uses_pstream
#define Uses_TApplication
#define Uses_TBackground
#define Uses_TButton
#define Uses_TChDirDialog
#define Uses_TCheckBoxes
#define Uses_TClipboard
#define Uses_TCluster
#define Uses_TCollection
#define Uses_TColorAttr
#define Uses_TColorDialog
#define Uses_TColorDisplay
#define Uses_TColorGroup
#define Uses_TColorGroupList
#define Uses_TColorItem
#define Uses_TColorItemList
#define Uses_TColorSelector
#define Uses_TCommandSet
#define Uses_TDeskTop
#define Uses_TDialog
#define Uses_TDirCollection
#define Uses_TDirEntry
#define Uses_TDirListBox
#define Uses_TDrawBuffer
#define Uses_TDrawSurface
#define Uses_TEditor
#define Uses_TEditWindow
#define Uses_TEvent
#define Uses_TEventQueue
#define Uses_TFileCollection
#define Uses_TFileDialog
#define Uses_TFileEditor
#define Uses_TFileInfoPane
#define Uses_TFileInputLine
#define Uses_TFileList
#define Uses_TFindDialogRec
#define Uses_TFrame
#define Uses_TGroup
#define Uses_THardwareInfo
#define Uses_THistory
#define Uses_THistoryViewer
#define Uses_THistoryWindow
#define Uses_TIndicator
#define Uses_TInputLine
#define Uses_TKeys
#define Uses_TLabel
#define Uses_TListBox
#define Uses_TListViewer
#define Uses_TMemo
#define Uses_TMenu
#define Uses_TMenuBar
#define Uses_TMenuBox
#define Uses_TMenuItem
#define Uses_TMenuPopup
#define Uses_TMenuView
#define Uses_TMonoSelector
#define Uses_TMultiCheckBoxes
#define Uses_TNSCollection
#define Uses_TNSSortedCollection
#define Uses_TObject
#define Uses_TOutline
#define Uses_TOutlineViewer
#define Uses_TPalette
#define Uses_TParamText
#define Uses_TPoint
#define Uses_TPReadObjects
#define Uses_TProgram
#define Uses_TPWrittenObjects
#define Uses_TRadioButtons
#define Uses_TRect
#define Uses_TReplaceDialogRec
#define Uses_TResourceCollection
#define Uses_TResourceFile
#define Uses_TResourceItem
#define Uses_TScreen
#define Uses_TScreenCell
#define Uses_TScrollBar
#define Uses_TScroller
#define Uses_TSearchRec
#define Uses_TSItem
#define Uses_TSortedCollection
#define Uses_TSortedListBox
#define Uses_TStaticText
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TStatusLine
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TStreamableTypes
#define Uses_TStrIndexRec
#define Uses_TStringCollection
#define Uses_TStringList
#define Uses_TStrListMaker
#define Uses_TSubMenu
#define Uses_TSurfaceView
#define Uses_TSystemError
#define Uses_TTerminal
#define Uses_TText
#define Uses_TTextDevice
#define Uses_TTimerQueue
#define Uses_TView
#define Uses_TVMemMgr
#define Uses_TWindow
#define Uses_ViewCommands

typedef unsigned short ushort;

#include "ckeys.h"
#include "ccommands.h"

/* Maximum text size for key events */
#define TV_MAX_CHAR_SIZE    4

#define TV_FALSE 0
#define TV_TRUE 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tv_Application tv_Application;
typedef struct tv_MenuBar tv_MenuBar;
typedef struct tv_StatusLine tv_StatusLine;
typedef struct tv_MenuItem tv_MenuItem;
typedef struct tv_SubMenu tv_SubMenu;
typedef struct tv_StatusItem tv_StatusItem;

/* Basic type definitions */
typedef unsigned short tv_ushort;
typedef unsigned char tv_uchar;
typedef unsigned int tv_uint;
typedef int tv_bool;

/* TPoint wrapper - simple struct, direct mapping */
typedef struct tv_Point {
    int x;
    int y;
} tv_Point;

/* TRect wrapper - simple struct, direct mapping */
typedef struct tv_Rect {
    int ax, ay; /* Top-left corner */
    int bx, by; /* Bottom-right corner */
} tv_Rect;

/* Mouse event structure */
typedef struct tv_MouseEvent {
    tv_Point where;
    tv_ushort event_flags;
    tv_ushort control_key_state;
    tv_uchar buttons;
    tv_uchar wheel;
} tv_MouseEvent;

/* Key event structure */
typedef struct tv_KeyEvent {
    tv_ushort key_code;
    tv_ushort control_key_state;
    char text[TV_MAX_CHAR_SIZE];
    tv_uchar text_length;
} tv_KeyEvent;

/* Message event structure */
typedef struct tv_MessageEvent {
    tv_ushort command;
    void *info_ptr;
} tv_MessageEvent;

/* Main event structure */
typedef struct tv_Event {
    tv_ushort what;

    union {
        tv_MouseEvent mouse;
        tv_KeyEvent key;
        tv_MessageEvent message;
    } data;
} tv_Event;

#ifdef __cplusplus
}
#endif

#endif //TVISION_CTYPES_H
