/*----------------------------------------------------------*/
/*                                                          */
/*   cstatusline.h - C wrappers for TStatusLine classes    */
/*                                                          */
/*   C interface for building Turbo Vision status lines    */
/*                                                          */
/*----------------------------------------------------------*/

#ifndef CSTATUSLINE_H
#define CSTATUSLINE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque handles for C code */
typedef struct TStatusItem_C TStatusItem_C;
typedef struct TStatusDef_C TStatusDef_C;
typedef struct TStatusLine_C TStatusLine_C;

/* Re-use key codes from cmenuitem if available, otherwise define them */
#ifndef C_kbNoKey
/* Key codes - common ones from TKeys */
#define C_kbNoKey     0x0000
#define C_kbF1        0x3B00
#define C_kbF2        0x3C00
#define C_kbF3        0x3D00
#define C_kbF5        0x3F00
#define C_kbF6        0x4000
#define C_kbF10       0x4400
#define C_kbCtrlN     0x310E
#define C_kbCtrlQ     0x1011
#define C_kbCtrlU     0x1615
#define C_kbCtrlW     0x1117
#define C_kbCtrlF5    0x6000
#define C_kbCtrlIns   0x0492
#define C_kbCtrlDel   0x0693
#define C_kbShiftDel  0x052E
#define C_kbShiftIns  0x0530
#define C_kbShiftF6   0x5800
#define C_kbAltE      0x1200
#define C_kbAltF      0x2100
#define C_kbAltS      0x1F00
#define C_kbAltW      0x1100
#define C_kbAltX      0x2D00
#define C_kbAltF3     0x4500
#endif

/* Help context constant */
#ifndef C_hcNoContext
#define C_hcNoContext 0
#endif

/*
 * TStatusItem functions
 */

/* Create a new status item */
TStatusItem_C* c_statusitem_new(
    const char* text,
    unsigned short key,
    unsigned short command
);

/* Destroy a status item (and its chain) */
void c_statusitem_destroy(TStatusItem_C* item);

/* Append one status item to another (operator +) */
TStatusItem_C* c_statusitem_append(TStatusItem_C* item1, TStatusItem_C* item2);

/*
 * TStatusDef functions
 */

/* Create a new status definition */
TStatusDef_C* c_statusdef_new(
    unsigned short min,
    unsigned short max,
    TStatusItem_C* items
);

/* Destroy a status definition (and its chain) */
void c_statusdef_destroy(TStatusDef_C* def);

/* Add a status item to a status definition (operator +) */
TStatusDef_C* c_statusdef_add_item(TStatusDef_C* def, TStatusItem_C* item);

/* Add a status definition to another status definition (operator +) */
TStatusDef_C* c_statusdef_add_def(TStatusDef_C* def1, TStatusDef_C* def2);

/*
 * TStatusLine functions
 */

/* Create a new status line from a status definition */
TStatusLine_C* c_statusline_new(
    short ax, short ay, short bx, short by,
    TStatusDef_C* defs
);

/* Destroy a status line */
void c_statusline_destroy(TStatusLine_C* statusLine);

/* Get the underlying TStatusLine pointer (for use with TApplication) */
void* c_statusline_get_ptr(TStatusLine_C* statusLine);

/* Get the underlying TStatusDef reference (for use with TStatusLine constructor) */
void* c_statusdef_get_ptr(TStatusDef_C* def);

#ifdef __cplusplus
}
#endif

#endif /* CSTATUSLINE_H */

// Made with Bob
