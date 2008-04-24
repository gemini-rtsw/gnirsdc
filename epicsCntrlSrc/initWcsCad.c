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
 * initWcsCad.c
 *
 * DESCRIPTION 
 * Process any inputs to "setWcs" CAD record.
 *
 * 
 * FUNCTION NAME(S)
 *	initWcsCad
 *
 *   
 * DEPENDENCIES
 * EPICS support library.
 *
 *
 *INDENT-OFF*
 * $Log$
 *INDENT-ON* 
 */



/* VxWorks include files */
#include <vxWorks.h>
#include <taskLib.h>
#include <semLib.h>

/* EPICS specific include files */
#include "epCommon.h"
#include "alarm.h"


#include "slalib.h"
#include "astLib.h"


/* Include file needed for control tasks */
#include <sysLib.h>
#include <car.h>

extern SEM_ID semInitWcs;
extern long TCS;
/* Forward declarations of the functions in this file */

/*
 *+
 * FUNCTION NAME:
 *	initWcsCad
 *
 * INVOCATION:
 * struct cadRecord *pCad;
 * status = initWcsCad( pCad );
 *
 * PARAMETERS: (">" input, "!" modified, "<" output)
 *
 *
 * FUNCTION VALUE:
 * > pCad   (struct cadRecord *)   pointer to CAD data structure
 *
 * PURPOSE:
 * User defined function for "setWcs" CAD record
 *
 * DESCRIPTION:
 *	Gives a semaphore to control task which does the calculations for the wcs.
 *
 *
 * EXTERNAL VARIABLES:
 *	TCS true if TCS is available
 *
 * PRIOR REQUIREMENTS:
 *
 *
 * DEFICIENCIES:
 *
 *
 * HISTORY (optional):
 *
 *
 *
 *-
 */
int initWcsCad(struct cadRecord *pCad)
{
    char errMess[80];
    long status = CAD_ACCEPT;
#ifdef DEBUG
    int t1 = 0;
#endif
  
    /* Action to be taken depends on directive received		*/
    switch (DIRECTIVE)
    {
      case CAD_MARK:	       	/* No action required		*/
	DPRINT(t1, "initWcsCad - MARK directive");

	break;

      case CAD_PRESET:
	DPRINT(t1, "initWcsCad - PRESET directive");

	
	break;
      case CAD_CLEAR:		/* No action required		*/
	DPRINT(t1, "initWcsCad - CLEAR directive");

	break;

      case CAD_START:
	/* copy filenames to output */

	status = assignVal(pCad->ftva, pCad->a, pCad->vala, MSG);
	status += assignVal(pCad->ftvb, pCad->b, pCad->valb, MSG);
	status += assignVal(pCad->ftvc, pCad->c, pCad->valc, MSG);

	if(status == OK)
	{
	    DPRINT(t1, "initWcsCad - START directive");
	    if(setCar(WCS_CAR,CAR_BUSY,OK,"",errMess)!= OK)
	    {
		status = CAD_REJECT;
		DPRINT(1,errMess);
	    }
	    else
	    {
		semGive(semInitWcs);
	    }
	}


	break;

      case CAD_STOP:		   /* Really can't stop	       */
	DPRINT(t1, "initWcsCad - STOP directive");
	strncpy(MSG, "initWcsCad: Cannot stop",MAX_STRING_SIZE - 1);
	status = CAD_REJECT;
	break;

      default:		   /* Unknown directive		*/
	strncpy(MSG, "initWcsCad: Unrecongized directive",MAX_STRING_SIZE - 1);
	status = CAD_REJECT;
	break;
    } 
  
  
    return status;
 }



/*
 *+
 * FUNCTION NAME:
 *      updateAstCtx
 *
 * INVOCATION:
 *      called when "astCtx"  gensub is processed
 *
 * PARAMETERS: (">" input, "!" modified, "<" output)
 *      none
 * FUNCTION VALUE:
 *      status
 *
 * PURPOSE:
 *      Get context from TCS.
 *
 * DESCRIPTION:
 *      Tries to get ast context from TCS.  If it fails, it just sets a 
/
...skipping
 */
long updateAstCtx(struct genSubRecord *pgsub)
{
 
    if(pgsub->sevr != INVALID_ALARM)
    { 
        TCS = 1; 
        astSetctx(pgsub->a); 
    } 
    else 
    { 
        TCS = 0 ;
        return ERROR; 
    } 

 

    return OK;
}
