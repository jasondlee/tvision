/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   CCONSTS.H                                                             */
/*                                                                         */
/*   C wrappers for Turbo Vision key code constants                       */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef __CCONSTS_H
#define __CCONSTS_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined( __TKeys )
#define __TKeys

#if defined( __FLAT__ ) && !defined( __WINDOWS_H )
#include <tvision/compat/windows/windows.h>
#endif

/* Control keys */
#define kbCtrlA     0x0001
#define kbCtrlB     0x0002
#define kbCtrlC     0x0003
#define kbCtrlD     0x0004
#define kbCtrlE     0x0005
#define kbCtrlF     0x0006
#define kbCtrlG     0x0007
#define kbCtrlH     0x0008
#define kbCtrlI     0x0009
#define kbCtrlJ     0x000a
#define kbCtrlK     0x000b
#define kbCtrlL     0x000c
#define kbCtrlM     0x000d
#define kbCtrlN     0x000e
#define kbCtrlO     0x000f
#define kbCtrlP     0x0010
#define kbCtrlQ     0x0011
#define kbCtrlR     0x0012
#define kbCtrlS     0x0013
#define kbCtrlT     0x0014
#define kbCtrlU     0x0015
#define kbCtrlV     0x0016
#define kbCtrlW     0x0017
#define kbCtrlX     0x0018
#define kbCtrlY     0x0019
#define kbCtrlZ     0x001a

/* Extended key codes */
#define kbEsc       0x011b
#define kbAltSpace  0x0200
#define kbCtrlIns   0x0400
#define kbShiftIns  0x0500
#define kbCtrlDel   0x0600
#define kbShiftDel  0x0700
#define kbBack      0x0e08
#define kbCtrlBack  0x0e7f
#define kbShiftTab  0x0f00
#define kbTab       0x0f09
#define kbAltQ      0x1000
#define kbAltW      0x1100
#define kbAltE      0x1200
#define kbAltR      0x1300
#define kbAltT      0x1400
#define kbAltY      0x1500
#define kbAltU      0x1600
#define kbAltI      0x1700
#define kbAltO      0x1800
#define kbAltP      0x1900
#define kbCtrlEnter 0x1c0a
#define kbEnter     0x1c0d
#define kbAltA      0x1e00
#define kbAltS      0x1f00
#define kbAltD      0x2000
#define kbAltF      0x2100
#define kbAltG      0x2200
#define kbAltH      0x2300
#define kbAltJ      0x2400
#define kbAltK      0x2500
#define kbAltL      0x2600
#define kbAltZ      0x2c00
#define kbAltX      0x2d00
#define kbAltC      0x2e00
#define kbAltV      0x2f00
#define kbAltB      0x3000
#define kbAltN      0x3100
#define kbAltM      0x3200
#define kbF1        0x3b00
#define kbF2        0x3c00
#define kbF3        0x3d00
#define kbF4        0x3e00
#define kbF5        0x3f00
#define kbF6        0x4000
#define kbF7        0x4100
#define kbF8        0x4200
#define kbF9        0x4300
#define kbF10       0x4400
#define kbHome      0x4700
#define kbUp        0x4800
#define kbPgUp      0x4900
#define kbGrayMinus 0x4a2d
#define kbLeft      0x4b00
#define kbRight     0x4d00
#define kbGrayPlus  0x4e2b
#define kbEnd       0x4f00
#define kbDown      0x5000
#define kbPgDn      0x5100
#define kbIns       0x5200
#define kbDel       0x5300
#define kbShiftF1   0x5400
#define kbShiftF2   0x5500
#define kbShiftF3   0x5600
#define kbShiftF4   0x5700
#define kbShiftF5   0x5800
#define kbShiftF6   0x5900
#define kbShiftF7   0x5a00
#define kbShiftF8   0x5b00
#define kbShiftF9   0x5c00
#define kbShiftF10  0x5d00
#define kbCtrlF1    0x5e00
#define kbCtrlF2    0x5f00
#define kbCtrlF3    0x6000
#define kbCtrlF4    0x6100
#define kbCtrlF5    0x6200
#define kbCtrlF6    0x6300
#define kbCtrlF7    0x6400
#define kbCtrlF8    0x6500
#define kbCtrlF9    0x6600
#define kbCtrlF10   0x6700
#define kbAltF1     0x6800
#define kbAltF2     0x6900
#define kbAltF3     0x6a00
#define kbAltF4     0x6b00
#define kbAltF5     0x6c00
#define kbAltF6     0x6d00
#define kbAltF7     0x6e00
#define kbAltF8     0x6f00
#define kbAltF9     0x7000
#define kbAltF10    0x7100
#define kbCtrlPrtSc 0x7200
#define kbCtrlLeft  0x7300
#define kbCtrlRight 0x7400
#define kbCtrlEnd   0x7500
#define kbCtrlPgDn  0x7600
#define kbCtrlHome  0x7700
#define kbAlt1      0x7800
#define kbAlt2      0x7900
#define kbAlt3      0x7a00
#define kbAlt4      0x7b00
#define kbAlt5      0x7c00
#define kbAlt6      0x7d00
#define kbAlt7      0x7e00
#define kbAlt8      0x7f00
#define kbAlt9      0x8000
#define kbAlt0      0x8100
#define kbAltMinus  0x8200
#define kbAltEqual  0x8300
#define kbCtrlPgUp  0x8400
#define kbNoKey     0x0000

