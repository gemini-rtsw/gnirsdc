#ifndef _CURSES_H_WRAPPER
#ifdef __cplusplus
# define bool __curses_bool_t
#endif
#include_next <curses.h>
#ifdef __cplusplus
# undef bool
#endif
#define _CURSES_H_WRAPPER
#endif /* _CURSES_H_WRAPPER */
