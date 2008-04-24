#ifndef _SYS_STREAM_H_WRAPPER
#ifdef __cplusplus
# define queue __stream_queue
#endif
#include_next <sys/stream.h>
#ifdef __cplusplus
# undef queue
#endif
#define _SYS_STREAM_H_WRAPPER
#endif /* _SYS_STREAM_H_WRAPPER */
