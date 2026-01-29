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
