static struct {
        void *v;
        char *c;
} rcsid = {
        &rcsid,
        "$Id$"
};
/*
 * Copyright 1997 Association of Universities for Research in Astronomy, Inc.
 * See the file COPYRIGHT for more details.
 *
 * FILENAME
 * simCalc.c
 *
 * DESCRIPTION 
 * Dummy subroutine for the genSub record to prevent
 * errors on startup
 *
 * FUNCTION NAME(S)
 * simCalc - genSub routine which will fill in various EPICS bi records which keep
 *           track of the simulation mode (vsm, notVsm, fast, notFast, etc.).

 * DEPENDENCIES (optional)
 * 
 *
 *INDENT-OFF*
 * $Log$
 * Revision 1.1.1.1  1998/12/15 16:18:51  buchholz
 * Imported gnaacSrc into CVS
 *
 *INDENT-ON* 
 */

#include <epCommon.h>
#include <genSubRecord.h>

long simCalcProc( struct genSubRecord *pGenSub )
{

    long status = OK;

    cicsLogMessage(3, "simCalcProc executing");


    return status;
}