/* Additional extended key codes */
#define kbAltEsc    0x0100
#define kbAltBack   0x0e00
#define kbF11       0x8500
#define kbF12       0x8600
#define kbShiftF11  0x8700
#define kbShiftF12  0x8800
#define kbCtrlF11   0x8900
#define kbCtrlF12   0x8a00
#define kbAltF11    0x8b00
#define kbAltF12    0x8c00
#define kbCtrlUp    0x8d00
#define kbCtrlDown  0x9100
#define kbCtrlTab   0x9400
#define kbAltHome   0x9700
#define kbAltUp     0x9800
#define kbAltPgUp   0x9900
#define kbAltLeft   0x9b00
#define kbAltRight  0x9d00
#define kbAltEnd    0x9f00
#define kbAltDown   0xa000
#define kbAltPgDn   0xa100
#define kbAltIns    0xa200
#define kbAltDel    0xa300
#define kbAltTab    0xa500
#define kbAltEnter  0xa600

/* Keyboard state and shift masks */
/* Note: Platform-specific values are simplified for C compatibility */
#define kbLeftShift   0x0001
#define kbRightShift  0x0002
#define kbShift       0x0003  /* kbLeftShift | kbRightShift */
#define kbLeftCtrl    0x0004
#define kbRightCtrl   0x0004
#define kbCtrlShift   0x0004  /* kbLeftCtrl | kbRightCtrl */
#define kbLeftAlt     0x0008
#define kbRightAlt    0x0008
#define kbAltShift    0x0008  /* kbLeftAlt | kbRightAlt */
#define kbScrollState 0x0010
#define kbNumState    0x0020
#define kbCapsState   0x0040
#define kbInsState    0x0080
#define kbPaste       0x0100
#endif


/* ------------------------------------------------------------------------*/
/*   Command codes and constants from views.h                             */
/* ------------------------------------------------------------------------*/

/* Standard command codes */
#define cmValid         0
#define cmQuit          1
#define cmError         2
#define cmMenu          3
#define cmClose         4
#define cmZoom          5
#define cmResize        6
#define cmNext          7
#define cmPrev          8
#define cmHelp          9

/* TDialog standard commands */
#define cmOK            10
#define cmCancel        11
#define cmYes           12
#define cmNo            13
#define cmDefault       14

/* Standard application commands */
#define cmNew           30
#define cmOpen          31
#define cmSave          32
#define cmSaveAs        33
#define cmSaveAll       34
#define cmChDir         35
#define cmDosShell      36
#define cmCloseAll      37

/* TView State masks */
#define sfVisible       0x001
#define sfCursorVis     0x002
#define sfCursorIns     0x004
#define sfShadow        0x008
#define sfActive        0x010
#define sfSelected      0x020
#define sfFocused       0x040
#define sfDragging      0x080
#define sfDisabled      0x100
#define sfModal         0x200
#define sfDefault       0x400
#define sfExposed       0x800

