#ifndef _MATH_H_WRAPPER
#ifdef __cplusplus
# define exception __math_exception
#endif
#include_next <math.h>
#ifdef __cplusplus
# undef exception
#endif
#define _MATH_H_WRAPPER
#endif /* _MATH_H_WRAPPER */
