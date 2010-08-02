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
 * Revision 1.2  2009/05/27 19:32:21  fkraemer
 * fkraemer - copied my complete working dir over trunk
 *
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
/*printf ("wfsUpdateAstCtx: pgsub->sevr = %s\n", &pgsub->sevr); */
 
    if(pgsub->sevr != INVALID_ALARM)
    { 
        /*printf("TCS = 1 !!!!!, to astSetctx\n"); */
        TCS = 1; 
        astSetctx(pgsub->a); 
        printf("From astSetctx\n"); 
    } 
    else 
    { 
        /*printf("TCS = 0 ??????\n"); */
        TCS = 0 ;
        return ERROR; 
    } 

 

    return OK;
}

/*
 *+
 * FUNCTION NAME:
 *      selectWcs
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
int overridePort = 0;

long selectWcs(struct cadRecord *pCad)
{
   char camera[MAX_STRING_SIZE] = "unknown";
   char selectedPort[MAX_STRING_SIZE] = "unknown";
   char wcscamera[MAX_STRING_SIZE] = "unknown";
   long agport = 0; /*default agport*/
   long status = CAD_ACCEPT; 
    
   printf(" selectWcs\n");
   
   *(long*) pCad->vala = 1;  /* Disable wfs switch by default*/ 
   switch (DIRECTIVE)
    {
      case CAD_START:            /* No action required           */
	  printf("WCS file based on selection=%s, camera=%s AGport=%s \n",
		  pCad->a, pCad->b, pCad->c);
          strncpy(selectedPort, (char *)pCad->a, MAX_STRING_SIZE-1);
          strncpy(camera, (char *)pCad->b, MAX_STRING_SIZE-1);
	  
	  agport = atoi(pCad->c);
          printf("selectedPort = %s\n",selectedPort); 
          printf("camera = %s\n",camera); 
          printf("agport = %d\n",agport); 


	  if ((strstr(camera, "Long") != NULL) || 
	      (strstr(camera, "Open") != NULL) )
	  {
	  	strcpy(wcscamera, "long");
          }
	  else if (strstr(camera, "Short") != NULL) {
	  	strcpy(wcscamera, "short");
	  }
	  else {

	        strncpy(pCad->mess, "selectWcsCad: Invalid camera",MAX_STRING_SIZE - 1);
		printf("ERR: selectWcsCad: Invalid camera\n");
	        status = CAD_REJECT;
		break;
	  }

	  if (overridePort)
	     sprintf(pCad->valb, "data/p%s%s.wcs", selectedPort, wcscamera); /* set file name*/
	  else 
	     sprintf(pCad->valb, "data/p%ld%s.wcs", agport, wcscamera); /* set file name*/
	  *(long*) pCad->vala = 0; /*enable setting wcsfile*/


      break;
     }

    return OK;
}

long copyTCSvalues(struct genSubRecord *pgsub)
{
printf ("in copyTCSvalues\n"); 
printf ("tcsValues.a = %s\n", (char *)pgsub->a); 
printf ("tcsValues.b = %s\n",pgsub->b); 
printf ("tcsValues.c = %s\n",pgsub->c); 
 
        pgsub->vala = pgsub->a; 
        pgsub->valb = pgsub->b; 
        pgsub->valc = pgsub->c; 

    return OK;
}
