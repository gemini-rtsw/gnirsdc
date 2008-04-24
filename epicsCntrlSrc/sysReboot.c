
static struct {
        void *v;
        char *c;
} rcsid = {
        &rcsid,
        "$Id$"
};

#include <reboot.h>
/* reboot vxworks box (mv167 or mv162*/
void sysReboot (void)
{
  *(SYS_WDOG) = *(SYS_WDOG) | SYS_WDOG_BITS;
  *(SYS_RSET) = *(SYS_RSET) | SYS_RSET_BITS;
}
