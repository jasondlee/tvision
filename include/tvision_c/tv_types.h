/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_TYPES.H                                                            */
/*                                                                         */
/*   C wrapper for Turbo Vision fundamental types (TPoint, TRect)         */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef TV_TYPES_H
#define TV_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Basic type definitions */
typedef unsigned short tv_ushort;
typedef unsigned char tv_uchar;
typedef unsigned int tv_uint;

/* Boolean type */
typedef int tv_bool;
#define TV_FALSE 0
#define TV_TRUE 1

/* TPoint wrapper - simple struct, direct mapping */
typedef struct tv_Point {
    int x;
    int y;
} tv_Point;

/* TRect wrapper - simple struct, direct mapping */
typedef struct tv_Rect {
    int ax, ay;  /* Top-left corner */
    int bx, by;  /* Bottom-right corner */
} tv_Rect;

/* TPoint functions */
tv_Point tv_point_make(int x, int y);
tv_Point tv_point_add(tv_Point p1, tv_Point p2);
tv_Point tv_point_sub(tv_Point p1, tv_Point p2);
tv_bool tv_point_equals(tv_Point p1, tv_Point p2);

/* TRect functions */
tv_Rect tv_rect_make(int ax, int ay, int bx, int by);
tv_Rect tv_rect_make_points(tv_Point a, tv_Point b);
tv_Rect tv_rect_move(tv_Rect r, int dx, int dy);
tv_Rect tv_rect_grow(tv_Rect r, int dx, int dy);
tv_Rect tv_rect_intersect(tv_Rect r1, tv_Rect r2);
tv_Rect tv_rect_union(tv_Rect r1, tv_Rect r2);
tv_bool tv_rect_contains(tv_Rect r, tv_Point p);
tv_bool tv_rect_equals(tv_Rect r1, tv_Rect r2);
tv_bool tv_rect_is_empty(tv_Rect r);
int tv_rect_width(tv_Rect r);
int tv_rect_height(tv_Rect r);

#ifdef __cplusplus
}
#endif

#endif /* TV_TYPES_H */

// Made with Bob