/* TView Option masks */
#define ofSelectable    0x001
#define ofTopSelect     0x002
#define ofFirstClick    0x004
#define ofFramed        0x008
#define ofPreProcess    0x010
#define ofPostProcess   0x020
#define ofBuffered      0x040
#define ofTileable      0x080
#define ofCenterX       0x100
#define ofCenterY       0x200
#define ofCentered      0x300
#define ofValidate      0x400

/* TView GrowMode masks */
#define gfGrowLoX       0x01
#define gfGrowLoY       0x02
#define gfGrowHiX       0x04
#define gfGrowHiY       0x08
#define gfGrowAll       0x0f
#define gfGrowRel       0x10
#define gfFixed         0x20

/* TView DragMode masks */
#define dmDragMove      0x01
#define dmDragGrow      0x02
#define dmDragGrowLeft  0x04
#define dmLimitLoX      0x10
#define dmLimitLoY      0x20
#define dmLimitHiX      0x40
#define dmLimitHiY      0x80
#define dmLimitAll      (dmLimitLoX | dmLimitLoY | dmLimitHiX | dmLimitHiY)

/* TView Help context codes */
#define hcNoContext     0
#define hcDragging      1

/* TScrollBar part codes */
#define sbLeftArrow     0
#define sbRightArrow    1
#define sbPageLeft      2
#define sbPageRight     3
#define sbUpArrow       4
#define sbDownArrow     5
#define sbPageUp        6
#define sbPageDown      7
#define sbIndicator     8

/* TScrollBar options for TWindow.StandardScrollBar */
#define sbHorizontal    0x000
#define sbVertical      0x001
#define sbHandleKeyboard 0x002

/* TWindow Flags masks */
#define wfMove          0x01
#define wfGrow          0x02
#define wfClose         0x04
#define wfZoom          0x08

/* TView inhibit flags */
#define noMenuBar       0x0001
#define noDeskTop       0x0002
#define noStatusLine    0x0004
#define noBackground    0x0008
#define noFrame         0x0010
#define noViewer        0x0020
#define noHistory       0x0040

/* TWindow number constants */
#define wnNoNumber      0

/* TWindow palette entries */
#define wpBlueWindow    0
#define wpCyanWindow    1
#define wpGrayWindow    2

#if !defined( __COMMAND_CODES )
#define __COMMAND_CODES
/* Application command codes */
#define cmCut           20
#define cmCopy          21
#define cmPaste         22
#define cmUndo          23
#define cmClear         24
#define cmTile          25
#define cmCascade       26
#define cmRedo          27

/* Standard messages */
#define cmReceivedFocus     50
#define cmReleasedFocus     51
#define cmCommandSetChanged 52
#define cmTimerExpired      58

/* TScrollBar messages */
#define cmScrollBarChanged  53
#define cmScrollBarClicked  54

/* TWindow select messages */
#define cmSelectWindowNum   55

/* TListViewer messages */
#define cmListItemSelected  56

/* TProgram messages */
#define cmScreenChanged     57
#endif


/* Event masks */
#define positionalEvents    (evMouse & ~evMouseWheel)
#define focusedEvents       (evKeyboard | evCommand)

#if !defined( __EVENT_CODES )
#define __EVENT_CODES
    /* Event codes */

#define evMouseDown  0x0001
#define evMouseUp    0x0002
#define evMouseMove  0x0004
#define evMouseAuto  0x0008
#define evMouseWheel 0x0020
#define evKeyDown    0x0010
#define evCommand    0x0100
#define evBroadcast  0x0200

    /* Event masks */

#define evNothing    0x0000
#define evMouse      0x002f
#define evKeyboard   0x0010
#define evMessage    0xFF00

    /* Mouse button state masks */

#define mbLeftButton   0x01
#define mbRightButton  0x02
#define mbMiddleButton 0x04

    /* Mouse wheel state masks */

#define mwUp      0x01
#define mwDown    0x02
#define mwLeft    0x04
#define mwRight   0x08

    /* Mouse event flags */

#define meMouseMoved   0x01
#define meDoubleClick  0x02
#define meTripleClick  0x04
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CCONSTS_H */