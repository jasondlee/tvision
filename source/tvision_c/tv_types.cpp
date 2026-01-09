/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV_TYPES.CPP                                                          */
/*                                                                         */
/*   C wrapper implementation for Turbo Vision fundamental types          */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#define Uses_TPoint
#define Uses_TRect
#include <tvision/tv.h>

#include "tvision_c/tv_types.h"

extern "C" {

/* TPoint functions */

tv_Point tv_point_make(int x, int y) {
    tv_Point p;
    p.x = x;
    p.y = y;
    return p;
}

tv_Point tv_point_add(tv_Point p1, tv_Point p2) {
    tv_Point result;
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    return result;
}

tv_Point tv_point_sub(tv_Point p1, tv_Point p2) {
    tv_Point result;
    result.x = p1.x - p2.x;
    result.y = p1.y - p2.y;
    return result;
}

tv_bool tv_point_equals(tv_Point p1, tv_Point p2) {
    return (p1.x == p2.x && p1.y == p2.y) ? TV_TRUE : TV_FALSE;
}

/* TRect functions */

tv_Rect tv_rect_make(int ax, int ay, int bx, int by) {
    tv_Rect r;
    r.ax = ax;
    r.ay = ay;
    r.bx = bx;
    r.by = by;
    return r;
}

tv_Rect tv_rect_make_points(tv_Point a, tv_Point b) {
    tv_Rect r;
    r.ax = a.x;
    r.ay = a.y;
    r.bx = b.x;
    r.by = b.y;
    return r;
}

tv_Rect tv_rect_move(tv_Rect r, int dx, int dy) {
    tv_Rect result = r;
    result.ax += dx;
    result.ay += dy;
    result.bx += dx;
    result.by += dy;
    return result;
}

tv_Rect tv_rect_grow(tv_Rect r, int dx, int dy) {
    tv_Rect result = r;
    result.ax -= dx;
    result.ay -= dy;
    result.bx += dx;
    result.by += dy;
    return result;
}

tv_Rect tv_rect_intersect(tv_Rect r1, tv_Rect r2) {
    TRect rect1(r1.ax, r1.ay, r1.bx, r1.by);
    TRect rect2(r2.ax, r2.ay, r2.bx, r2.by);
    rect1.intersect(rect2);
    
    tv_Rect result;
    result.ax = rect1.a.x;
    result.ay = rect1.a.y;
    result.bx = rect1.b.x;
    result.by = rect1.b.y;
    return result;
}

tv_Rect tv_rect_union(tv_Rect r1, tv_Rect r2) {
    TRect rect1(r1.ax, r1.ay, r1.bx, r1.by);
    TRect rect2(r2.ax, r2.ay, r2.bx, r2.by);
    rect1.Union(rect2);
    
    tv_Rect result;
    result.ax = rect1.a.x;
    result.ay = rect1.a.y;
    result.bx = rect1.b.x;
    result.by = rect1.b.y;
    return result;
}

tv_bool tv_rect_contains(tv_Rect r, tv_Point p) {
    TRect rect(r.ax, r.ay, r.bx, r.by);
    TPoint point;
    point.x = p.x;
    point.y = p.y;
    return rect.contains(point) ? TV_TRUE : TV_FALSE;
}

tv_bool tv_rect_equals(tv_Rect r1, tv_Rect r2) {
    return (r1.ax == r2.ax && r1.ay == r2.ay && 
            r1.bx == r2.bx && r1.by == r2.by) ? TV_TRUE : TV_FALSE;
}

tv_bool tv_rect_is_empty(tv_Rect r) {
    TRect rect(r.ax, r.ay, r.bx, r.by);
    return rect.isEmpty() ? TV_TRUE : TV_FALSE;
}

int tv_rect_width(tv_Rect r) {
    return r.bx - r.ax;
}

int tv_rect_height(tv_Rect r) {
    return r.by - r.ay;
}

} /* extern "C" */

// Made with Bob
